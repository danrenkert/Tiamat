// SimpleTx - the master or the transmitter
#include <SPI.h> //To communicate with the nRF chip

//Documentation for libraries can be found here: http://tmrh20.github.io/RF24/
#include <nRF24L01.h> // Library from: https://github.com/nRF24/RF24
#include <RF24.h> // Library from: https://github.com/nRF24/RF24


#define CE_PIN 9
#define CSN_PIN 10

/*
 *  GND - GND
 *  13 - SCK
 *  12 - MISO
 *  11 - MOSI
 *  8 - CSN
 *  7 - CE
 *  3.3 - Vcc
 */

//How many devices
const int numRec = 14;

//Radio Stuff
const byte slaveAddress[5] = {'R','x','A','A','A'};
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

//How we are sending stuff
String dataToSend = "";// = {'1','0','0','0','0','0','0','0','0','0','0','0','0','0'};
bool queue = false;


void setup() {
    //setup usb communication
    Serial.begin(9600);
    dataToSend.reserve(14);
    
    pinMode(7,OUTPUT);

    //Serial.println("SimpleTx Starting");

    radio.begin();
    radio.setPALevel(RF24_PA_MAX);
    radio.setDataRate( RF24_250KBPS );
    radio.openWritingPipe(slaveAddress);
}

//====================

void loop() {
    if(queue){
      send();
      dataToSend = "";
      queue = false;
    }
}

//====================

void send() {

    bool rslt;
    rslt = radio.write( &dataToSend, sizeof(dataToSend) );
        // Always use sizeof() as it gives the size as the number of bytes.
        // For example if dataToSend was an int sizeof() would correctly return 2

    //Serial.print("Data Sent ");
    Serial.print(dataToSend);
    if (rslt) {
        digitalWrite(7,HIGH);
        //delay(1000);
        digitalWrite(7,LOW);
    }
}

//=====================

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    dataToSend += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      queue = true;
    }
  }
}
