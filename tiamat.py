"""
 Tiamat control
 
 This program needs a file named 'cues.txt' in the same directory to function
 It reads in the cues (see README.md for formatting fo 'cues.txt').

 If 'enter' is hit it steps to the next cue,
 If 'b' is hit it steps back a cue,
 If a number is entered it jumps to that cue.
    
"""
import serial
import os
from time import sleep

cues=[]
temp=str()

#clears the screen when called
def cls():
    os.system('cls' if os.name=='nt' else 'clear')

#This serial port will need to be updated based on the laptop running the program
ser = serial.Serial('COM4',9600,timeout=0)  # open serial port

#Debugging
#print(ser.name)
cls()
print("Begining Tiamat Light Software")
print("Loading 'cues.txt'. Please wait.")

#Open's cues file as read only
lineNum = 1
with open('cues.txt', 'r') as f:
    fileheader = f.readline().rstrip("\n\r") #pulls out the header and verifies it.
    if(fileheader != "5H"):
        print('File ', fileheader)
        raise Exception("File format is incorrect")
    
    lineNum = lineNum + 1
    NodeCount= f.readline().rstrip("\n\r") #gets number of recievers in the show. Must match numRec in Arduinos
    print("This file lists " + NodeCount + " recievers in this show.")
    verify = input("Is this correct? (Y/n)")
    if(verify == 'n' or verify == 'N'):
        raise Exception("Please fix 'cues.txt'")
    cls()

    #Read in all the cues
    
    for line in f:
        lineNum = lineNum + 1
        temp = line.rstrip("\r").split(",") # we split apart the desciption and the cue
        #print(type(len(temp))) #debugging
        if(len(temp[1]) - 1 == int(NodeCount)):
            cues.append([temp[0],temp[1].encode()])
        else:
            print("Line " + str(lineNum) + " is size: " + str(len(temp[1])-1) + ". Expected: " + str(NodeCount))
            print("Description: " + temp[0])
        
input("Please review errors. Press 'Enter' when done...")

#Total numbe rof cues 
maxCues=len(cues)

#pad the end of the show with a final shutdown cue
end = ''.join(['0' for i in range(int(NodeCount))]).encode()
cues.append(["End of show", end])

#initialize needed variable
curentCue = 0
newCue=str()
endOfShow = False

print("Welcome to the show.")
print("You have access to the following commands: ")
print("'Enter' - moves you forward 1 cue")
print("'b' - moves you backward 1 cue")
print("'q'- exits the program if you are at the end of the show")
print("{any number} - takes you to that cue number")
print("")
print("Alright, on with the show.")
input("press Enter ...")
cls()

while True:
    #get user input
    print("Current cue: " + str(curentCue + 1) + " - " + cues[curentCue][0])
    print("Next cue description: " + cues[curentCue+1][0])
    newCue=input("Enter a command: ")
    cls()
    #if they enter enter go to the next cue
    if newCue=="":
        if curentCue+1 < maxCues:
            newCue=curentCue+1
        else:
            print ("End of Show")
            endOfShow = True
            newCue= curentCue
    #if they enter b go back to the last cue
    elif newCue=="b" or newCue=="B":
        if curentCue >0:
            newCue=curentCue-1
        else:
            print ("Top of Show")
            newCue = curentCue
    #otherwise pray to god they entered a number and go to that cue
    elif newCue.isdigit() and int(newCue) > 0 and int(newCue) < maxCues+1:
        newCue=int(newCue)-1
    elif endOfShow == True and (newCue == 'Q' or newCue == 'q'):
        exit
    else:
        print(newCue, " Is not a valid cue or command.")
        newCue=curentCue

    #set the current cue to the actual current cue
    curentCue=newCue
    
    #write cue to the USB
    ser.write(cues[int(newCue)][1])
    sleep(1) #wait 1 second

    #Debugging
    #print("Read: ")
    #print(ser.readline())






"""

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

