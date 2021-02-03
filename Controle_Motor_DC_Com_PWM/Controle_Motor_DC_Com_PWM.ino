// Autor: Vitor de Almeida Silva, PUC-GO 

/* informações:
  For Arduino Mega: (tested on Arduino Mega 2560)
  timer 0 (controls pin 13, 4)
  timer 1 (controls pin 12, 11)   --- no atmega328p-pu esse é do pino 10 e 9
  timer 2 (controls pin 10, 9)
  timer 3 (controls pin 5, 3, 2)
  timer 4 (controls pin 8, 7, 6)

  TCCRnB, where 'n' is the number for the timer.
  TCCR2B for timer 2, TCCR3B for timer 3.
  Eg:

  TCCR2B = TCCR2B & 0b11111000 | 0x01;
  //sets Arduino Mega's pin 10 and 9 to frequency 31250.
  //code typically inserted in setup()

  Setting   Divisor   Frequency
  0x01        1       31372.55
  0x02        8       3921.16
  0x03        64      490.20   <--DEFAULT
  0x04        256     122.55
  0x05        1024    30.64

  TCCR1B = (TCCR1B & 0b11111000) | <setting>;
*/



#define B1 9      // pino que controla a base 1
#define B2 10      // pino que controla a base 2

void setup()
{


  Serial.begin(9600); // configura a comunicação serial com 9600 bps
  pinMode(B1, OUTPUT);  // configura pino da B1 como saída
  pinMode(B2, OUTPUT);  // configura pino da B2 como saída
  digitalWrite(B1, LOW); //configura o pino B1 como 0
  digitalWrite(B2, LOW); //configura o pino B2 como 0

  TCCR1B = TCCR1B & 0b11111000 | 0x03; //configura a frequência do pwm nos pinos 9 a 10

  //proximo passo é implementar a função pro usuário configurar a velocidade

}

int velocidade = 100;
String direcao = "";
bool cheq1 = true;
bool cheq2 = true;

String ler() {
  String entrada;
  while (true)
  {
    if (Serial.available() > 0) {
      char numero = Serial.read();
      entrada += numero; //converte o dígito em um char e coloca isso na string
      //delay(1);
    }
    else {
      int v = Serial.read();
      return entrada;
    }
  }
}



void freqPWM(int freq)
{
  /*
     Opção Setting   Divisor   Frequency
      1     0x01        1       31372.55
      2     0x02        8       3921.16
      3     0x03        64      490.20   <--DEFAULT
      4     0x04        256     122.55
      5     0x05        1024    30.64
  */
  switch (freq)
  {
    case 1:
      TCCR1B = TCCR1B & 0b11111000 | 0x05; //configura a frequência do pwm nos pinos 9 a 10
      break;
    case 2:
      TCCR1B = TCCR1B & 0b11111000 | 0x04; //configura a frequência do pwm nos pinos 9 a 10
      break;
    case 3:
      TCCR1B = TCCR1B & 0b11111000 | 0x03; //configura a frequência do pwm nos pinos 9 a 10
      break;
    case 4:
      TCCR1B = TCCR1B & 0b11111000 | 0x02; //configura a frequência do pwm nos pinos 9 a 10
      break;
    case 5:
      TCCR1B = TCCR1B & 0b11111000 | 0x01; //configura a frequência do pwm nos pinos 9 a 10
      break;
    default:
      Serial.println("opção de frequência inexistente");
      break;
  }

}



void wait()
{
  int t = 0;
  limpaBuffer();//para tirar o nixo do buffer
  while (t == 0)
  {
    char a = Serial.read();
    String b = "";
    b += a;
    t = b.toInt();
  }
  int v = Serial.read();
  cheq1 = cheq2 = true;
}

void limpaBuffer()
{
  while (Serial.available() > 0)
  {
    char valor = Serial.read();
  }
  int v=Serial.read();
}


void configurar()
{
  String dado = "";

  limpaBuffer();//para tirar o nixo do buffer

  if (cheq1)
  {
    Serial.println("insira a direção h(horário) a(anti horário): ");
    limpaBuffer();//para tirar o nixo do buffer
    while (true) {
      if (Serial.available() > 0) //verifica se chegou algum dado na serial
      {
        direcao = ler();
        cheq1 = false;
        break;
      }
    }
    //separaDV(dado);
  }


  if (cheq2)
  {
    Serial.println("ecolha a velocidade  1,2,3,4 ou 5 (1 máximo e 5 mínimo): ");
    limpaBuffer();//para tirar o nixo do buffer
    velocidade = 0;
    while (velocidade == 0) {
      if (Serial.available() > 0) //verifica se chegou algum dado na serial
      {
        String v = ler();
        velocidade = v.toInt();
        cheq2 = false;
        //break;
      }
    }
  }

}

void condicoes()
{
  
  limpaBuffer();//para tirar o nixo do buffer
  if (direcao == "a")
  {
    analogWrite(B2, 0); //zera B2
    analogWrite(B1, velocidade+245); //atualiza a saída PWM do pino B1 com valor recebido
    freqPWM(velocidade);
    Serial.println("h) para reiniciar insira qualquer tecla");
    //Serial.println("h");
    wait();

  } else
  {
    limpaBuffer();//para tirar o nixo do buffer
    if (direcao == "h")
    {
      analogWrite(B1, 0); //zera B2
      analogWrite(B2, velocidade+245); //atualiza a saída PWM do pino B1 com valor recebido
     freqPWM(velocidade);
      Serial.println("(a) para reiniciar insira um número");
      // Serial.println("a");
      wait();
    }

  }

}

void loop() {
  configurar();  //configura a velocidade e a direção
  condicoes();   //executa o código nas opções de velocidade e direção definidas
  
}
