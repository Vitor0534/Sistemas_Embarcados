Autor: Vitor de Almeida Silva

Programa para amostragem de sinal com arduino uno. � uma amostragem simples, que faz uso somente do loop e do delay(). As taxas de amostragem indicadas no c�digo s�o de:
- 1hz
- 10hz
- 100hz

funcionamento:

1 - inicializa��o da porta serial e dos pinos
2 - O sinal � capiturado por meio da porta anal�gica A0 do arduino;
3 - ocorre um delay de tempo 10, 100 ou 1000;
4 - o sinal � normalizado para um valor entre 0v e 5v para ser visualizado;
5 - o valor � impresso na porta serial;
6 - O programa volta ao passo 2 � repete o processo at� que seja interrompido. 