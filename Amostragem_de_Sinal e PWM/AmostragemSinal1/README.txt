Autor: Vitor de Almeida Silva

Programa para amostragem de sinal com arduino uno. é uma amostragem simples, que faz uso somente do loop e do delay(). As taxas de amostragem indicadas no código são de:
- 1hz
- 10hz
- 100hz

funcionamento:

1 - inicialização da porta serial e dos pinos
2 - O sinal é capiturado por meio da porta analógica A0 do arduino;
3 - ocorre um delay de tempo 10, 100 ou 1000;
4 - o sinal é normalizado para um valor entre 0v e 5v para ser visualizado;
5 - o valor é impresso na porta serial;
6 - O programa volta ao passo 2 é repete o processo até que seja interrompido. 