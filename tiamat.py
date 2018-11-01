"""
 Tiamat controll 
"""
import serial
cues=[]
temp=str()
#ser = serial.Serial('USB\VID_1A86&PID_7523\5&34C8F5E4&0&7', 9600, timeout=30)
ser = serial.Serial('USB\VID_1A86&PID_7523\5&2C705BFE&0&1', 9600, timeout=30)
print("test")
with open('test.txt', 'r') as f:
    for line in f:
        temp = line
        print (temp)
        cues.append(temp)
        
   
     
for item in cues:
    print(item)
    print("\n")
print("endtest")

curentCue = 1


newCue=input("Enter cue number")
print(cues[newCue])
ser.write(cues[newCue])






""""

these notes are just part of a old project i did that was similar to this. hopefuly it helps

# read comands from comand file
ser = serial.Serial()#'/dev/ttyACM0', 9600, timeout=30)
if command == "LEAK":
   
    print("checking for leaks")
    ser.write(b'LEAK')
    responce = ser.readline()
    if len(responce) < 1:
        responce = "ERROR"
    f = open('responce.txt','w')
    f.write(responce)
    f.close()
elif command == "TEST":
    ser = serial.Serial()#'/dev/ttyACM0',9600, timeout=30)
    print ("checking that all sensors are good")
    ser.write(b'TEST')
    responce = ser.readline()
    if len(responce) < 1:
        responce = "ERROR"
    f = open('responce.txt','w')
    f.write(responce)
    f.close()
"""
