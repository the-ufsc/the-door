#include <Servo.h>

#define PIN_TRIG 13
#define PIN_ECHO 11
#define PIN_BUTTON 2
#define PIN_SERVO 10

Servo myservo; 
int pos = 90;   
int buttonState = 0; 

const String link = "http://example.org";

void setup() {
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  // Serial.begin(115200);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  myservo.attach(PIN_SERVO);
}

void loop() {
  buttonState = digitalRead(PIN_BUTTON);

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