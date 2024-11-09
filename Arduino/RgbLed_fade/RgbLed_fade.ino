int red = 9;         // the PWM pin the red LED is attached to
int green = 10;      // the PWM pin the green LED is attached to
int blue = 11;       // the PWM pin the blue LED is attached to
int brightness = 1;  // how bright the LED is
int fadeAmount = 5;  // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup() {
  // declare pins 9, 10, and 11 to be outputs:
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // fade the red LED
  fadeLED(red);
  // fade the green LED
  fadeLED(green);
  // fade the blue LED
  fadeLED(blue);
}

// Function to fade an LED in and out
void fadeLED(int pin) {
  brightness = 1;
  fadeAmount = 4;
  while (brightness > 0) {
    analogWrite(pin, brightness);
    brightness += fadeAmount;

    // reverse the direction of the fading at the ends of the fade
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }

    // wait for 30 milliseconds to see the dimming effect
    delay(20);
  }
}

