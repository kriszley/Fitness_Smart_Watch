import snowboydecoder
import sys
import wave
from os import path
import fcntl
from time import sleep

#if len(sys.argv) != 2:
#  print("Error: need to specify model name")
#  print("Usage: python recognizer.py model_file")
#  sys.exit(-1)

model_file = path.join(path.dirname(path.realpath(__file__)), "resources/DEWatch.pmdl")#"resources/alexa_02092017.umdl")#sys.argv[1]
sensitivity = 0.5
detection = snowboydecoder.HotwordDetector(model_file, sensitivity=sensitivity)
new_file = path.join(path.dirname(path.realpath(__file__)), "new.wav")
buf = bytearray()
size = 0

audio_input = open("/proc/audio", "rb")
bt_output = open("/proc/bluetooth", "wb")
leds = open("/proc/leds", "wb")

def get_audio_data():
  global size, buf
   
  #get new data
  audio_data = audio_input.read()

  if (len(audio_data) != 0):    
    size = size + (len(audio_data)//2)
    #reduce it to 16khz audio
    ls_bytes = audio_data[0::4]
    ms_bytes = audio_data[1::4]
    audio_16khz = bytearray(len(ls_bytes)+len(ms_bytes))
    audio_16khz[::2] = ls_bytes 
    audio_16khz[1::2] = ms_bytes
  
    # store this 16khz chunk in the buffer
    buf.extend(audio_16khz)
  return

#zero out LEDS
leds.write(b'\x00\x00')
leds.flush()

while (1):
  sleep(0.01) 
  get_audio_data()
  
  if (size  > 32000):
    data = str(buf)
    ans = detection.detector.RunDetection(data)

    if ans == 1:
      # reset the buffer complety
      #buf = bytearray()
      #size = 0
      print('Hotword Detected!')
            
      #light up
      leds.write(b'\xff\xff')
      leds.flush()

      #store data for 5 seconds
      while (size < 32000 * 4):
        sleep(0.01)
        get_audio_data()
      
      #light down
      leds.write(b'\x00\x00')
      leds.flush()

      #send data to the app
      writef = wave.open(new_file, 'w')
      writef.setparams((1, 2, 16000, 16000 * 2 * 5, "NONE", "Uncompressed"))
      writef.writeframes(buf)
      writef.close()
      writef = open(new_file, 'rb')
      buffery = bytearray()
      buffery.extend(writef.read())
      data = str(buffery)

      print ("Trying to get the lock ")
      fcntl.flock(bt_output, fcntl.LOCK_EX)
      print ("Got the lock!")
      #bt_output.write("AUDIO*")
      for i in range(0, len(data)):
        bt_output.write(data[i])
        sleep(0.00005)
      bt_output.write("$$$")
      bt_output.flush()
      fcntl.flock(bt_output, fcntl.LOCK_UN)      
    else:
      print (ans)
      # reset the buffer to the middle of previous buffer
      #buf = buf[len(buf)//2:]
      #size = len(buf)
      print('Hotword Not Detected!')
    
    #empty the buffer
    buf = bytearray()
    size = 0
    #print(size)
      




