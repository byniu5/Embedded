#include <Bounce2.h>

int inputPin = 5;
int ledPin = 13;
int ledValue = LOW;
Bounce bouncer = Bounce(inputPin, 5);

void setup() {
  pinMode(inputPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(inputPin, HIGH);   //Uruchamia rezystor wbudowany w wejście nr 5 //Należy wywołać po ustaleniu pinMode()
  Serial.begin(9600);
}

void loop() {


  if(bouncer.update() && bouncer.read() == HIGH){
    ledValue = ! ledValue;
    digitalWrite(ledPin, ledValue);
    Serial.println(ledValue);
  }
}
