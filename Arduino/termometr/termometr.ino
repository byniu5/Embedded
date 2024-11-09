#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

OneWire MyWire(12);
DallasTemperature sensor(&MyWire);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int temperatura;

void setup() {
  Serial.begin(9600);
  sensor.begin();
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.clear();
}

void loop() {
  lcd.home();
  sensor.requestTemperatures();
  Serial.println(sensor.getTempCByIndex(0));
  temperatura = 100 * (sensor.getTempCByIndex(0));
  if (temperatura < 0) {
    lcd.print(F("-"));
  }
  else {
    lcd.print(F(" "));
  }
  
  temperatura = abs(temperatura);

  if(temperatura < 1000) {
    lcd.print(F(" "));
  }
  lcd.print("   ");
  lcd.print(float(temperatura) / 100, 2);
  lcd.print((char)223);         // Znak stopni chyba ASCII
  lcd.print(F("C"));
  delay(200);
}