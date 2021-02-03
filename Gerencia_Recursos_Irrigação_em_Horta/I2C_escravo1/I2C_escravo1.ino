#include <Wire.h>
#define pin1 12


void setup()
{
  Wire.begin(1);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  pinMode(pin1 , OUTPUT);
}

//---
int s = 0; //variável que controla o momento de utilizar o recurso
int tempo = 0;  //tempo que será recebido do mestre para utilizar o recurso 

void loop()
{
  //delay(100);
  // --- if de controle do recurso
  if (s == 1){   
    usarLed();
    s = 0;
    tempo=0; 
  }
  
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()


//void usarLed(int tempo)
void usarLed()
{
  digitalWrite(pin1 , HIGH);
  delay(tempo);
  digitalWrite(pin1 ,LOW);
  delay(tempo);
}


void receiveEvent(int howMany)
{
  //delay (100);
  
  Serial.print("escravo 1: ");
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  //Serial.print("slave response: ");
  Serial.print(x);         // print the integer
  Serial.println("ms "); 

  //usarLed(x);

  // ---
  s = 1;  //seta uso do recurso
  tempo = x;  //tempo de uso do recurso
  
}
