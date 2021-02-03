#include <Arduino_FreeRTOS.h>
//#include <FreeRtOSConfig.h>
//#include "FreeRTOS.h"
//#include <task.h>
//#include <croutine.h>



//define four tasks for Blink & Serial write "task N"
void SeguirFrente( void *pvParameters );
void marchaRe( void *pvParameters );
void VirarEsquerda( void *pvParameters );
void VirarDireita( void *pvParameters );
#define total 15

int verificaFrente = 0;
int Metros = 0;

/* roteiro:
    2m  ---- direita
    2m  ---- direita
*/

/*xTaskGetHandle TaskHandle_1;
xTaskHandle TaskHandle_2;
xTaskHandle TaskHandle_3;
xTaskHandle TaskHandle_4;
xTaskHandle TaskHandle_5;
*/
//the setup function runs once when you press reset or power the board
void setup() {

  // initialize digitalas output.
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9 , OUTPUT);


  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  // Now set up two tasks to run independently.
  xTaskCreate(
    SeguirFrente
    ,  (const portCHAR *)"SeguirFrente"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 0 (configMAX_PRIORITIES - 1) being the highest, and 3 being the lowest.
    ,  NULL );

//  xTaskCreate(
//    marchaRe
//    ,  (const portCHAR *) "marchaRe"
//    ,  128  // Stack size
//    ,  NULL
//    ,  0  // Priority
//    ,  NULL );

//  xTaskCreate(
//    VirarEsquerda
//    ,  (const portCHAR *) "VirarEsquerda"
//    ,  128  // Stack size
//    ,  NULL
//    ,  0  // Priority
//    ,  NULL );

  xTaskCreate(
    VirarDireita
    ,  (const portCHAR *) "VirarDireita"
    ,  128  // Stack size
    ,  NULL
    ,  3  // Priority
    ,  NULL );


  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}


void irParaFrente(int temp)
{
  //aciona motores no sentido orário
  Serial.print("SeguirFrente ");
  Serial.println(temp / 1000);
  digitalWrite(12, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(9 , HIGH);
  //vTaskDelay( temp / portTICK_PERIOD_MS );
}

void virarEsquerda()  //vira o carro para a esquerda, isso leva 0.1s
{
  Serial.println("virando a esquerda");
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9 , HIGH);
  //vTaskDelay( 100 / portTICK_PERIOD_MS );
  delay(100);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9 , LOW);
  //vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for temp second
}

void virarDireita(double temp)  //vira o carro para a direita, isso leva 0.1s
{
  Serial.println("virando a direita");
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9 , HIGH);
 // vTaskDelay( 1000 / portTICK_PERIOD_MS );
}

void irParaTras(int temp)
{

  //aciona motores no sentido antorario
  Serial.print("marcha ré ");
  Serial.println(temp / 1000);

  digitalWrite(12, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(9 , LOW);
 // delay(temp);
  //vTaskDelay( temp / portTICK_PERIOD_MS ); // wait for temp second

  //desliga os motores
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9 , LOW);
  //vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for temp second
  
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void SeguirFrente (void *pvParameters)  // This is a task.
{
  (void) pvParameters;


  for (;;) // A Task shall never return or exit.
  {
   // if (Metros != total) { //verifica se o percurso acabou

     // if (verificaFrente == 0)
      //{
        irParaFrente(2000);
       // verificaFrente = 1;
        Metros++;             //conta-se os metros para ter controle do percurso
        vTaskDelay( 2000 / portTICK_PERIOD_MS );
        
      // vTaskSuspend(SeguirFrente);  //supende a execução da task  to wait
      //}
      //else
      //{
       // if (Metros == 4)
       // {
         // irParaFrente(6000); //neste momento ele realiza o maior caminho
        //  Metros += 6;
          
          //vTaskSuspend(SeguirFrente);  //supende a execução da task  to wait
       // }
        //else{
        // irParaFrente(2000);
        //  verificaFrente = 0;
        //  Metros += 2;

//          vTaskSuspend(SeguirFrente);  //supende a execução da task  to wait
       // }
         
     // }
       //vTaskSuspend(&TaskHandle_1);
       //vTaskResume(&TaskHandle_2);
   // }
  }
}

//void marchaRe(void *pvParameters)  // This is a task.
//{
//  (void) pvParameters;
//
//for (;Metros != total;) // A Task shall never return or exit.
//  {
//    
//    if (Metros == 14)
//    {
//      irParaTras(1000);
//    }
//    
//  }
//
//}

//void VirarEsquerda(void *pvParameters)  // This is a task.
//{
//  (void) pvParameters;
//
//  for (;Metros != total;) // A Task shall never return or exit.
//  {
//    //virarEsquerda();
//    //vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for temp second
//  }
//
//}

void VirarDireita(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;) // A Task shall never return or exit.
  {
   // if (Metros == 1 && Metros == 3 && Metros == 4 && Metros == 10 && Metros == 11
       // && Metros == 13){
         // if(verificaFrente ==0)
                 virarDireita(1000);
                 vTaskDelay( 1000 / portTICK_PERIOD_MS );
          //else 
              //   virarDireita(2002);

         // vTaskSuspend(&TaskHandle_2);
          //vTaskResume(&TaskHandle_1);
  
    }
  //}
}
