#include <DHT.h>

#define DHTPIN D1
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float tempMin = 999; float tempMax = 0;
float umidMin = 999; float umidMax = 0;

void setup(void)
{
  Serial.begin(115200);
  dht.begin();
}


void loop()
{  
  // Local Variable
  float temperatura = 0.0;
  float umidade = 0.0;

  // Read Temp
  temperatura = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.println(temperatura);
  if(temperatura > tempMax) tempMax = temperatura;
  if(temperatura < tempMin) tempMin = temperatura;
  Serial.println("TempMax: " + String(tempMax));
  Serial.println("TempMin: " + String(tempMin));

  // Read Hum.
  umidade = dht.readHumidity();
  Serial.print("Humidity: ");
  Serial.println(umidade); 
  if(umidade > umidMax) umidMax = umidade;
  if(umidade < umidMin) umidMin = umidade;
  Serial.println("HumidMax: " + String(umidMax));
  Serial.println("HumidMin: " + String(umidMin));

  // Delay
  delay(3000);Serial.println("");
}
