#include <Adafruit_NeoPixel.h>

#define LED_PIN 21
#define LED_PIN_A 23       // Pin connected to Data In on the LED strip
#define LED_PIN_B 26
#define LED_COUNT 110    // Number of LEDs in the strip

#define LED_COUNT_DOWN_FORT 59

#define RELAY_A 12
#define RELAY_B 27
#define RELAY_C 14

// Initialize the NeoPixel library
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripA(LED_COUNT, LED_PIN_A, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripB(LED_COUNT, LED_PIN_B, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);

  Serial.println("Hello");

  pinMode(RELAY_A, OUTPUT);
  pinMode(RELAY_B, OUTPUT);
  pinMode(RELAY_C, OUTPUT);

  digitalWrite(RELAY_A, HIGH);
  digitalWrite(RELAY_B, HIGH);
  digitalWrite(RELAY_C, HIGH);

  //  pinMode(23, OUTPUT);
  //  digitalWrite(23, HIGH);
  strip.begin();        // Initialize the strip
  strip.show();         // Turn off all LEDs at the start

  stripA.begin();        // Initialize the strip
  stripA.show();         // Turn off all LEDs at the start

  stripB.begin();        // Initialize the strip
  stripB.show();         // Turn off all LEDs at the start

}

void loop() {
  if (Serial.available()) {
    char data = Serial.read();

    if (data == 'C') {
      Serial.println("ON");
      digitalWrite(RELAY_A, LOW);
      digitalWrite(RELAY_B, LOW);
      digitalWrite(RELAY_C, LOW);
    } else if (data == 'B') {
      digitalWrite(RELAY_A, HIGH);
      digitalWrite(RELAY_B, HIGH);
      digitalWrite(RELAY_C, HIGH);
    }
  }
  
  for (int i = 0; i < LED_COUNT_DOWN_FORT - 23; i++) {
    // Set each LED to a different color (example with random colors)
    strip.setPixelColor(i, strip.Color(255, 63, 0));
  }

  for (int i = 36; i < 59; i++) {
    // Set each LED to a different color (example with random colors)
    strip.setPixelColor(i, strip.Color(0, 255, 0));
  }
  
  strip.show();         // Display all the colors
  delay(500);

  for (int i = 0; i < LED_COUNT; i++) {
    // Set each LED to a different color (example with random colors)
    stripA.setPixelColor(i, stripA.Color(255, 150, 100));
  }
  stripA.show();         // Display all the colors
  delay(500);

  for (int i = 0; i < LED_COUNT; i++) {
    // Set each LED to a different color (example with random colors)
    stripB.setPixelColor(i, stripB.Color(255, 150, 100));
  }
  stripB.show();         // Display all the colors

}
