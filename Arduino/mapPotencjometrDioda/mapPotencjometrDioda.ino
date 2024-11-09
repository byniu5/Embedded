//Numer analogowego pinu do którego podłączony jest potencjometr
#define POTENCJOMETR_PIN A0

//Numer pinu do którego podłaćzona jest dioda LED
#define LED_PIN 3


void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() 
{
  int value = analogRead(POTENCJOMETR_PIN);

  //Za pomocą funkcji map możemy przeskalować wartość z zakresu potencjometru 0-1023 na inny zakres
  int bright = map(value, 0, 1023, 0, 255);

  //Ustawienie jasności za pomocą wyjścia PWM od 0-255
  analogWrite(LED_PIN, bright);

  Serial.print("Potencjometr: ");
  Serial.print(value);
  Serial.print("  Jasność LED: ");
  Serial.println(bright);

  delay(100);
}
