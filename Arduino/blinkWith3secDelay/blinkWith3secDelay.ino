int ledPin = 13;
int delayPeriod = 250;

void setup()
{
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  static int count = 0;
  digitalWrite(ledPin, HIGH);
  delay(delayPeriod - count*7);
  digitalWrite(ledPin, LOW);
  delay(delayPeriod - count*7);
  count ++;
  if (count == 29)
  {
    count++;
    digitalWrite(ledPin, HIGH);
    delay(2000);
    digitalWrite(ledPin, LOW);
  }
  if (count == 30)
  {
    count = 0;
    delay(3000);
  }
}