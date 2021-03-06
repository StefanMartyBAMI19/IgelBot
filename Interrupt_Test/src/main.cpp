#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>

#define M0 14              //Pinbelegung
#define PIN_A 12
#define PIN_B 11
#define PIN_I 10

Adafruit_MotorShield AFMS = Adafruit_MotorShield();     //Motor einrichten
Adafruit_DCMotor *Bein = AFMS.getMotor(1);

int i;

volatile int encoderPos = 0;                    //encoder Values
volatile int encoderPinALast = LOW;
volatile int n = LOW;

void setup() {
  pinMode (PIN_A, INPUT);
  pinMode (PIN_B, INPUT);
  Serial.begin (9600);
    while(!Serial){
      delay(1);
    }
attachInterrupt(digitalPinToInterrupt(PIN_A), encoder, CHANGE);     //ISR Encoderabtast
Serial.println("Ready");
pinMode(M0,OUTPUT);       //Motor konfigurieren
AFMS.begin();

Bein->setSpeed(90);
Bein->run(FORWARD);
while (i == 0) {        //Position Kalibrieren
  i = digitalRead(PIN_I);
    }
while(encoderPos<200)  {
  Serial.println("Auf Startposition...");
  n = digitalRead(PIN_A);
    if((encoderPinALast == LOW) && (n == HIGH)) {
    if (digitalRead(PIN_B) == LOW) {
      encoderPos++;
    } else {
      encoderPos--; }
  }
  encoderPinALast = n;
}
Bein ->run(RELEASE);           //Startposition erreicht
delay(200);
encoderPos = 0;

Bein ->run(FORWARD);
}

void loop() {
delay(100);
Serial.print("Position Bein = ");       //Position auf SerialMonitor mitverfolgen
Serial.println(encoderPos);
if(encoderPos>360*4)  {                 //4 Schritte vorwärts
  Bein ->run(RELEASE);
  delay(200);
  Bein ->setSpeed(80);
  Bein ->run(BACKWARD);
  while(encoderPos>0) {                 //4 Schritte rückwärts
    Serial.print("Position Bein = ");
    Serial.println(encoderPos);
    }
  Bein ->run(RELEASE);
  delay(200);
  Bein ->setSpeed(90);
  Bein ->run(FORWARD);
  }
}
void encoder()  {             //ISR Encoderprogrammablauf
  n = digitalRead(PIN_A);
    if((encoderPinALast == LOW) && (n == HIGH)) {
    if (digitalRead(PIN_B) == LOW) {
      encoderPos++;
    } else {
      encoderPos--; }
  i = digitalRead(PIN_I);
  }
  encoderPinALast = n;
}
