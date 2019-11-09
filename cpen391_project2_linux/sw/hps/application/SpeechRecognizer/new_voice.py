import snowboydecoder
import sys
#import wave
from os import path
import fcntl
from time import sleep
from threading import Thread
import Queue
##"resources/DEWatch.pmdl")
model_file = path.join(path.dirname(path.realpath(__file__)),"resources/alexa_02092017.umdl") 
sensitivity = 0.5
detection = snowboydecoder.HotwordDetector(model_file, sensitivity=sensitivity, audio_gain=1.5)

audio_input = open("/proc/audio", "rb")
bt_output = open("/proc/bluetooth", "wb")
leds = open("/proc/leds", "wb")

q = Queue.Queue()

def get_audio_data():   
  #get new data
  audio_data = audio_input.read()

  if (len(audio_data) != 0):
    #reduce it to 16khz audio
    ls_bytes = audio_data[0::4]
    ms_bytes = audio_data[1::4]
    audio_16khz = bytearray(len(ls_bytes)+len(ms_bytes))
    audio_16khz[::2] = ls_bytes 
    audio_16khz[1::2] = ms_bytes
    return audio_16khz
  else:
    return bytearray()

def lights_on():
  leds.write(b'\xff\xff')
  leds.flush()
  return

def lights_off():
  leds.write(b'\x00\x00')
  leds.flush()
  return

def save_X_sec():
  lights_on()
  size = 0
  while (size < 32000 * 4):
    buf = get_audio_data()
    if (len(buf) > 0):  
      size += len(buf)
      data = str(buf)
      q.put(data)
  
  lights_off()
  return

def send_X_sec():
  size = 0
  while (size < 32000 * 4):
    if (not q.empty()):
      data = q.get()
      size += len(data)
      for i in range(0, len(data)//50):
        bt_output.write(data[50*i:50*(i+1)])
        sleep(0.003)
      if (len(data)%50 > 0):
        bt_output.write(data[-len(data)%50:])
  return   


#main
lights_off()
buf = bytearray()

while (1):
  sleep(0.01) 
  buf.extend(get_audio_data())
  
  if (len(buf)  > 32000):
    data = str(buf)
    ans = detection.detector.RunDetection(data)

    if ans == 1:
      print('Hotword Detected!')
      fcntl.flock(bt_output, fcntl.LOCK_EX)
      print ("Got the lock!")
      
      #start storing the data
      saver = Thread(target=save_X_sec)
      saver.start()

      #start sending the data as well
      sender = Thread(target=send_X_sec)
      sender.start()
      
      #join both threads
      saver.join()
      sender.join()
      
      #send the end indicator
      bt_output.write("$$$")
      bt_output.flush()
      fcntl.flock(bt_output, fcntl.LOCK_UN)
      
      lights_on()
      sleep(0.5)
      lights_off()      
    
    else:
      print (ans)
      print('Hotword Not Detected!')
    
    #empty the buffer
    buf = bytearray()

      




