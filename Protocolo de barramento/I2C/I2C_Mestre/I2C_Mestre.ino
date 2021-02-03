#include <Wire.h>

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);           // start serial for output
}

byte x = 0;

void loop()
{
  Wire.beginTransmission(1); // transmit to device #4
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();    // stop transmitting

  Wire.beginTransmission(2); // transmit to device #4
  Wire.write("x is ");        // sends five bytes
  Wire.write(x+1);              // sends one byte  
  Wire.endTransmission();    // stop transmitting

  Serial.print("The master send... ");
  Serial.println(x);
  x++;
  delay(500);
  
}
