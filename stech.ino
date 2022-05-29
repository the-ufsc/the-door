#include <ESP32Servo.h>

#include <WiFi.h>
#include <HTTPClient.h>
// #include <ArduinoJson.h>

#define PIN_TRIG 4
#define PIN_ECHO 2
#define PIN_SERVO 15

Servo myservo; 
int pos = 90;   
int buttonState = 0; 

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const String url = "https://raw.githubusercontent.com/the-ufsc/the-door/main/data.json";

void setup() {
  Serial.begin(115200);
  Serial.print("Connect Components");
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  myservo.attach(PIN_SERVO);
  Serial.print("Components ok.");  

  
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password, 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.print("Wifi ok.");

  
  HTTPClient http;
  http.begin(url);

  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println();
    Serial.println(payload);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    Serial.println(":-(");
  }

}


void loop() {

  // CAPTURAR A DISTANCIA //
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  // LER O RESULTADO
  int duration = pulseIn(PIN_ECHO, HIGH);
  
  // END DISTANCIA //
  if (duration / 58 < 200){
   pos = 180;
  } else {
    pos = 90; 
  }

  myservo.write(pos);
  delay(1000);
}
