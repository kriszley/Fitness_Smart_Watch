import snowboydecoder
import sys
import wave
from os import path
import fcntl
from time import sleep


buf = bytearray()
size = 0

audio_input = open("/proc/audio", "rb")
new_file = path.join(path.dirname(path.realpath(__file__)), "new.wav")

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

while (1):
  get_audio_data()
  if (size  > 32000 * 3):
    ans = 1
    writef = wave.open(new_file, 'w')
    writef.setparams((1, 2, 16000, 16000 * 2 * 5, "NONE", "Uncompressed"))
    writef.writeframes(buf)
    writef.close()
    exit()



