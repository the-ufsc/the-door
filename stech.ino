#include <ESP32Servo.h>

#include <WiFi.h>
#include <HTTPClient.h>

#define PIN_TRIG 4
#define PIN_ECHO 2
#define PIN_SERVO 15

Servo myservo; 
int pos = 90;   
int buttonState = 0; 
int distanceOpen = 0;

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const String url = "https://raw.githubusercontent.com/the-ufsc/the-door/main/distance.txt";

void setup() {
  Serial.begin(115200);
  Serial.println("Connect Components");
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  myservo.attach(PIN_SERVO);
  Serial.println("Components ok.");  
  
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password, 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println("Wifi ok.");
  
  HTTPClient http;
  http.begin(url);

  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    distanceOpen = http.getString().toInt();
    Serial.print("Distancia definida:");
    Serial.println(distanceOpen);
    Serial.println("Pronto para uso");
  }
  else {
    Serial.println("ERROR HTTP");
  }
}


void loop() {
  int oldPos = 90;   
  // CAPTURAR A DISTANCIA //
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  // LER O RESULTADO
  int duration = pulseIn(PIN_ECHO, HIGH);
  
  // END DISTANCIA //
  if (duration / 58 < distanceOpen){
   pos = 180;
  } else {
    pos = 90; 
  }

  if (pos != oldPos){
    myservo.write(pos);
    oldPos = pos;
  }
  
  delay(1000);
}
