#ifndef COMM_h
#define COMM_h
#include "Arduino.h"
void initCan(void);
void ReceiveMessage(void  *pvParameters );
void sendMessage(void  *pvParameters );
void testCan(void  *pvParameters );
void deliverMessage(void) ;
#endif

