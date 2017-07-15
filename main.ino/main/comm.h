#ifndef COMM_h
#define COMM_h
#include "Arduino.h"
void initCan(void);
void ReceiveMessage(void  *pvParameters );
void sendMessage(void  *pvParameters );
void testCan(void  *pvParameters );
void deliverMessage(void) ;
extern int csValue, imdFail, csFail;  // these values are read by tasks that reside at this node.
extern int teValue; // values send from far node/s
extern unsigned char messageToSend[8], messageReceived[8];
#endif
