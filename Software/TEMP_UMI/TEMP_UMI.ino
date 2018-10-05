#include "DHT.h"
 
#define DHTPIN A1 // SENSOR PIN
#define DHTTYPE DHT11 // DHT 11
#define ATTENTION 7 // PIN LED
#define DANGER 8 // PIN LED
 
// Conecte pino 1 do sensor (esquerda) ao +5V
// Conecte pino 2 do sensor ao pino de dados definido em seu Arduino
// Conecte pino 4 do sensor ao GND
// Conecte o resistor de 10K entre pin 2 (dados) 
// e ao pino 1 (VCC) do sensor
DHT dht(DHTPIN, DHTTYPE);
 
void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();

  pinMode(ATTENTION, OUTPUT);
  pinMode(DANGER, OUTPUT);
  
  analogWrite(ATTENTION, 200);
  analogWrite(DANGER, 200);
  delay(500);
  
  analogWrite(ATTENTION, 0);
  analogWrite(DANGER, 0);
}
 
void loop() {
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Umidade: ");
    Serial.print(h);
    Serial.print(" %t");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");

    if(h < 33 && h >= 30 && t < 34) {
      analogWrite(ATTENTION, 200);
    } else {
      analogWrite(ATTENTION, 0);  
    }
    if(h < 30 && t > 34 ) {
      analogWrite(DANGER, 200);
    } else {
      analogWrite(DANGER, 0);  
    }
    
  }
}
