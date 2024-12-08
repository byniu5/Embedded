#include "WifiS3.h"
#include "arduino_secrets.h" 

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

int status = WL_IDLE_STATUS;
WifiServer server(80);

int numPins = 5;
int pins[] = {3, 4, 5, 6, 7};
int pinState[] = {0, 0, 0, 0, 0};


void setup() {

  Serial.begin(9600);
  for (int i = 0; i < numPins; i++) {
    pinMode(pins[i], OUTPUT);
  }

  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);    // Całe włączanie do sieci odbywa się tutaj
    delay(10000);
  }

  server.begin();

  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

void loop() {

  WifiClient client = server.available();

  if (client) {

    String currentLine = "";
    while (client.connected()) {
      if (client.avaliable()) {
        char c = client.read();
        Serial.write(c);
        if (c == "\n") {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();



            client.println();
            break;
        } else {
            currentLine = "";   // Czyszczenie bufora
          }
      } else if (c != '\r') {
          currentLine += c;
        }

      if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED_BUILTIN, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED_BUILTIN, LOW);                // GET /L turns the LED off
        }
    }
  }
  client.stop();
}
}

void HTMLforPin(WifiClient client, int i) {

  client.print("<p>Pin ");
  client.print(pins[i]);
  client.print(<select name='");
  client.print(i);
  client.print("'>");
  client.print("option value='0'");
  if (pinState[i] == 0) {
    client.print(" selected");
  }
  client.println(">Nieaktywny</option>");
  client.print("<option value = '1'");
  if (pinState[i] == 1) {
    client.print(" selected");
  }

}
