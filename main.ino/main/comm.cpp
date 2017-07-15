#include <Arduino_FreeRTOS.h>
#include <SPI.h>
#include "mcp_can.h"

#include "comm.h"
#include "tE.h"

// var to test the can bus 
int noMessageRecievedCount = 0; // count will be increment whenever we do not receive message and reset when we receive one.
const int MAXCOMMDOWNTIME = 10; // if above count did reach this constant controller should indicate fault.
bool isCanFail = true;
int canFaultPin = 8; // this pin will go high in case of can fault

// var to handle sending and receiving of the message
unsigned char messageToSend[8] = {1, 2, 3, 4, 5, 6, 7, 8};
unsigned char messageToReceive[8] = {0, 0, 0, 0, 0, 0, 0, 0};
const int Id = 1; // Back controller Id 
unsigned char len = 0; // message length;

// var to hold sensor values
int csValue, imdFail, csFail;  // these values are read by tasks that reside at this node.
int teValue; // values send from far node/s

// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void initCan(void) {
  pinMode(canFaultPin, OUTPUT);
  Serial.begin(115200);
  Serial.println("start initializing can");
  Serial.println(CAN.begin(CAN_500KBPS));
  while (CAN_OK != CAN.begin(CAN_500KBPS))              // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(100);
        noMessageRecievedCount++;

    }
   Serial.println("CAN BUS Shield init ok!");
}

/**
 * This method recieve the aggregated message send from other node/s
 */
void ReceiveMessage(void) {
    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
      CAN.readMsgBuf(&len, messageToReceive);    // read data,  len: data length, buf: data buf
      noMessageRecievedCount = 0;
    }
    else {
      noMessageRecievedCount++;
    }
}

/** 
 *  This method send an aggregated message from this end to other node/s 
 */
void sendMessage(void) {
  messageToSend[0] = apps;
  Serial.println("sending message");
  CAN.sendMsgBuf(Id,0, 8, messageToSend);
}

/**
 * A method to test can bus communication
 * This method works like ping testing connectivity between two nodes. 
 */
void testCan(void  *pvParameters ) {
  for (;;) {
   Serial.begin(115200);
   Serial.println("-----------------------------");
   sendMessage();
   vTaskDelay(5);
   ReceiveMessage();
   vTaskDelay(5);
   deliverMessage();
   if(noMessageRecievedCount <=  MAXCOMMDOWNTIME ) {
    isCanFail = false;
    digitalWrite(canFaultPin, LOW);
   } 
   else {
   digitalWrite(canFaultPin, HIGH);
    isCanFail = true;
   }
  } 
}

/**
 * A method to separate the message and set the values of the external variable accordingly
 */
void deliverMessage(void){
  unsigned char canId = CAN.getCanId();

        Serial.println("-----------------------------");
        Serial.println("get data from ID: ");
        Serial.println(canId);

        for(int i = 0; i<len; i++)    // print the data
        {
            Serial.print(messageToReceive[i]);
            Serial.print("\t");
        }
        Serial.println();
}

