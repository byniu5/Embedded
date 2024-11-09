#include <LiquidCrystal.h>
#include <TimeLib.h>

const byte rs = 8;
const byte en = 9;
const byte d4 = 4;
const byte d5 = 5;
const byte d6 = 6;
const byte d7 = 7;

const byte longDelay = 250;
const byte shortDelay = 25;

const byte buttonPlus = 2;
const byte buttonChange = 3;
const byte buttonMinus = 11;

byte sec;
byte mint;
byte h;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  pinMode(buttonMinus, INPUT_PULLUP);
  pinMode(buttonChange, INPUT_PULLUP);
  pinMode(buttonPlus, INPUT_PULLUP);

}

void loop() {

  displayTime:

  while (digitalRead(buttonChange) == HIGH) {                 //Przyciski są automatycznie w stanie wysokim
    time_t actualTime = now();                                
    sec = second(actualTime);
    mint = minute(actualTime);
    h = hour(actualTime);
    displayTime();
    displaySeconds();
  }

  lcd.clear();
  displayTime();
  delay(longDelay);
  while(digitalRead(buttonChange) == LOW) {}

  setTime:

  if (digitalRead(buttonPlus) == LOW) {
    addTime();
    displayTime();
    delay(longDelay);
  }
  while (digitalRead(buttonPlus) == LOW) {
    addTime();
    displayTime();
    delay(shortDelay);
  }

  if (digitalRead(buttonMinus) == LOW) {
    subtractTime();
    displayTime();
    delay(longDelay);
  }
  while (digitalRead(buttonMinus) == LOW) {
    subtractTime();
    displayTime();
    delay(shortDelay);
  }

  if (digitalRead(buttonChange) == HIGH) {
    goto setTime;
  }
  else {
    setTime(h, mint, 00, 01, 01, 2000);
    delay(longDelay);
    goto displayTime;
  }
}

///////////////////////////////////////////////////////////

void displayTime() {
  lcd.home();
  if (h < 10) {
    lcd.print(F(" "));
  }
  lcd.print(h);
  lcd.print(F(":"));
  if (mint < 10) {
    lcd.print(F("0"));
  }
  lcd.print(mint);
}

///////////////////////////////////////////////////////////

void displaySeconds() {
  lcd.print(F(":"));
  if (sec < 10) {
    lcd.print(F("0"));
  }
  lcd.print(sec);
}

///////////////////////////////////////////////////////////

void addTime() {
  mint++;
  if (mint == 60) {
    mint = 0;
    h++;
    if (h == 24) {
      h = 0;
    }
  }
}

///////////////////////////////////////////////////////////

void subtractTime() {
  mint--;
  if (mint == 255) {
    mint = 59;
    h--;
    if (h == 255) {
      h = 23;
    }
  }
}
