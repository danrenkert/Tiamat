"""
 Tiamat controll 
 
 to do:
    add tstign to make sure user inputs a valid input
    make sure a cue exists, dont let it fail if the cue does not exists
    test the software on a compter with the serial conected to the master arduino
    
"""
import serial
cues=[]
temp=str()
#ser = serial.Serial('USB\VID_1A86&PID_7523\5&34C8F5E4&0&7', 9600, timeout=30)
#ser = serial.Serial('USB\VID_1A86&PID_7523\5&2C705BFE&0&1', 9600, timeout=30)
print("test")
with open('test.txt', 'r') as f:
    for line in f:
        temp = line
        cues.append(temp)
        
   
     
for item in cues:
    print(item)
print("endtest")

curentCue = -1
newCue=str()
while True:
    #get user input 
    newCue=raw_input("Enter cue number   ")
    #if they enter enter go to the next cue
    if newCue=="":
       newCue=curentCue+1
    #if they enter b go back to the last cue
    elif newCue=="b" or newCue=="B":
        newCue=curentCue-1
    #otherwise pray to god tey entered a number and go to that cue
    else:
        newCue=int(newCue)-1
        
    #print the current cue for testing 
    print(cues[int(newCue)])
    #set the current cue to the actual current cue
    curentCue=newCue
    
    #write to serial out the cue, this will have to be uncommented once its acutaly used
    #ser.write(cues[int(newCue)])






""""

everythign below here is from another project i did similar to this it might help


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
