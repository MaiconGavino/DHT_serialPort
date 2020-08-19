/* Name: Maicon Serrão Gavino */
#include <DHT.h>

#define Pin_DHT 6 //Pino digital ultilizado dht
#define DHTTYPE DHT22 //definindo o modelo do sensor

DHT dht(Pin_DHT, DHTTYPE); // passando os parâmetros

void setup() 
{
  Serial.begin(9600); //inicializando o serial
  dht.begin(); //inicializando a função
  delay(2000); //intervalo de inicialização
}

void loop() 
{
  Serial.print(" Temperatura: ");
  Serial.print(dht.readTemperature());
  delay(2000);
}
