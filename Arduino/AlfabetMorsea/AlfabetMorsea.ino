#include "Arduino_LED_Matrix.h"   // Include the LED_Matrix library

ArduinoLEDMatrix matrix;          // Create an instance of the ArduinoLEDMatrix class

int dot = 600;
int dash = 1800;
char* letters[] = {".-","-...","-.-.","-..",".","..-.","-.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--..",};
char* numbers[] = {"-----",".----","..---","...--","....-",".....","-....","--...","---..","----."};



void setup() {
  Serial.begin(9600);           // Initialize serial communication at a baud rate of 115200
  matrix.begin();                 // Initialize the LED matrix

}

void loop() {
  //Load and display the "big heart" frame provided by the library
  //matrix.loadFrame(LEDMATRIX_HEART_BIG);
  //Turn off the display
  //matrix.clear();
  char ch;
  if(Serial.available() > 0){     //Sprawdza czy są jakieś dane na buforze
    ch = Serial.read();           //Odczytuje ciąg znaków z bufora i zapisuje w zmiennej ch
    if(ch >= 'a' && ch <= 'z'){       //Tutaj ch oraz litery zamieniane są automatycznie na ich adresy liczbowe z kodu ASCII
      flashSequence(letters[ch - 'a']);   //Te adresy liczbowe są od siebie odejmowane
    }
    else if(ch >= 'A' && ch <= 'Z'){    //To samo
      flashSequence(letters[ch - 'A']);
    }
    else if(ch >= '0' && ch <= '9'){
      flashSequence(numbers[ch - '0']);
    }
    else if(ch == ' '){   //Koniec wyrazu; przerwa między wyrazami
      delay(dot * 7);     
    }
  }
}

void flashSequence(char* sequence){   //char* sequence przynosi wartość w postaci np. "--.."
  int i = 0;
  while(sequence[i] != NULL){         //sequence[0] z tego przykładu to '-'
    flashDotOrDash(sequence[i]);      //'-' przenoszone jest do funkcji flashDotOrDash
    i++;
  }
  delay(dash);  //Koniec litery; przerwa między literami
}

void flashDotOrDash(char dotOrDash){    //Tu jedynie rozpoznaję kropkę i linię
  matrix.loadFrame(LEDMATRIX_HEART_BIG);
  if(dotOrDash == '.'){
    delay(dot);
  }
  else{
    delay(dash);
  }
  matrix.clear();   //Przerwa pomiędzy znakiem alfabetu Morsea
  delay(dot);
}

const uint32_t heart[] = {
	0x3184a444,
	0x44042081,
	0x100a0040
};