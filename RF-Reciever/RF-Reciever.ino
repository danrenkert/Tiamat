// The slave or the receiver - Built on Aruino Nano

#include <SPI.h> //This is the protocol library needed to communicate with the nRF24l01+ chip

//Documentation for libraries can be found here: http://tmrh20.github.io/RF24/
//These libraries run the radio communication for the system
#include <nRF24L01.h> // Library from: https://github.com/nRF24/RF24
#include <RF24.h> // Library from: https://github.com/nRF24/RF24


#define CE_PIN 9 //Tells the arduino which pin is attached to the CE pin of the nRF24l01+ chip
#define CSN_PIN 10 //Tells the arduino which pin is attached to the CSN pin of the nRF24l01+ chip


//====================Change this  information each show=========================//
//This variable keeps track of how many devices are in the system
//This defines the size of the array sent to the recievers
const int numRec = 14;

const int ID = 1; //each Arduino in the show needs a unique seqential ID. We are indexing starting at 1.

//===============================================================================//

//TODO: add solder connections


//This code sets up the radio pipeline
const byte slaveAddress[5] = {'R','x','A','A','A'}; // This is the pipeline all of the chips will use
RF24 radio(CE_PIN, CSN_PIN); // This creates the radio transmitter on the software side

// This is the pin the relay is attached to. It is pin A5
int pinOut = 19;

char cue[numRec+5]; //This is the character array we will recieve over the radio. Must match buff from RF-master.
bool newCue = false; //This boolean checks if there is a new cue that has been recieved

//===========
//This sets up the USB(not needed for function but useful for debugging), relay and radio.
void setup() {
    //setup usb communication
    Serial.begin(9600); //opens the usb communication
    
    pinMode(pinOut, OUTPUT); // This sets up the relay linked to pin A5

    //This code sets up the radio
    radio.begin(); //Start the radio object
    radio.setDataRate( RF24_250KBPS ); // Sets how much data we can transfer
    radio.openReadingPipe(1, thisSlaveAddress); //opens a communication pipeline to the transmitter
    radio.startListening(); //Starts listening to the pipeline
    
    //Debugging
    //Serial.write("Start");
}

//=============
//This loop runs consistently on the reciever. We wait for a cue from the radio then process it and trip the relay
void loop() {
    getData();
    processData();
}

//==============
//If the radio has data we get it and set newCue to true
void getData() {
    if ( radio.available() ) {
        radio.read( &cue, sizeof(cue) );
        newCue = true;
    }
}

//==============
//If data is recived we check the number corresponding to the ID of the reciever and set the relay accordingly.
void processData() {
    if (newCue == true) {
      Serial.print(cue[ID-1]); //Debugging
        if(cue[ID-1] == '1'){ // If the ID in the cue is 1 we turn on the lights
          digitalWrite(pinOut, HIGH);
        } else if(cue[ID-1] == '0'){ // If it is 0, we turn them off
          digitalWrite(pinOut, LOW);
        }
        newCue = false;
    }
}
