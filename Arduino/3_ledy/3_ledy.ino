int greenPin = 11;
int yellowPin = 10;
int redPin = 9;
string userColor;
string userPrompt = "Please Enter Color (Green/Yellow/Red)";
float brightness = 0.00;

void setup() {
  Serial.begin(9600);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);

  //Ustawienie wszystkich diod LED na wyłączone  
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(redPin, LOW);

  //Wyświetlenie wiadomości powitalnej
  Serial.println(userPrompt);
}

void loop() {
  if (Serial.available() > 0) {
  
  userColor = Serial.readStringUntil('\n');   // Odczyt linii zakończonej znakiem nowej linii
  userColor.trim();         // Usunięcie białych znaków z początku i końca stringa
  userColor.toLowerCase();  // Ta sprytna funkcja zamienia wszystkie znaki w stringu na małe literki ;)
  
  if (userColor.equals("green") || userColor.equals("red") || userColor.equals("yellow"))
  bright();

  if (userColor.equals("green")) {
    analogWrite(greenPin, brightness);
    analogWrite(yellowPin, NULL);
    analogWrite(redPin, NULL);
    clearSerialBuffer();   // Opróżnienie bufora
  }
  else if (userColor.equals("yellow")) {
    analogWrite(yellowPin, brightness);
    analogWrite(greenPin, NULL);
    analogWrite(redPin, NULL);
    clearSerialBuffer();   // Opróżnienie bufora
  }
  else if (userColor.equals("red")) {
    analogWrite(redPin, brightness);
    analogWrite(greenPin, NULL);
    analogWrite(yellowPin, NULL);
    clearSerialBuffer();   // Opróżnienie bufora
  }
  

  else if ((userColor != "red") && (userColor != "green") && (userColor != "yellow")) {
    //Jeśli użytkownik wprowadził nieznany kolor
    Serial.println("Unknown color. Please enter Green, Yellow, or Red.");
  }

  // Po każdej iteracji ponownie wyświetlamy prośbę o wprowadzenie koloru
    Serial.println(userPrompt);
} 
}

//////////////////////////// Ustawianie jasności /////////////////////////////////////////////////

float bright() {
    
    Serial.println("Wpisz napięcie w granicach od 0 do 5V");
    
    while (Serial.available() == 0) {
      // Nic nie rób, czekaj na dane
    }

   float voltage = Serial.parseFloat();     // Pzyjmuję wartość float z Serial monitora

  if(voltage >= 0.0 && voltage <= 5.0){
    brightness = map(voltage * 100, 0, 500, 0, 255);
  }
  else{
    Serial.println("Błąd: Wartość poza zakresem. Wprowadź liczbę od 0 do 5.");
    brightness = 0;   // Ustawienie jasności na 0 w przypadku błędu
  }
return (brightness);
}

//////////////////////////// Czyszczenie bufora /////////////////////////////////////////////////

void clearSerialBuffer() {
  while (Serial.available() > 0) {
    Serial.read(); // Odczyt i zignorowanie wszystkich danych
  }
}
