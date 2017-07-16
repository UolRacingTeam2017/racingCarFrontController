#include <Arduino_FreeRTOS.h>
#include "tE.h"

int apps = 0;
int bse = 0;
int apps1 = 0;
int apps2 = 0;

int apps1Pin = 0; 
int apps2Pin = 1;
int bsePin = 3;

void readPots( void *pvParameters ){
  (void) pvParameters;
  static bool TEFLAG;
  TEFLAG = false;
  
  for(;;) {
    apps1 = analogRead(apps1Pin);
    apps2 = analogRead(apps2Pin);
    bse = analogRead(bsePin);
    int diff = abs(apps1 -apps2);
    
    if (TEFLAG) {
      delay(100);
    }
    if (diff > 102 && TEFLAG) {
      apps = 0; 
    } else if (diff > 102 && !TEFLAG) {
      TEFLAG = true; 
      apps = map(apps1, 0, 1024, 0, 255);
    } else {
      apps = map(apps1, 0, 1024, 0, 255);
      TEFLAG = false;
    }
  }
}


