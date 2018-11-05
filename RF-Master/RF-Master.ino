// Master or the transmitter - Built on an arduino UNO

#include <SPI.h> //This is the protocol library needed to communicate with the nRF24l01+ chip

//Documentation for libraries can be found here: http://tmrh20.github.io/RF24/
//These libraries run the radio communication for the system
#include <nRF24L01.h> // Library from: https://github.com/nRF24/RF24
#include <RF24.h> // Library from: https://github.com/nRF24/RF24


#define CE_PIN 9 //Tells the arduino which pin is attached to the CE pin of the nRF24l01+ chip
#define CSN_PIN 10 //Tells the arduino which pin is attached to the CSN pin of the nRF24l01+ chip

//TODO: change from pin number to pin lable
/*  Arduino   -   nRF24l01+
 *  GND       -   GND
 *  13        -   SCK
 *  12        -   MISO
 *  11        -   MOSI
 *  8         -   CSN
 *  7         -   CE
 *  3.3       -   Vcc
 */

//This variable keeps track of how many devices are in the system
//This defines the size of the array sent to the recievers
const int numRec = 14;

//This code sets up the radio pipeline
const byte slaveAddress[5] = {'R','x','A','A','A'}; // This is the pipeline all of the chips will use
RF24 radio(CE_PIN, CSN_PIN); // This creates the radio transmitter on the software side

// This code define the communication protocol
String dataToSend = ""; //This is the string we will use to read cue from the USB cable
char buff[numRec+5]; //This is the character array we will send over the radio
bool cue = false; //This boolean checks if there is a cue to be sent out

//====================
//This sets up the USB, light and radio
void setup() {
    //setup usb communication
    Serial.begin(9600); //opens the usb communication
    dataToSend.reserve(numRec); //We reserve space for the String read from the USB in memory
    
    pinMode(7,OUTPUT); // This sets up a test light linked to pin 7 of the UNO. Not required for functionality

    //This code sets up the radio
    radio.begin(); //Start the radio object
    radio.setPALevel(RF24_PA_MAX); //Sets how powerful our signal is
    radio.setDataRate( RF24_250KBPS ); // Sets how much data we can transfer
    radio.openWritingPipe(slaveAddress); //opens a communication pipeline to the recievers
}

//====================
//This loop runs consistently on the transmitter. We wait for a cue from the USB then send it to the recievers
void loop() {
    if(cue){
      send();
      dataToSend = "";
      cue = false;
    }
}

//====================
// This is the code to send out the cue read from the USB
void send() {

    bool rslt; //This checks if the tranmission succeeded
    rslt = radio.write( &buff, sizeof(buff) ); //Sends the message

    Serial.print(dataToSend); //sends what we transmitted back along the USB

    //If we succeed we turn on the light on pin 7 for 1 second
    if (rslt) {
        digitalWrite(7,HIGH);
        //delay(1000);
        digitalWrite(7,LOW);
    }
}

//=====================
//This runs after each loop. It collects information from the USB and makes it possible to transmit
void serialEvent() {
  while (Serial.available()) { // While there is information from the USB
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to dataToSend:
    dataToSend += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it
    if (inChar == '\n') {
      cue = true;
    }
  }
  //When we finish reading data convert the string to a character array
  //so the radio can send it.
  dataToSend.toCharArray(buff, sizeof(buff));
}
