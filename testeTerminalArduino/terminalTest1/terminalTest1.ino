void setup() {
  Serial.begin(9600);
}

bool test = true;
String entrada = "";


String ler() {
  String entrada;
  while (Serial.available() == 0);

  while (Serial.available() > 0)
  {

    char numero = ' ';
    numero=Serial.read();
    delay(40);
    if (numero != '\n') {
      Serial.println(numero);
      entrada += numero;
    }
    else {
      if(numero=='\n'){
        Serial.println("foi igual a \n");
        entrada+="\0";
        break;
      }
     
    }
  }
  return entrada;
}

String ler2()
{
  char l, j;
  Serial >> l >> j;
  char result = l + j;
  return result;
}

void loop() {
  String entrada;
  if (test) {
    Serial.println("insira um numero:");
    test = false;
  }

  if (Serial.available() > 0) {
    entrada = ler();
    int valor=entrada.toInt();
    Serial.println(valor+1);
  }

}
