/*Nierozwiązany problem: 
Program nie utrzymuję wartości wpisanej w Serial monitor*/
/*Złącza należy podłączyć do 3 i GND i multimetru*/
int outputPin = A4;
float lastVoltage = 0.0;

void setup() {
  pinMode(outputPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Wpisz napięcie w granicach od 0 do 5V");
}

void loop() {
  if(Serial.available() > 0){
    //char ch = Serial.read();        //Tutaj dane są przekazywane jako string ale to później wymaga ich konwersji więc niezalecane w tym przypadku
    float ch = Serial.parseFloat();   ////Zmodyfikowana wersja przyjmująca wartości float a nie znaki ASCII
    
    if(ch >= 0.0 && ch <= 5.0){
    
      //int volts = (ch - '0') * 51;    //0 w tabeli znaków ASCII przyjmuję kod 048, jest ono odejmowane od wartości większej dając liczbę prawidłową //Mnożymy przez 51, ponieważ zakres na wyjściach analogowych wyraża się od 0 do 255
      int volts = map(ch * 100, 0, 500, 0, 255);    ////Funkcja mapująca wartości z tych zrozumiałych dla użytkownika od 0.0 do 5.0 na 0 do 255
      analogWrite(outputPin, volts);   
      lastVoltage = ch;
      
      Serial.print("Wartość PWM ustawiona na: ");
      Serial.println(volts);
    }
    else{
      //Informacja o błędzie
      Serial.println("Błąd: Wartość poza zakresem. Wprowadź liczbę od 0 do 5.");
    }
    clearSerialBuffer(); // Opróżnienie bufora po błędzie lub zakończeniu odczytu
  }
    else{
      int volts = map(lastVoltage * 100, 0, 500, 0, 255);
      analogWrite(outputPin, volts);
    
  }
}

//////////////////////////// Czyszczenie bufora /////////////////////////////////////////////////

void clearSerialBuffer() {
  while (Serial.available() > 0) {
    Serial.read(); // Odczyt i zignorowanie wszystkich danych
  }
}

