// SimpleTx - the master or the transmitter

#include <KeyboardController.h>

#include <SPI.h> //To communicate with the nRF chip

//Documentation for libraries can be found here: http://tmrh20.github.io/RF24/
#include <nRF24L01.h> // Library from: https://github.com/nRF24/RF24
#include <RF24.h> // Library from: https://github.com/nRF24/RF24


#define CE_PIN   7
#define CSN_PIN 8

/*
 *  GND - GND
 *  13 - SCK
 *  12 - MISO
 *  11 - MOSI
 *  8 - CSN
 *  7 - CE
 *  3.3 - Vcc
 */

const int numRec = 14;
const byte slaveAddress[5] = {'R','x','A','A','A'};


RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

char dataToSend[numRec];
char txNum = '0';


void setup() {

    Serial.begin(9600);

    Serial.println("SimpleTx Starting");

    radio.begin();
    radio.setPALevel(RF24_PA_MAX)
    radio.setDataRate( RF24_250KBPS );
    radio.openWritingPipe(slaveAddress);
}

//====================

void loop() {
    if( Serial.available() > 0){
      char inChar = Serial.read();
      if (inChar == 'n' || inChar == 'N'){
        //TODO step to next queue
      }else if(inChar == 'b' || inChar == 'B'){
        //TODO step back a queue
      }else if(inChar == 'j' || inChar == 'J'){
        //TODO prompt a number and jump to queue
      }
    }
}

//====================

void send() {

    bool rslt;
    rslt = radio.write( &dataToSend, sizeof(dataToSend) );
        // Always use sizeof() as it gives the size as the number of bytes.
        // For example if dataToSend was an int sizeof() would correctly return 2

    Serial.print("Data Sent ");
    Serial.print(dataToSend);
    if (rslt) {
        Serial.println("Sent");
    }
    else {
        Serial.println("  Tx failed");
    }
}
