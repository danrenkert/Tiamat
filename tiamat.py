"""
 Tiamat controll 
 
 to do:
    
    test the software on a compter with the serial conected to the master arduino
    
"""
import serial
cues=[]
temp=str()
#ser = serial.Serial('USB\VID_1A86&PID_7523\5&34C8F5E4&0&7', 9600, timeout=30)
#ser = serial.Serial('USB\VID_1A86&PID_7523\5&2C705BFE&0&1', 9600, timeout=30)
print("test")
with open('test.txt', 'r') as f:
    fileheader= f.readline().rstrip("\n\r")
    print 'File ', fileheader
    NodeCount= f.readline().rstrip("\n\r")
    print NodeCount,
    print'Nodes.'
    
    for line in f:
        temp = line.rstrip("\n\r")
        cues.append(temp.encode())
        
   
maxCues=len(cues) 
""""
for item in cues:
    print(item)
print("endtest")
"""""
curentCue = -1
newCue=str()
while True:
    #get user input 
    newCue=raw_input("Enter cue number   ")
    #if they enter enter go to the next cue
    if newCue=="":
        if curentCue+1 < maxCues:
            newCue=curentCue+1
        else:
            print ("End of Show")
            newCue= curentCue
    #if they enter b go back to the last cue
    elif newCue=="b" or newCue=="B":
        if curentCue >0:
            newCue=curentCue-1
        else:
            print ("Top of Show")
            newCue= curentCue
    #otherwise pray to god tey entered a number and go to that cue
    elif newCue.isdigit() and int(newCue) > 0 and int(newCue) < maxCues+1:
        newCue=int(newCue)-1
    else:
        print(newCue, " Is not a valid cue or command.")
        newCue=curentCue
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
