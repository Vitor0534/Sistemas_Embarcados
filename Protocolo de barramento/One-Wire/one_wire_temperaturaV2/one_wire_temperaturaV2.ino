#include <OneWire.h>

OneWire  ds(2);  // pino 2


void setup(void) {
   Serial.begin(9600);
}


void loop(void) {
  byte data[9];
  int temp;
  
  ds.reset();//sinal de reset
  ds.write(0xCC);//skip rom
  ds.write(0x44);//inicia conversão de temperatura
  delay(750);//espera 750ms para calcular a temperatura
  ds.reset();//sinal de reset
  ds.write(0xCC);//skip rom
  ds.write(0xBE);//inicia a leitura do scratchpad ( 9 bytes )

  //Leitura
  for (byte i = 0; i < 9; i++) {
    data[i] = ds.read();
  }
  

  if((data[1]>>7)==1){//verifica se a temperatura é negativa
      data[1] = ~data[1];
      data[0] = (~data[0]) + 1;
      Serial.print("-"); 
    }
    else{
      Serial.print("+"); 
    }
    temp = (data[1]<<4) | (data[0]>>4);
    Serial.print(temp);
    Serial.print(".");
    temp = (data[0] & 0x0F) * 625;
    if(temp>625){
      Serial.print(temp);
    }
    else{
      Serial.print("0");
      Serial.print(temp);
    }
  Serial.print(" ");
  Serial.write(223);//imprime o caracter (°)
  Serial.println("C    ");
}
