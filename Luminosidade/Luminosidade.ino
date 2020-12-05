/*
  Luminosidade
*/

#define PIN_LUM A0

int luminosidade = 0;
int luminosidade_perc = 0;
int lumiMax = 0; int lumiMin = 999; 


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
  
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
  
 
  delay(3000);
  Serial.println("");     
}
