#include <DHT.h>

#define PIN_P 15      // Pino do Botão para Nutriente P
#define PIN_K 2       // Pino do Botão para Nutriente K
#define LDR_PIN 34    // Pino do Sensor LDR para pH
#define DHT_PIN 4     // Pino do Sensor DHT22
#define RELAY_PIN 5   // Pino do Relé

DHT dht(DHT_PIN, DHT22);

void setup() {
  Serial.begin(115200);
  pinMode(PIN_P, INPUT_PULLUP);
  pinMode(PIN_K, INPUT_PULLUP);
  pinMode(LDR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  dht.begin();
}

void loop() {
  // Leitura dos Sensores
  int nutrientP = digitalRead(PIN_P) == LOW ? 1 : 0; // Botão P
  int nutrientK = digitalRead(PIN_K) == LOW ? 1 : 0; // Botão K
  int ldrValue = analogRead(LDR_PIN); // LDR para simular pH
  float phValue = map(ldrValue, 0, 4095, 0, 14); 
  float humidity = dht.readHumidity(); // DHT22 para Umidade

  // Exibir as Leituras no Monitor Serial
  Serial.print("Nutriente P: "); Serial.println(nutrientP);
  Serial.print("Nutriente K: "); Serial.println(nutrientK);
  Serial.print("LDR (pH): "); Serial.println(phValue);
  Serial.print("Umidade: "); Serial.println(humidity);

  // Lógica para Controle do Relé (Bomba)
  if (humidity < 50 || nutrientP == 1 || nutrientK == 1) {
    digitalWrite(RELAY_PIN, HIGH); // Liga a bomba
    Serial.println("Bomba: Ligada");
  } else {
    digitalWrite(RELAY_PIN, LOW); // Desliga a bomba
    Serial.println("Bomba: Desligada");
  }

  delay(2000); // Aguarda 2 segundos antes de nova leitura
}
