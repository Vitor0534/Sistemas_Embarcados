#include "TimerOne.h"
#include "math.h"


//implementação de buffer circular
/*
   o buffer circular vai sobrescrever os valores conforme avança as posições
   se pos==maximo então pos=0
   dessa forma ele volta do início do vetor e continua o ciclo
*/


#define tamBuffer  10
double bufferCircular[tamBuffer];
int pos;  //posição da amostra atual




unsigned long tempo_inicio;

unsigned long tempo_fim;

unsigned long valor;



//variáveis para controlar o numero de amostras

int cont;
int qtdAmostras;
int veri = 0;         //variável que indica o término da amostragem
double V2[100];       //vetor que irá receber as amostras
int veri2 = 0;




const unsigned char PS_16 = (1 << ADPS2);  //linha 5 tabela  clock 1Mhz    clock=1Mhz            50khz amostras
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0); //linha 6 tabela  clock=500 khz   31khz amostras
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1); //linha 7 tabela  clock=250khz    16Khz amostra
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // linha 8 tabela  clock=padrão = 8600Hz amostra
//estas atribuições são concatenações de valores



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



  //insira aqui a quantidade de amostras que se deseja coletar
  qtdAmostras = 50;
  cont = 0;
  veri = 0; //variável que indica o término da amostragem

}

void callback()
{

  float  valorAD = analogRead(A0);     //lé o valor de entrada no pino A0
  float Vd = valorAD * (5.0 / 1023.0); //faz o caluclo para que o valor seja mostrado entre 0 e 5 volts

  atualizaBuffer(Vd);

  Serial.println(bufferCircular[pos]);
  
}

void atualizaBuffer(double valor)
{
  pos = ((pos == tamBuffer) ? 0 : (pos + 1)); //operador ternário, ele recebe 0 se pos==tamBuffer ou pos+1 caso contrário
  bufferCircular[pos] = valor;
}


void inicializaBuffer() {
  for (int i = 0; i < tamBuffer; i++) /* preeche com 0 */
    bufferCircular[i] = 0;
  pos = tamBuffer - 1; /* começa da posição 0 após a comparação */
}



double GetValueBuffer(int posi) {
  /* retorna um valor da posição do buffer */
  int indice;
  /* calculando a poição do buffer */
  indice = (pos - posi) % tamBuffer;

  return bufferCircular[indice];

}

void loop() {


  if (veri == 0 ) {
    inicializaBuffer();
    veri = 1;
  }


}
