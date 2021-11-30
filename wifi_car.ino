/*Nodemcu ESP8266 WIFI control car.
*/
 
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//For temperature sensor
#include <DHT.h>


 
//Motor PINs
#define ENA D0
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENB D5

//For temperature sensor
#define DHTPIN D8
#define DHTTYPE DHT12
DHT dht(DHTPIN, DHTTYPE);

 
bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int Speed;
char auth[] = "O7SZvgx1vSpWFEQF1PswAolB0RFY3uOF"; //Enter your Blynk application auth token
char ssid[] = "tejkiran"; //Enter your WIFI name
char pass[] = "tejkiran"; //Enter your WIFI passowrd

//For temperature sensor
BlynkTimer timer;

 
void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D8,OUTPUT);
 
  Blynk.begin(auth, ssid, pass);

  
//For temperature sensor
  dht.begin();
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}
 
BLYNK_WRITE(V0) {
  forward = param.asInt();
}
 
BLYNK_WRITE(V1) {
  backward = param.asInt();
}
 
BLYNK_WRITE(V2) {
  left = param.asInt();
}
 
BLYNK_WRITE(V3) {
  right = param.asInt();
}
 
BLYNK_WRITE(V4) {
  Speed = param.asInt();
}
 
void smartcar() {
  if (forward == 1) {
    carforward();
    Serial.println("carforward");
  } else if (backward == 1) {
    carbackward();
    Serial.println("carbackward");
  } else if (left == 1) {
    carturnleft();
    Serial.println("carfleft");
  } else if (right == 1) {
    carturnright();
    Serial.println("carright");
  } else if (forward == 0 && backward == 0 && left == 0 && right == 0) {
    carStop();
    Serial.println("carstop");
  }
}
void loop() {
  Blynk.run();
  smartcar();
  digitalWrite(D6,HIGH);

  //For temperature sensor
  timer.run();
}
 //For temperature sensor
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}
 
void carforward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, HIGH);
}
void carbackward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, LOW);
}
void carturnleft() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, HIGH);
}
void carturnright() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(D6, LOW);
  digitalWrite(D7, HIGH);
}
void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, LOW);
}
