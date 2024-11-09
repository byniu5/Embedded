#include <LiquidCrystal.h>

//lcd(rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int numRows = 2;
int numCols = 16;

void setup() {
  Serial.begin(9600);
  lcd.begin(numCols, numRows);
  lcd.clear();
  void home();
  lcd.print("Simba :)");
  lcd.setCursor(0, 1);
  lcd.print("to moj kociak");
}

void loop() {
  if (Serial.available() > 0) {
    
    char ch = Serial.read();
    if (ch == '#') {
      lcd.clear();
    }
    else if (ch == '/') {
      lcd.setCursor(0, 1);
    }
    else if (ch == '\\') {
      lcd.home();
    }
    else if (ch == '$') {
      lcd.noDisplay();
    }
    else if (ch == '%') {
      lcd.display();
    }
    else {
      lcd.write(ch);
    }
  }
}
