/*Trzeba też odblokować żeby świeciło w pełnym zakresie to znaczy 5V bo na razie to jest gdzieś do 2,3V
NIE BĘDZIE TAK ŚWIECIĆ BO ARDUINO MA JAKIEŚ STABILIZATORY I SAMO W SOBIE POBIERA CZĘŚĆ TEGO PRĄDU
trzeba to zrobić na zewnętrznym zasilaczu i tranzystorach

- program nie chce pracować kiedy przełącze wszystkie złącza na analogowe
- kolory w gotowych patternach nie red green blue a ich mieszanki
- prędkość migania w blinku niewygodnie się zmienia
*/

#include <LiquidCrystal.h>

#define BUTTON_PIN A0
#define FULL 255

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int numRows = 2;
int numCols = 16;
int blackWire = A5, greenWire = A4, redWire = A3, blueWire = A2;
int x;
bool flag = false;
int blueValue = 255, redValue = 255, greenValue = 255, overallValue = 0;

void setup() {

  pinMode(blackWire, OUTPUT); 
  pinMode(greenWire, OUTPUT); 
  pinMode(redWire, OUTPUT); 
  pinMode(blueWire, OUTPUT);
  lcd.begin(numCols, numRows); 
  Serial.begin(9600);

  printMenu();
  delay(500);
  help();
}

void loop() {

    back:
    x = analogRead(BUTTON_PIN);
    delay(100);

    if (x >= 800 && x < 1000) {
    
        int overallValue1 = map(overallValue, 255, 0, 100, 0);
        int redValue1 = map(redValue, 255, 0, 0, 100);
        int greenValue1 = map(greenValue, 255, 0, 0, 100);
        int blueValue1 = map(blueValue, 255, 0, 0, 100);

        lcd.clear();
        lcd.home();
        lcd.print(overallValue1);
        lcd.print("% brght ");
        lcd.print(blueValue1);
        lcd.print("% blue");  
        lcd.setCursor(0, 1);
        lcd.print(redValue1);
        lcd.print("% red ");
        lcd.print(greenValue1);
        lcd.print("% grn");
        flag = true;
    }

    while (flag) {

    int y = analogRead(BUTTON_PIN);
    int button = valuesToSwitch(y);

    if (button != 6) {
      Serial.print("Button pressed: ");
      Serial.println(button);
      delay(100);
    }

    switch (button) {

      case (1): {   // Right
        blueValue = switchingVoltageBlue(blueValue);
        analogWrite(blueWire, blueValue);
        flag = false;          
        break;
      }

      case (2): {   // Up - overall brightness
        overallValue = switchingVoltageBrightness(overallValue);
        analogWrite(blackWire, overallValue);
        flag = false; 
        break;
      }

      case (3): {   // Down
        greenValue = switchingVoltageGreen(greenValue);
        analogWrite(greenWire, greenValue);
        flag = false; 
        break;
      }

      case (4): {   // Left
        redValue = switchingVoltageRed(redValue);
        analogWrite(redWire, redValue);
        flag = false; 
        break;
      }

      case (5): {   // More options

        delay(500);
        lcd.clear();
        lcd.home();
        lcd.print("Rt-help Dn-fade");
        lcd.setCursor(0, 1);
        lcd.print("Lt-blink Up-???");                            

        while (true) {
        int z = analogRead(BUTTON_PIN);

        if (z >= 0 && z <= 50) {
          help();
          break;
        }
        else if (z >= 50 && z <= 250) break;
        else if (z >= 250 && z <= 450) {
          patternFade();
          break;
        } 
        else if (z >= 450 && z <= 650) {
          patternBlink();
          break;
        }
        else if (z >= 650 && z <= 850) goto back;
        }
      break;
      }  
    }
  }


  // Small delay to debounce the button
  delay(50);
}


int valuesToSwitch(int analogValue) {

  if (analogValue >= 0 && analogValue <= 50) {
    return 1; // Right
  } else if (analogValue >= 50 && analogValue <= 250) {
    return 2;  // Up
  } else if (analogValue >= 250 && analogValue <= 450) {
    return 3;  // Down
  } else if (analogValue >= 450 && analogValue <= 650) {
    return 4;  // Left
  } else if (analogValue >= 650 && analogValue <= 850) {
    return 5;  // Select
  } else if (analogValue > 850 && analogValue <= 1023) {
    return 6;  // None
  } else {
    return 7;  // Unkown
  }
}


int switchingVoltageBlue(int voltage) {

  lcd.clear();
  lcd.home();
  lcd.print("UP increasing");
  lcd.setCursor(0, 1);
  lcd.print("DOWN decreasing");
  delay(100);

  do {

  x = analogRead(BUTTON_PIN);
  
  if (x >= 50 && x <= 250 && voltage > 10) {
    voltage -= 10;
    increase(voltage);
    analogWrite(blueWire, voltage);
  }
  else if (x >= 250 && x <= 450 && voltage < 245) {
    voltage += 10;
    decrease(voltage);
    analogWrite(blueWire, voltage);
  }
  else if (x >= 50 && x <= 250 && voltage <= 10) {
    voltage = 0;
    increase(voltage);
    analogWrite(blueWire, voltage);
    }
  else if (x >= 250 && x <= 450 && voltage >= 245) {
    voltage = 255;
    decrease(voltage);
    analogWrite(blueWire, voltage);
    }

  }while (x < 650 || x > 850);

return voltage;
}


int switchingVoltageGreen(int voltage) {

  lcd.clear();
  lcd.home();
  lcd.print("UP increasing");
  lcd.setCursor(0, 1);
  lcd.print("DOWN decreasing");
  delay(100);

  do {

  x = analogRead(BUTTON_PIN);
  
  if (x >= 50 && x <= 250 && voltage > 10) {
    voltage -= 10;
    increase(voltage);
    analogWrite(greenWire, voltage);
  }
  else if (x >= 250 && x <= 450 && voltage < 245) {
    voltage += 10;
    decrease(voltage);
    analogWrite(greenWire, voltage);
  }
  else if (x >= 50 && x <= 250 && voltage <= 10) {
    voltage = 0;
    increase(voltage);
    analogWrite(greenWire, voltage);
    }
  else if (x >= 250 && x <= 450 && voltage >= 245) {
    voltage = 255;
    decrease(voltage);
    analogWrite(greenWire, voltage);
    }

  }while (x < 650 || x > 850);

return voltage;
}


int switchingVoltageRed(int voltage) {

  lcd.clear();
  lcd.home();
  lcd.print("UP increasing");
  lcd.setCursor(0, 1);
  lcd.print("DOWN decreasing");
  delay(100);

  do {

  x = analogRead(BUTTON_PIN);
  
  if (x >= 50 && x <= 250 && voltage > 10) {
    voltage -= 10;
    increase(voltage);
    analogWrite(redWire, voltage);
  }
  else if (x >= 250 && x <= 450 && voltage < 245) {
    voltage += 10;
    decrease(voltage);
    analogWrite(redWire, voltage);
  }
  else if (x >= 50 && x <= 250 && voltage <= 10) {
    voltage = 0;
    increase(voltage);
    analogWrite(redWire, voltage);
    }
  else if (x >= 250 && x <= 450 && voltage >= 245) {
    voltage = 255;
    decrease(voltage);
    analogWrite(redWire, voltage);
    }

  }while (x < 650 || x > 850);

return voltage;
}


int switchingVoltageBrightness(int voltage) {

  int userView;

  // Checking of all colours without this colours automatically turn on full brightness.
  analogWrite(blueWire, blueValue);
  analogWrite(greenWire, greenValue);
  analogWrite(redWire, redValue);

  lcd.clear();
  lcd.home();
  lcd.print("UP increasing");
  lcd.setCursor(0, 1);
  lcd.print("DOWN decreasing");
  delay(100);

  do {

  x = analogRead(BUTTON_PIN);
  
  if (x >= 50 && x <= 250 && voltage < 245) {
    voltage += 10;
    delay(100);
    lcd.clear();
    lcd.home();
    lcd.print(" ++ ");
    userView = map(voltage, 255, 0, 100, 0);
    lcd.setCursor(5, 1);
    lcd.print(userView);
    lcd.print("%");
    analogWrite(blackWire, voltage);
  }
  else if (x >= 250 && x <= 450 && voltage > 10) {
    voltage -= 10;
    delay(100);
    lcd.clear();
    lcd.home();
    lcd.print(" -- ");
    userView = map(voltage, 255, 0, 100, 0);
    lcd.setCursor(5, 1);
    lcd.print(userView);
    lcd.print("%");
    analogWrite(blackWire, voltage);
  }
  else if (x >= 50 && x <= 250 && voltage >= 245) {
    voltage = 255;
    delay(100);
    lcd.clear();
    lcd.home();
    lcd.print(" ++ ");
    userView = map(voltage, 255, 0, 100, 0);
    lcd.setCursor(5, 1);
    lcd.print(userView);
    lcd.print("%");
    analogWrite(blackWire, voltage);
    }
  else if (x >= 250 && x <= 450 && voltage <= 10) {
    voltage = 0;
    delay(100);
    lcd.clear();
    lcd.home();
    lcd.print(" -- ");
    userView = map(voltage, 255, 0, 100, 0);
    lcd.setCursor(5, 1);
    lcd.print(userView);
    lcd.print("%");
    analogWrite(blackWire, voltage);
    }

  }while (x < 650 || x > 850);

return voltage;
}


void printMenu() {

  lcd.clear();
  lcd.home();
  lcd.print("Programator LED");
  lcd.setCursor(0, 1);
  lcd.print("");

}


void increase(int voltage) {

    int userView;
    delay(100);
    lcd.clear();
    lcd.home();
    lcd.print("++ 10");
    userView = map(voltage, 255, 0, 0, 100);
    lcd.setCursor(5, 1);
    lcd.print(userView);
    lcd.print("%");

}


void decrease(int voltage) {

    int userView;
    delay(100);
    lcd.clear();
    lcd.home();
    lcd.print("-- 10");
    userView = map(voltage, 255, 0, 0, 100);
    lcd.setCursor(5, 1);
    lcd.print(userView);
    lcd.print("%");

}


void help() {

  lcd.clear();
  lcd.home();
  lcd.print("Up-brght Lt-red");
  lcd.setCursor(0, 1);
  lcd.print("Dn-green Rt-blue");
  delay(4000);
  lcd.clear();
  lcd.home();
  lcd.print("SELECT-options");
  lcd.setCursor(0, 1);
  lcd.print("press select");
}


void patternFade() {

int i;
  analogWrite(blackWire, 255);
  lcd.clear();
  lcd.home();
  lcd.print("Fade option");

do{

  for(i=0; i<=255; i++) {
    analogWrite(redWire, i);
    delay(10);
  }
  for(i=255; i>=0; i--) {
    analogWrite(redWire, i);
    delay(10);
  }
    for(i=0; i<=255; i++) {
    analogWrite(greenWire, i);
    delay(10);
  }
  for(i=255; i>=0; i--) {
    analogWrite(greenWire, i);
    delay(10);
  }
    for(i=0; i<=255; i++) {
    analogWrite(blueWire, i);
    delay(10);
  }
  for(i=255; i>=0; i--) {
    analogWrite(blueWire, i);
    delay(10);
  }
}while(true);

}


void patternBlink() {

bool exit = false;
int speed = 400;
  lcd.clear();
  lcd.home();
  lcd.print("  Blink option");
  delay(500);
  analogWrite(redWire, 0);
  analogWrite(greenWire, 0);
  analogWrite(blueWire, 0);
  analogWrite(blackWire, FULL);
  do {

    x = analogRead(BUTTON_PIN);
    analogWrite(blueWire, FULL);
    analogWrite(redWire, 0);
    analogWrite(greenWire, 0);
    delay(speed);
    analogWrite(blueWire, 0);
    delay(speed);

    analogWrite(greenWire, FULL);
    analogWrite(redWire, 0);
    analogWrite(blueWire, 0);
    delay(speed);
    analogWrite(greenWire, 0);
    delay(speed);

    analogWrite(redWire, FULL);
    analogWrite(greenWire, 0);
    analogWrite(blueWire, 0);
    delay(speed);
    analogWrite(redWire, 0);
    delay(speed);

    if(x >= 650 && x <=850) exit = true;
    else if(x >= 50 && x <= 250) 
    {
    speed -= 100;
    max(speed - 100, 100);     // Ensure speed doesn't go below 100
    lcd.clear();
    lcd.home();
    lcd.print("speed: ");
    lcd.print(speed);
    delay(100);
    }
    else if(x >= 250 && x <= 450)
    {
    speed += 100;
    min(speed + 100, 1000);  // Ensure speed doesn't go above 1000
    lcd.clear();
    lcd.home();
    lcd.print("speed: ");
    lcd.print(speed);
    delay(100);
    }

  }while(!exit);
analogWrite(redWire, NULL);
analogWrite(greenWire, NULL);
analogWrite(blueWire, NULL);
analogWrite(blackWire, NULL);
return;
}
