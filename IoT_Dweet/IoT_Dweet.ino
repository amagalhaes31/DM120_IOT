/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/

#include <ESP8266WiFi.h>
#include <DHT.h>

#define PIN_LUM A0
#define DHTTYPE DHT11
#define DHTPIN  D1
#define LED_R   D2 
#define LED_G   D3
#define LED_B   D4
#define BUZZER  D5

// Global Variable
float temperatura = 0.0; float umidade = 0.0;
float tempMin = 999; float tempMax = 0;
float umidMin = 999; float umidMax = 0;
int luminosidade = 0;
int luminosidade_perc = 0;
int lumiMax = 0; int lumiMin = 999;
String current_color = "";
bool status_buzzer = false;

#ifndef STASSID
#define STASSID "MagalhaesAlexandre"
#define STAPSK  "magal2020Alexandre"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

const uint16_t port = 80;
const char* host = "dweet.io";
String thing_name = "alexandre_dm120";

DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;

void setup() {
  Serial.begin(115200);

  // Initialize the DHT11
  dht.begin();

  // Enable LEDs RGB
  pinMode(LED_R, OUTPUT); 
  pinMode(LED_G, OUTPUT); 
  pinMode(LED_B, OUTPUT); 
  // Enable Buzzer
  pinMode(BUZZER, OUTPUT);
  
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  ReadTempHumidity();

  ReadLuminosidade();
  
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }

  // This will send a string to the server
  Serial.println("sending data to server");
  if (client.connected()) {
    postToDweet();
  }

  // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(60000);
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  Serial.println("receiving from remote server");
  // not testing 'client.connected()' since we do not need to send data here
  while (client.available()) {
    char ch = static_cast<char>(client.read());
    Serial.print(ch);
  }

  // Close the connection
  Serial.println();
  Serial.println("closing connection");
  client.stop();

  delay(3000); // execute once every 5 minutes, don't flood remote service
}

void ReadTempHumidity() {
  
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
  
  if (temperatura >= 30 && temperatura < 100) {
    acendeLED(255,0,0);
    current_color = "vermelha";
  }
  else if (temperatura >= 10 && temperatura < 30) {
    acendeLED(0,255,0);
    current_color = "verde";
  }
  else {
    acendeLED(0,0, 255);
    current_color = "azul";
  }
  Serial.println("Cor: " + current_color);
  Serial.println("");
}


void ReadLuminosidade() {

  luminosidade = analogRead(PIN_LUM);                
  Serial.print("Luminosidade = " );              
  Serial.println(luminosidade);  
  if(luminosidade < lumiMin) lumiMin = luminosidade;
  if(luminosidade > lumiMax) lumiMax = luminosidade;
  Serial.println("lumiMin = " + String(lumiMin));  
  Serial.println("lumiMax = " + String(lumiMax));  
 
  luminosidade_perc = map(luminosidade, 0, 1023, 0, 100);
  Serial.print("Luminosidade[%] = " );              
  Serial.print(luminosidade_perc);     
  Serial.println("%"); 

  if(luminosidade_perc >= 50) {
    acionaBuzzer();
    status_buzzer = true;
  } else {
    status_buzzer = false;
  }
  Serial.println("Buzzer: " + String(status_buzzer)); 
  Serial.println(""); 
}

void acendeLED(int r, int g, int b){
  analogWrite(LED_R, r);
  analogWrite(LED_G, g);
  analogWrite(LED_B, b);
}

void acionaBuzzer(){
  digitalWrite(BUZZER, HIGH); 
  delay(2000);
  digitalWrite(BUZZER, LOW);   
}


void postToDweet(){
  String params;
  params += "temperatura=" + String(temperatura) + "&";
  params += "tempMax=" + String(tempMax) + "&";
  params += "tempMin=" + String(tempMin) + "&";
  params += "umidade=" + String(umidade) + "&";
  params += "umidMax=" + String(umidMax) + "&";
  params += "umidMin=" + String(umidMin) + "&";
  params += "luminosidade=" + String(luminosidade) + "&";
  params += "lumMax=" + String(lumiMax) + "&";
  params += "lumMin=" + String(lumiMin) + "&";
  params += "current_color=" + String(current_color) + "&";
  params += "status_buzzer=" + String(status_buzzer);

  String request = "POST /dweet/for/" + thing_name + "?" + params;
  Serial.println("REQUEST: " + request);
  client.println(request);
  client.println("Host: https://www.dweet.io");
  client.println("Connection: close");
  client.println();
}
