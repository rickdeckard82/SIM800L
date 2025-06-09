#include <HardwareSerial.h>
#include <Arduino.h>

HardwareSerial sim800(2); // UART2 - GPIO17(TX), GPIO16(RX)

void sendCommand(String cmd); // <- Adicione esta linha

void setup() {
  Serial.begin(115200);      // Comunicação com o PC
  sim800.begin(9600, SERIAL_8N1, 16, 17); // Comunicação com SIM800L

  Serial.println("Inicializando SIM800L...");

  delay(2000);

  sendCommand("AT");           // Verifica comunicação
  sendCommand("AT+CSQ");       // Verifica qualidade do sinal
  sendCommand("AT+CREG?");     // Verifica registro na rede
  sendCommand("AT+COPS?");     // Verifica operadora atual
}

void loop() {
  // nada no loop
}

void sendCommand(String cmd) {
  Serial.println("Enviando: " + cmd);
  sim800.println(cmd);
  
  long timeout = millis() + 3000;
  while (millis() < timeout) {
    while (sim800.available()) {
      char c = sim800.read();
      Serial.write(c); // Mostra resposta no Serial Monitor
    }
  }

  Serial.println("\n---\n");
}
