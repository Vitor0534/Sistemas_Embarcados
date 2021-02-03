#include <Arduino_FreeRTOS.h>

// define four tasks for Blink & Serial write "task N"
void Task1( void *pvParameters );
void Task2( void *pvParameters );
void Task3( void *pvParameters );
void Task4( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  // Now set up two tasks to run independently.
  xTaskCreate(
    Task1
    ,  (const portCHAR *)"Blink"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    Task2
    ,  (const portCHAR *) "AnalogRead"
    ,  128  // Stack size
    ,  NULL
    ,  2  // Priority
    ,  NULL );

 xTaskCreate(
    Task3
    ,  (const portCHAR *) "AnalogRead"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

xTaskCreate(
    Task4
    ,  (const portCHAR *) "AnalogRead"
    ,  128  // Stack size
    ,  NULL
    ,  3  // Priority
    ,  NULL );


  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void Task1(void *pvParameters)  // This is a task.
{
  (void) pvParameters;


  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(13, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {

    Serial.println("Task 1");
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
  }
}

void Task2(void *pvParameters)  // This is a task.
{
  (void) pvParameters;


  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(12, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {

    Serial.println("Task 2");
    digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for one second
  }
}
void Task3(void *pvParameters)  // This is a task.
{
  (void) pvParameters;


  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(11, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {

    Serial.println("Task 3");
    digitalWrite(11, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(11, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for one second
  }
}

void Task4(void *pvParameters)  // This is a task.
{
  (void) pvParameters;


  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(10, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {

    Serial.println("Task 4");
    digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(10, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
  }
}
