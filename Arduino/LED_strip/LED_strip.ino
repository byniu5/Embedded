/*Trzeba zrobić tak żeby maksymalna wartość danego koloru odpowiadała jej jasności póki co jest tak że jak ustawisz np. zielony - 5 - 255 to nie świeci
Musisz ustawić na 0 - 0 to wtedy świeci na maksa*/

int blackWire = 11, greenWire = 3, redWire = 5, blueWire = 6;

int overallBrightness = 0;
int greenBrightness = 0;
int redBrightness = 0;
int blueBrightness = 0;


void setup() {

  pinMode(blackWire, OUTPUT); 
  pinMode(greenWire, OUTPUT); 
  pinMode(redWire, OUTPUT); 
  pinMode(blueWire, OUTPUT); 
  Serial.begin(9600);

  printMenu();
}

void loop() {

  if(Serial.available() > 0) {

    int choice = Serial.parseInt();
    clearSerialBuffer();
    
    switch (choice) {

      case (1): {

        brightness("black");
        analogWrite(blackWire, overallBrightness);
      
      }
      break;

      case (2): {

        brightness("green");
        analogWrite(greenWire, greenBrightness);
      
      }
      break;

      case (3): {

        brightness("red");
        analogWrite(redWire, redBrightness);
      
      }
      break;

      case (4): {

        brightness("blue");
        analogWrite(blueWire, blueBrightness);
      
      }
      break;

      case (5): {

        Serial.println("Exiting...");
        return;

      }

      default: {
        Serial.println("Invalid choice. Please select a valid option.");
      }

    }
    voltageValues();
    printMenu();
  }
  else {
    analogWrite(blackWire, overallBrightness);
    analogWrite(greenWire, greenBrightness);
    analogWrite(redWire, redBrightness);
    analogWrite(blueWire, blueBrightness);
  }

}


void brightness(String color) {

  Serial.print("Enter a voltage between 0 and 5V for ");
  Serial.println(color);

  while (Serial.available() == 0) {}

  float voltage = Serial.parseFloat();
  int brightnessValue = 0;
  clearSerialBuffer();
    
  if(voltage >= 0.0 && voltage <= 5.0)
    brightnessValue = map(voltage * 100, 0, 500, 0, 255);

    if (color == "black") {
      overallBrightness = brightnessValue;
    } else if (color == "green") {
      greenBrightness = brightnessValue;
    } else if (color == "red") {
      redBrightness = brightnessValue;
    }else if (color == "blue") {
      blueBrightness = brightnessValue;
    }

  else{
      Serial.println("Error. Value out of range. Please enter a number between 0 and 5.");
      overallBrightness = 0;
    }
}


void clearSerialBuffer() {

  while (Serial.available() > 0) {
    Serial.read();
  }
}


void printMenu() {

  Serial.println("Welcome to the configurator of the LED strip");
  Serial.println("1. Overall brightness");
  Serial.println("2. Brightness green");
  Serial.println("3. Brightness red");
  Serial.println("4. Brightness blue");
  Serial.println("5. Exit");

}


void voltageValues() {

  // map(overallBrightness, 0, 255, 255, 0);
  // map(greenBrightness, 0, 255, 255, 0);
  // map(redBrightness, 0, 255, 255, 0);
  // map(blueBrightness, 0, 255, 255, 0);

  Serial.print("Value of OVERALL BRIGHTNESS set to: ");
        Serial.println(overallBrightness);
  Serial.print("Value of GREEN set to: ");
        Serial.println(greenBrightness);
  Serial.print("Value of RED set to: ");
        Serial.println(redBrightness);
  Serial.print("Value of BLUE set to: ");
        Serial.println(blueBrightness);
  
}