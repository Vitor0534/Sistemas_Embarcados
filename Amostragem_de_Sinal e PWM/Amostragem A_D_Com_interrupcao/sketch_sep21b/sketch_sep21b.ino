// Autor: Vitor de Almeida Silva, PUC-GO

#include "TimerOne.h"

// Variáveia para armazenar os resultados

unsigned long tempo_inicio;

unsigned long tempo_fim;

unsigned long valor;

//variáveis para controlar o numero de amostras

int cont;
int qtdAmostras;

//constante para configuração do prescaler
//Configuração  do fator de divisão entre o clock do sistema e a entrada de clock do ADC. 
//Os valores possíveis são exibidos na tabela abaixo:

/*     ADPS2------ADPS1------ADPS0------Fator de divisão 
 * 1|    0         0           0               2         
 * 2|    0         0           1               2
 * 3|    0         1           0               4
 * 4|    0         1           1               8
 * 5|    1         0           0               16
 * 6|    1         0           1               32
 * 7|    1         1           0               64
 * 8|    1         1           1               128
 */

/*
 *  O bloco prescaler controla do clock do conversor A/D, 
 *  assim o clock do conversor A/D será uma fração do clock 
 *  do oscilador principal, conforme o fator do prescaler.
 */
/*
 * 
 * Uma conversão normal necessita de 13 pulsos de clock no 
 * conversor A/D. A primeira conversão necessita de 25 pulsos 
 * de clock. Dessa forma 
 * o valor de amostragem do conversor A/D depende do pulsos 
 * de clock de cada conversão, ou seja, o valor do clock deve 
 * ser dividido por 13 para calcular  a quantidade de amostras 
 * por segundo.
 */
 //para saber o número de amostras basta dividir a frequência de amostragem por 13
 //sbi é uma macro para setar o bit (do segundo argumento) do endereço (do primeiro argumento) para 1
 //sbi(ADCSRA, ADPS2);   com isso é possível setar um por 1, equivale a fazer ADPSx=1

 
const unsigned char PS_16 = (1 << ADPS2);  //linha 5 tabela  clock 1Mhz    clock=1Mhz            50khz amostras
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0); //linha 6 tabela  clock=500 khz   31khz amostras 
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1); //linha 7 tabela  clock=250khz    16Khz amostra
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // linha 8 tabela  clock=padrão = 8600Hz amostra
//estas atribuições são concatenações de valores

void setup() {
 Serial.begin(9600);

 //configura o preescaler do ADC
  ADCSRA &= ~PS_128;  //limpa configuração da biblioteca do arduino

//valores possiveis de prescaler, descomentar  a linha com prescaler desejado
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
 * para um sinal de 1Hz a frequência de Niquist seria 1/2 segundos
 * porem na pratica esse valor não é suficiente por isso aumentados de 2, para 10 vezes a maior freq do sinal para as amostras logo
 * a freqN para um sinal de 1Hz é 1/10 seg, ou 0,1 segundos   ( timer1.initialize(100000))
 */
 
Timer1.attachInterrupt(callback); // Configura a função callback() como a função para ser chamada a cada interrupção do Timer1
pinMode(A0, INPUT);

//insira aqui a quantidade de amostras que se deseja coletar 
qtdAmostras=100;
cont=0;

}

void callback()
{
  //if(cont<=qtdAmostras)
 // {
   //leitura
   tempo_inicio = micros(); //marca tempo de inicio de leitura
   
   float  valorAD = analogRead(A0);     //lé o valor de entrada no pino A0
   float Vd= valorAD * (5.0 / 1023.0);  //faz o caluclo para que o valor seja mostrado entre 0 e 5 volts
   
   tempo_fim = micros();                //le tempo no fim da conversão
   
   //cont++;

   //exibe valor lido e tempo de conversão
   
   //Serial.print("Valor= ");
   
   Serial.println(Vd);
  //}
  //else
  //{
    
 // }
   
  //Serial.print(" -- Tempo leitura = ");
  //Serial.print(tempo_fim - tempo_inicio);
  //Serial.println(" us");
  
  // este delay pode vir a ser pulado caso o timer lance a interrupção
  // delay(500);
}


void loop() 
{  

  //estado de espera
  
}
