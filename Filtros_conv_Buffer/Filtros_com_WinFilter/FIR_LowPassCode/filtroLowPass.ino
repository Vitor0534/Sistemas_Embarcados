#include "TimerOne.h"
#include "math.h"



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

/**************************************************************
WinFilter version 0.8
http://www.winfilter.20m.com
akundert@hotmail.com

Filter type: Low Pass
Filter model: Butterworth
Filter order: 10
Sampling Frequency: 100 Hz
Cut Frequency: 4.000000 Hz
Coefficents Quantization: float

Z domain Zeros
z = -1.000000 + j 0.000000
z = -1.000000 + j 0.000000
z = -1.000000 + j 0.000000
z = -1.000000 + j 0.000000
z = -1.000000 + j 0.000000
z = -1.000000 + j 0.000000
z = -1.000000 + j 0.000000
z = -1.000000 + j 0.000000
z = -1.000000 + j 0.000000
z = -1.000000 + j 0.000000

Z domain Poles
z = 0.793107 + j -0.091040
z = 0.793107 + j 0.091040
z = 0.777775 + j -0.032339
z = 0.777775 + j 0.032339
z = 0.823023 + j -0.150137
z = 0.823023 + j 0.150137
z = 0.870642 + j -0.199169
z = 0.870642 + j 0.199169
z = 0.932293 + j -0.236384
z = 0.932293 + j 0.236384
***************************************************************/
#define Ntap 30

float fir(float NewSample) {
    float FIRCoef[Ntap] = { 
        -0.01060021751718307400,
        -0.00699709827409038250,
        -0.00206930412680435530,
        0.00412125480620061620,
        0.01143624965147888700,
        0.01966219645488821000,
        0.02851680820194567300,
        0.03766049773050581000,
        0.04671270570706050100,
        0.05527230940058856800,
        0.06294094963841379000,
        0.06934773307586253300,
        0.07417346992997010700,
        0.07717244472048512300,
        0.07818974524268906800,
        0.07717244472048512300,
        0.07417346992997010700,
        0.06934773307586253300,
        0.06294094963841379000,
        0.05527230940058856800,
        0.04671270570706050100,
        0.03766049773050581000,
        0.02851680820194567300,
        0.01966219645488821000,
        0.01143624965147888700,
        0.00412125480620061620,
        -0.00206930412680435530,
        -0.00699709827409038250,
        -0.01060021751718307400,
        -0.01288974404133330300
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
