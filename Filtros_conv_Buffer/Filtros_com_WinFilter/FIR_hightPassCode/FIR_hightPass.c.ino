#include "TimerOne.h"
#include "math.h"
#define Ntap 31


//implementação de buffer circular utilizando o software winFilter
/*
   o buffer circular vai sobrescrever os valores conforme avança as posições
   se pos==maximo então pos=0
   dessa forma ele volta do início do vetor e continua o ciclo
*/


#define tamBuffer 4

double bufferCircular[tamBuffer];
int pos;  //posição da amostra atual
int veri=0;
double anterior=0;
// vetor de coeficiêntes do filtro
const int tam=4;


const unsigned char PS_16 = (1 << ADPS2);  //linha 5 tabela  clock 1Mhz    clock=1Mhz            50khz amostras
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0); //linha 6 tabela  clock=500 khz   31khz amostras
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1); //linha 7 tabela  clock=250khz    16Khz amostra
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // linha 8 tabela  clock=padrão = 8600Hz amostra
//estas atribuições são concatenações de valores


//Filtro FIR hight pass 100HzFs--4HzFc
float fir(float NewSample) {
    float FIRCoef[Ntap] = { 
        -0.00361882943579113670,
        -0.00591778040953374900,
        -0.00667639094116757780,
        -0.00467073450872546560,
        0.00072768950305848355,
        0.00895555407848293810,
        0.01787081344548056100,
        0.02382931067886822100,
        0.02238972980746851300,
        0.00961210020006860420,
        -0.01635233532722765700,
        -0.05392250380218901300,
        -0.09762958634784024700,
        -0.13899161330275908000,
        -0.16870581897300346000,
        0.81822187759353004000,
        -0.16870581897300346000,
        -0.13899161330275908000,
        -0.09762958634784024700,
        -0.05392250380218901300,
        -0.01635233532722765700,
        0.00961210020006860420,
        0.02238972980746851300,
        0.02382931067886822100,
        0.01787081344548056100,
        0.00895555407848293810,
        0.00072768950305848355,
        -0.00467073450872546560,
        -0.00667639094116757780,
        -0.00591778040953374900,
        -0.00361882943579113670
    };

    static float x[Ntap]; //input samples
    float y=0;            //output sample
    int n;

    //shift the old samples
    for(n=Ntap-1; n>0; n--)
       x[n] = x[n-1];

    //Calculate the new output
    x[0] = NewSample;
    for(n=0; n<Ntap; n++)
        y += FIRCoef[n] * x[n];
    
    return y;
}



void setup() {
  Serial.begin(9600);

  //configura o preescaler do ADC
  ADCSRA &= ~PS_128;  //limpa configuração da biblioteca do arduino

  //valores possiveis de prescaler só deixar a linha com prescaler desejado
  //PS_16, PS_32, PS_64 or PS_128
  //ADCSRA |= PS_128; // 128 prescaler
  //ADCSRA |= PS_64; // 64 prescaler
  //ADCSRA |= PS_32; // 32 prescaler
  //ADCSRA |= PS_16; // 16 prescaler
  //pega a interrupção lançada pelo bit aden do ADCSA
  //ADCSRA |= ( 1 << ADSC);
  //ADCSRA |= ( 1 << ADIE);

  //int oldSREG = SREG;
  //cli(); // Disable interrupts for 16 bit register access
  //SREG = oldSREG;

  //attachInterrupt(digitalPinToInterrupt(ADIF),callback, CHANGE);
  //attachInterrupt(ADIF,callback, CHANGE);


  //como eu não consegui gerar uma interrupção usando os bits do proprio ADCSRA com o SREG
  //optei por combinar a interrupção do timer 1 juntamente com a mudança de clock do A/D
  //para começar incio o ADC com clock padrão

  Timer1.initialize(10000); // Inicializa o Timer1 e configura para um período de 0,1 segundos   (parametro é dado em micro segundos  1*10^(-6)s)

  /*exemplo:
     para um sinal de 1Hz a frequência de Niquist seria 1/2 segundos
     porem na pratica esse valor não é suficiente por isso aumentados de 2, para 10 vezes a maior freq do sinal para as amostras logo
     a freqN para um sinal de 1Hz é 1/10 seg, ou 0,1 segundos   ( timer1.initialize(100000))
  */

  Timer1.attachInterrupt(callback); // Configura a função callback() como a função para ser chamada a cada interrupção do Timer1
  pinMode(A0, INPUT);


}


void callback()
{

  float  valorAD = analogRead(A0);     //lé o valor de entrada no pino A0
  float Vd = valorAD * (5.0 / 1023.0); //faz o caluclo para que o valor seja mostrado entre 0 e 5 volts

  
 // Serial.println(Vd);

  //Serial.println(String(fir(Vd),6));
  Serial.println(fir(Vd),6);
  
}






void loop() {

}
