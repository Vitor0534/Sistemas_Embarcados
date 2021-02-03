#include "TimerOne.h"
#include "math.h"


//implementação de buffer circular
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
  /*  double vetorCof[tamBuffer]=
    {
            0,
          -0.0031105211498156328,
        -0.012797301340805499               
       , 0.048741557240531003                
       , 0.2627564689748314                      
       ,   0.40881959255051736                         
       ,  0.2627564689748314                       
       ,    0.048741557240531003                            
       ,  -0.012797301340805499                  
       ,  -0.0031105211498156328
       ,0                                            
      };*/


//PASSA BAIXA 4HZ
double vetorCof[tamBuffer]=
   {
          0.1964734010405112
         , 0.1964734010405112 
         , 0.30405566970417008
          ,-0.1964734010405112                                  
      };

//passa alta 4hz
 /*double vetorCof[tamBuffer]=
    {
         0,
          0.0030439033408429599,
        0.012523222453369549               
       , -0.047697662795552674                 
       , -0.25712903247354402                      
       ,   0.60009589886907055                          
       ,   -0.25712903247354402                         
       ,    -0.047697662795552674                           
       , 0.012523222453369549                  
       ,  0.0030439033408429599
       ,0                                            
      };
*/

/*double vetorCof[tamBuffer]=
    {
         -0.000000000000000035946852365325244,
          -0.088217736359795115               ,
         0.000000000000000026628776645408408               
       , -0.29401151844423223                                 
       ,  0.00000000000000002715357662674018                      
       ,    0.58841243583112568                                          
       ,   0.00000000000000002715357662674018                         
       ,   -0.29401151844423223                                          
       ,  0.000000000000000026628776645408408                 
       ,  -0.088217736359795115               
       ,-0.000000000000000035946852365325244       
                                           
      };*/




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


}


void callback()
{

  float  valorAD = analogRead(A0);     //lé o valor de entrada no pino A0
  float Vd = valorAD * (5.0 / 1023.0); //faz o caluclo para que o valor seja mostrado entre 0 e 5 volts

  
 // Serial.println(Vd);

  //Serial.println(String(fir(Vd),6));
  Serial.println(fir(Vd),6);
  
}





void atualizaBuffer(double valor)
{
  pos = ((pos == 0) ? tamBuffer-1 : (pos - 1)); //operador ternário, ele recebe tamBuffer-1 se pos==0 ou pos-1 caso contrário
  bufferCircular[pos] = valor;
}




void inicializaBuffer() {
  for (int i = 0; i < tamBuffer; i++) /* preeche com 0 */
    bufferCircular[i] = 0;
  pos = 0; /* começa da posição tamBuffer-1 após a comparação */
}




double GetValueBuffer(int posi) {
  /* retorna um valor da posição do buffer */
  int indice;
  /* calculando a poição do buffer */
  indice = (pos - posi) % tamBuffer;

  return bufferCircular[indice];

}






double fir(double xnew)
{

  int i;
  double result;

  atualizaBuffer(xnew);

  for(i=0,result=0; i< tamBuffer;i++)
  {
    //result = result + vetorCof[i] * GetValueBuffer(i);
    result = result + vetorCof[i] * bufferCircular[i];
  }  
   return result;
  
}





void loop() {


  if (veri == 0 ) {
    inicializaBuffer();
    veri = 1;
  }


}
