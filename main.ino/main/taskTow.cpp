#include <Arduino_FreeRTOS.h>
#include "taskTwo.h"

void TaskTwo(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize digital pin 12 as an output.
  pinMode(12, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 3000 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 3000 / portTICK_PERIOD_MS ); // wait for one second
  }
}
