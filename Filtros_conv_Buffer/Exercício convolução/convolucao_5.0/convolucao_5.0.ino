int veri;
double *vetA = new double();
double *vetB = new double();
double *vetConv = new double();
int n = 0;
int m = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  int veri = 0;
}

//para passar um int para string basta usar a função String(numero);

void imprimirVetor(double *v, int tamanho)
{
  //tamanho = n+m-1 para conv
  Serial.print("[ ");
  for (int i = 0; i < tamanho; i++)
  {
    if(i!=0){
    Serial.print(",");
    }
    Serial.print(v[i]);
  }
  Serial.println(" ]");
}


String ler2()
{
  String entrada = "";
  //while para montar a entrada

  while (Serial.available() <= 0);


  while (Serial.available() > 0)
  {
    char valor = "";
    valor = Serial.read();
    delay(4);
    if (valor!= '\n')   //verifica o final da linha 
    {
      entrada+=valor;
      //Serial.print(entrada);
    }
    else
    {
      if (valor == '\n')  //adiciona o final da string \0
      {
        entrada+= '\0';
       // Serial.println(entrada);
        return entrada;
      }
    }
  }
}

void limpaBuffer()
{
  while (Serial.available() > 0)
  {
    char valor = Serial.read();
  }
  Serial.flush();
  int v = Serial.read();
}



void Leitura()
{

   Serial.println("Insira o tamanho do vetor A");
   n = ler2().toInt();
   double vetorAtest[n];
   Serial.println();
   Serial.println("Insira os valores do vetor A, entrada tipo 1,2,3,4,5,....,n ");

  int i = 0;
  while (i<n) {
    Serial.print("vetorA[ ");
    Serial.print(i+1);
    Serial.print(" ]: ");
    String novo = ler2();
   /* if(novo=="F\0"){
      n=i;
      break;
    }*/
      
    vetorAtest[i] = novo.toInt();
    Serial.println(vetorAtest[i]);
    i++;
  }

Serial.println("Insira o tamanho do vetor B");
 m = ler2().toInt();
  double vetorBtest[m];
  Serial.println();
  Serial.println("Insira os valores do vetor B, entrada tipo 1,2,3,4,5,....,m ");

  int j = 0;
  while (j<m){
    Serial.print("vetorB[ ");
    Serial.print(j+1);
    Serial.print(" ]: ");
    String novo = ler2();
    /*if(novo=="F\0"){
      m=j;
      break;
    }*/
    vetorBtest[j] = novo.toInt();
    Serial.println(vetorBtest[j]);
    j++;
  }

  Serial.println(" VetorA = ");
  imprimirVetor(vetorAtest, n);
  Serial.println("VetorB = ");
  imprimirVetor(vetorBtest, m);
  Serial.println();
  convolucao(n,m,vetorAtest,vetorBtest);
}





void convolucao(int n, int m, double *vetorA, double *vetorB)
{
  double vet_a[n], vet_b[m], vet_conv[n + m - 1], aux[m + 2 * (n - 1)];

  //inicializa todos os vetores VA,VB e VC
  for (int i = 0; i < n + m - 1; i++)
  {
    if (i < n)
      vet_a[i] = vetorA[i];
    if (i < m)
      vet_b[i] = vetorB[i];
    vet_conv[i] = 0;
  }

  int x = 0; //aux contadora
  for (int i = 0; i < m + 2 * (n - 1); i++)
  {
    if (i < n - 1)
      aux[i] = 0; //parte nula
    else
    {
      if (i < n + m - 1)
      {
        aux[i] = vet_b[x]; //parte = vet_maior VB é o maior
        x++;
      }
      else
        aux[i] = 0; //parte nula
    }
  }
  for (int j = 0; j < n + m - 1; j++)
    for (int k = 0; k < n; k++)
      vet_conv[j] += vet_a[n - 1 - k] * aux[j + k]; //ele faz a operação com VA do n até o 0
  //VB por sua vez opera de 0 a m


  //imprime resultado
  Serial.print("VetorConv = ");
  imprimirVetor(vet_conv, (n + m - 1));

}


void loop() {

  if (veri == 0) {
    //double V1[13]={1,2,3,4,6,6,4,2,3,4,5,6,7};
    // double V2[13]={1,1,1,1,1,2,1,1,1,1,1,1,1};
    
    Leitura();
    veri = 1;
  }
}
