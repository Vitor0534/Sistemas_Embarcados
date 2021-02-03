#include <Wire.h>
#define Slave1 200
#define Slave2 100
#define pin1 12


void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);           // start serial for output
}

byte x = 0;


void loop()
{

  Serial.print("O mestre envia ");
  Serial.print(Slave1);
  Serial.println("ms para o escravo 1 ");
 // x++;
  Wire.beginTransmission(1);     // transmite para o 1
  Wire.write("Tempo=  ");        // envia 5 bytes 
  Wire.write(Slave1);            // envia 1 byte 
  Wire.endTransmission();        // encerra a transmissão

  delay(Slave1 + 100);           //delay para aguardar o uso do recurso pelo slave

  Serial.print("O mestre envia ");
  Serial.print(Slave2);
  Serial.println("ms para o escravo 2 ");
  
  Wire.beginTransmission(2);     //transmite para 2
  Wire.write("Tempo=  ");        
  Wire.write(Slave2);               
  Wire.endTransmission();    

  delay(Slave2 + 100);
  
}
