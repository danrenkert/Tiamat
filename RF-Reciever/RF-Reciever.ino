// SimpleRx - the slave or the receiver

#include <SPI.h> //To communicate with the nRF chip

//Documentation for libraries can be found here: http://tmrh20.github.io/RF24/
#include <nRF24L01.h> // Library from: https://github.com/nRF24/RF24
#include <RF24.h> // Library from: https://github.com/nRF24/RF24

#define CE_PIN   9
#define CSN_PIN 10

const int numRec = 14;
const byte thisSlaveAddress[5] = {'R','x','A','A','A'};
const int ID = 0; //each Arduino in the show needs a unique seqential ID.

RF24 radio(CE_PIN, CSN_PIN);

char queue[numRec]; // this must match dataToSend in the TX
bool newData = false;

//===========

void setup() {

    Serial.begin(9600);

    Serial.println("SimpleRx Starting");
    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.openReadingPipe(1, thisSlaveAddress);
    radio.startListening();
}

//=============

void loop() {
    getData();
    processData();
}

//==============

void getData() {
    if ( radio.available() ) {
        radio.read( &queue, sizeof(queue) );
        newData = true;
    }
}

void processData() {
    if (newData == true) {
        if(queue[ID] == 1){
          //TODO turn on relay
        } else if(queue[ID] == 0){
          //TODO turn off relay
        }
        newData = false;
    }
}
