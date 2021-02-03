// Autor: Vitor de Almeida Silva, PUC-GO
// programa feito para realiar a amostragem de um sinal de 1hz,10hz e 100hz vindo da porta analógica

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //inicializa a comunicação serial a 9600 bits por segundo
  pinMode(A0,INPUT);  //definindo a porta analógica como entrada
  pinMode(13,OUTPUT); //definido o pino 13 como entrada;
}

/*realizar amostragem de sinal 1Hz,10Hz, 100Hz
a função Delay será usada para o periodo de amostragem
delay(); é em milissegundos
P=1/F;

p - periodo
F - frequência

frequência de nikisti:

Fn= 2 * (maior componente de frequência) 

na prátia Fn = 10 * (maior componente de frequência) 

para 1Hz:

Fn=2*1=2Hz

P=1/2
P=0.5 s

Pm= 0.5*1000= 500 ms

para 10Hz

Pm=1/20*100= 50ms

para 100Hz

Pm=1/200*100=5ms

*/



void loop() {
  // put your main code here, to run repeatedly:
  int valorAD=0;

  valorAD=analogRead(A0); //realiza a leitura do valor do pino A0
  digitalWrite(13,HIGH);

  //1hz
  //delay(500);
  //10hz
  //delay(50);
  //100hz
  delay(10);
  
  //para imprimir um valor entre 0-5v é preciso fazer o calculo da proxima linha
  // a leitura analógica  vai de 0 - 1023
  float Vd= valorAD * (5.0 / 1023.0);

  
  Serial.println(Vd);
  digitalWrite(13,LOW);
  delay(1);        // essa espera é para não sobrecarrega de dados

}
