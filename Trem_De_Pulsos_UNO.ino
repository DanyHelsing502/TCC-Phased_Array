// Bibliotecas necessárias
#include <Arduino.h>
// Pino utilizado para a saída do sinal
const int tx1 = 13;
const int tx2 = 12;
const int tx3 = 11;
const int tx4 = 10;

const int ack = 8;

const int flag_tx1 = 7;
const int flag_tx2 = 6;
const int flag_tx3 = 5;
const int flag_tx4 = 4;

const int cont1 = 10;
const int delay_time = 8;


// Função para enviar o sinal burst
void enviarBurst_TX1() {

  for (int x=1; x<=cont1; x++){
  digitalWrite(tx1, HIGH);
  delayMicroseconds(delay_time);
  digitalWrite(tx1, LOW);
  delayMicroseconds(delay_time);
    }
  }


  void enviarBurst_TX2() {

  for (int x=1; x<=cont1; x++){
  digitalWrite(tx2, HIGH);
  delayMicroseconds(delay_time);
  digitalWrite(tx2, LOW);
  delayMicroseconds(delay_time);
    }
  }

  void enviarBurst_TX3() {

  for (int x=1; x<=cont1; x++){
  digitalWrite(tx3, HIGH);
  delayMicroseconds(delay_time);
  digitalWrite(tx3, LOW);
  delayMicroseconds(delay_time);
    }
  }

  void enviarBurst_TX4() {

  for (int x=1; x<=cont1; x++){
  digitalWrite(tx4, HIGH);
  delayMicroseconds(delay_time);
  digitalWrite(tx4, LOW);
  delayMicroseconds(delay_time);
    }
  }


void setup() {
  pinMode(tx1, OUTPUT);
  pinMode(tx2, OUTPUT);
  pinMode(tx3, OUTPUT);
  pinMode(tx4, OUTPUT);
  pinMode(ack, OUTPUT);

  pinMode(flag_tx1, INPUT);
  pinMode(flag_tx2, INPUT);
  pinMode(flag_tx3, INPUT);
  pinMode(flag_tx4, INPUT);
}


  void loop() {
  // Lê os valores dos pinos e armazena em variáveis
  bool estadoFlagTx1 = digitalRead(flag_tx1);
  bool estadoFlagTx2 = digitalRead(flag_tx2);
  bool estadoFlagTx3 = digitalRead(flag_tx3);
  bool estadoFlagTx4 = digitalRead(flag_tx4);

  // Compara os valores lidos e chama as funções correspondentes
  if (estadoFlagTx1 == HIGH) {
    digitalWrite(ack, HIGH);
    enviarBurst_TX1();
    digitalWrite(ack, LOW);

  } else if (estadoFlagTx2 == HIGH) {
     digitalWrite(ack, HIGH);
    enviarBurst_TX2();
    digitalWrite(ack, LOW);

 
  } else if (estadoFlagTx3 == HIGH) {
    digitalWrite(ack, HIGH);
    enviarBurst_TX3();
    digitalWrite(ack, LOW);
  

  } else if (estadoFlagTx4 == HIGH) {
    digitalWrite(ack, HIGH);
    enviarBurst_TX4();
    digitalWrite(ack, LOW);
    

  }
  estadoFlagTx1=LOW;
  estadoFlagTx2=LOW;
  estadoFlagTx3=LOW;
  estadoFlagTx4=LOW;
  // Aguarda 3000 microssegundos antes de enviar o próximo burst
  delay(3);
}

//Fica oscioso enquanto o pi pico ainda faz a aquisição