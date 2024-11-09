/*
  Odczytywanie wartości sygnału z potencjometru
*/
//Numer analogowego pinu do którego podłączony jest potencjometr
#define POTENCJOMETR_PIN 0

void setup() 
{
  //Ustawienie komunikacji z komputerem na 57600 bodów (nie wiem co to)
  Serial.begin(9600);
  //Oczekiwanie na uaktywnienie portu
  while(!Serial);
}

void loop() 
{
  //Odczytywanie wartości
  int value = analogRead(POTENCJOMETR_PIN);

  //Odczytanie wartości
  Serial.println(value, DEC);

  //Oczekiwanie 100 ms
  delay(100);
}
