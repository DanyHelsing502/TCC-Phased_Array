// Bibliotecas necessárias
#include <Arduino.h>
// Pino utilizado para a saída do sinal
const int tx1 = 9;

const int cont1 = 10;


// Função para enviar o sinal burst
void enviarBurst_TX1() {
  //unsigned long tpAT = millis();  // Tempo atual em milissegundos
  // Gera um burst de 10 microssegundos
  for (int x=1; x<=cont1; x++){
  digitalWrite(tx1, HIGH);
  delayMicroseconds(10);
  digitalWrite(tx1, LOW);
  delayMicroseconds(10);
    }
  }


void setup() {
  pinMode(tx1, OUTPUT);

}


  void loop() {
 
    enviarBurst_TX1();

  // Aguarda 3000 microssegundos antes de enviar o próximo burst
  delayMicroseconds(3000);
}
//Fica oscioso enquanto o pi pico ainda faz a aquisição