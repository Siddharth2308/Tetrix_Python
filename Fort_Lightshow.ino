#include <Adafruit_NeoPixel.h>

// Orange -> 255,63, 0
// Green  -> 0, 255, 0
// Highlight shade -> 255, 150, 100

#define LED_UPDATE_RATE 500

#define RELAY_GREEN   12
#define RELAY_BLUE    27
#define RELAY_YELLOW  14

#define LED_PIN_FORT  23    // Pin connected to the data pin of the WS2812B
#define LED_PIN_ARMY  21
#define LED_PIN_BACK  26

#define NUM_LEDS_FORT    20    // Number of LEDs in strip on fort
#define NUM_LEDS_ARMY    59    // Number of LEDs in strip in front of fort
#define NUM_LEDS_BACK    54    // Number of LEDs in strip around the fort

// Position specific led counts and definations below

#define JAVALI_HIGHLIGHT_TIMESTAMP 2.11F
#define JAVALI_CLOSE_TIMESTAMP 3.20F

// Fort Leds
#define KEDARESHWAR_PIN_NUMBER   5  // Change if needed
#define KEDARESHWAR_HIGHLIGHT_TIMESTAMP    4.00F

#define MAHADARWAJA_PIN_NUMBER   3  // Change if needed
#define MAHADARWAJA_TIMESTAMP    4.13F

#define CHOR_VAT_1_PIN_NUMBER   6  // Change if needed
#define CHOR_VAT_2_PIN_NUMBER   10
#define CHOR_VAT_TIMESTAMP    4.25F

#define TATABANDHI_PIN        13
#define TATABANDHI_TIMESTAMP  4.42F
#define TATABANDHI_CLOSE_TIMESTAMP  5.05F

#define BURUJ_1_PIN_NUMBER  6
#define BURUJ_2_PIN_NUMBER  12
#define BURUJ_3_PIN_NUMBER  15

#define BURUJ_1_TIMESTAMP 4.45F
#define BURUJ_2_TIMESTAMP 4.48F
#define BURUJ_3_TIMESTAMP 4.51F

#define TAALE_1_PIN_NUMBER  6
#define TAALE_2_PIN_NUMBER  14
#define TAALE_3_PIN_NUMBER    17

#define TAALE_1_TIMESTAMP 5.10F
#define TAALE_2_TIMESTAMP 5.12F
#define TAALE_3_TIMESTAMP 5.14F

#define SADAR_PIN_NUMBER  17
#define SADAR_TIMESTAMP   5.28F

#define RAJWADA_PIN_NUMBER  17
#define RAJWADA_TIMESTAMP   5.30F

#define CLOSE_ALL_TIMESTAMP 6.10

#define MARATHE_TIMESTAMP 9.15F
#define MUGHAL_TIMESTAMP  8.40F

// Army Leds

// Background Leds

char data;
unsigned long led_update_timer = 0, run_time = 0;
bool started = false, javali_executed = false, tatbandhi_executed = false, executed_once = false, descirption_done = false, close_all_executed = false;

Adafruit_NeoPixel fort_strip(NUM_LEDS_FORT, LED_PIN_FORT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel army_strip(NUM_LEDS_ARMY, LED_PIN_ARMY, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel back_strip(NUM_LEDS_BACK, LED_PIN_BACK, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(RELAY_GREEN, OUTPUT);
  pinMode(RELAY_BLUE, OUTPUT);
  pinMode(RELAY_YELLOW, OUTPUT);
  pinMode(TATABANDHI_PIN, OUTPUT);

  digitalWrite(RELAY_GREEN, HIGH);
  digitalWrite(RELAY_BLUE, HIGH);
  digitalWrite(RELAY_YELLOW, HIGH);
  digitalWrite(TATABANDHI_PIN, HIGH);
  
  Serial.begin(115200);
  Serial.println("Fort Light show script initiated. \n Press A to Start | B to Stop | C to Reset");
  
  fort_strip.begin();
  army_strip.begin();
  back_strip.begin();
  
  fort_strip.show();
  army_strip.show();
  back_strip.show();
}

void loop() {
  if(Serial.available()){
    data = Serial.read(); 
    if(data == 'A'){
      run_time = millis();
      started = true;
      Serial.println("Show started");
    } else if (data == 'B'){
      Serial.println("Show stopped");
      run_time = millis();
      started = false;
    } else if (data == 'C'){
      Serial.println("Show reset");
      run_time = millis();
      started = false;
    }
  }

  if(started){
    if(!descirption_done){
  //    Javali Highlight Logic Start
  
      if(!javali_executed && (millis() - run_time > minsToMillis(JAVALI_HIGHLIGHT_TIMESTAMP))){
        digitalWrite(RELAY_GREEN, LOW);
        javali_executed = true;
      } else if(javali_executed && (millis() - run_time > minsToMillis(JAVALI_CLOSE_TIMESTAMP))){
        digitalWrite(RELAY_GREEN, HIGH);
      }
      
  //  Javali Highlight Logic END  
  
  // Kedareshwar Highlight
      if((millis() - run_time > minsToMillis(KEDARESHWAR_HIGHLIGHT_TIMESTAMP))){
        fort_strip.setPixelColor(KEDARESHWAR_PIN_NUMBER, fort_strip.Color(255, 150, 100));
      }
  // Kedareshwar Done
  
  // MAHADARWAJA Highlight
      if((millis() - run_time > minsToMillis(MAHADARWAJA_TIMESTAMP))){
        fort_strip.setPixelColor(MAHADARWAJA_PIN_NUMBER, fort_strip.Color(255, 150, 100));
      }
  // MAHADARWAJA Done   
  
  // Chor Vat Highlight
      if((millis() - run_time > minsToMillis(CHOR_VAT_TIMESTAMP))){
        fort_strip.setPixelColor(CHOR_VAT_1_PIN_NUMBER, fort_strip.Color(255, 150, 100));
        fort_strip.setPixelColor(CHOR_VAT_2_PIN_NUMBER, fort_strip.Color(255, 150, 100));
      }
  // Chor Vat Done  
  
  // TATABANDHI Highlight
      if(!tatbandhi_executed && (millis() - run_time > minsToMillis(TATABANDHI_TIMESTAMP))){
        digitalWrite(TATABANDHI_PIN, LOW);
        tatbandhi_executed = true;
      } else if(tatbandhi_executed && (millis() - run_time > minsToMillis(TATABANDHI_CLOSE_TIMESTAMP)) && !executed_once){
        fort_strip.setPixelColor(BURUJ_1_PIN_NUMBER, fort_strip.Color(0, 0, 0));
        fort_strip.setPixelColor(BURUJ_2_PIN_NUMBER, fort_strip.Color(0, 0, 0));
        fort_strip.setPixelColor(BURUJ_3_PIN_NUMBER, fort_strip.Color(0, 0, 0));
        
        digitalWrite(TATABANDHI_PIN, HIGH);
        executed_once = true;
      }
  // TATABANDHI Done
  
  // BURUJ_1 Highlight
      if((millis() - run_time > minsToMillis(BURUJ_1_TIMESTAMP))){
        fort_strip.setPixelColor(BURUJ_1_PIN_NUMBER, fort_strip.Color(255, 150, 100));
      }
  // BURUJ_1 Done  
  
  // BURUJ_2 Highlight
      if((millis() - run_time > minsToMillis(BURUJ_2_TIMESTAMP))){
        fort_strip.setPixelColor(BURUJ_2_PIN_NUMBER, fort_strip.Color(255, 150, 100));
      }
  // BURUJ_2 Done  
  
  // BURUJ_3 Highlight
      if((millis() - run_time > minsToMillis(BURUJ_3_TIMESTAMP))){
        fort_strip.setPixelColor(BURUJ_3_PIN_NUMBER, fort_strip.Color(255, 150, 100));
      }
  // BURUJ_3 Done  
  
  // TAALE_1 Highlight
      if((millis() - run_time > minsToMillis(TAALE_1_TIMESTAMP))){
        fort_strip.setPixelColor(TAALE_1_PIN_NUMBER, fort_strip.Color(255, 150, 100));
      }
  // TAALE_1 Done  
  
  // TAALE_2 Highlight
      if((millis() - run_time > minsToMillis(TAALE_2_TIMESTAMP))){
        fort_strip.setPixelColor(TAALE_2_PIN_NUMBER, fort_strip.Color(255, 150, 100));
      }
  // TAALE_2 Done  
  
  // TAALE_3 Highlight
      if((millis() - run_time > minsToMillis(TAALE_3_TIMESTAMP))){
        fort_strip.setPixelColor(TAALE_3_PIN_NUMBER, fort_strip.Color(255, 150, 100));
      }
  // TAALE_3 Done  
  
  // SADAR Highlight
      if((millis() - run_time > minsToMillis(SADAR_TIMESTAMP))){
        fort_strip.setPixelColor(SADAR_PIN_NUMBER, fort_strip.Color(255, 150, 100));
      }
  // SADAR Done  
  // Rajwada Highlight
      if((millis() - run_time > minsToMillis(RAJWADA_TIMESTAMP))){
        fort_strip.setPixelColor(RAJWADA_PIN_NUMBER, fort_strip.Color(255, 150, 100));
        descirption_done = true;
      }
  // Rajwada Done  
   }

    if(!close_all_executed && (millis() - run_time > minsToMillis(CLOSE_ALL_TIMESTAMP))){
      for (int i = 0; i < NUM_LEDS_FORT; i++) {
        // Set each LED to a different color (example with random colors)
        fort_strip.setPixelColor(i, fort_strip.Color(0, 0, 0));
      }
      close_all_executed = true;
    }

//    Marathe highlight
      if((millis() - run_time > minsToMillis(MARATHE_TIMESTAMP))){
        for (int i = 0; i < NUM_LEDS_ARMY - 23; i++) {
          // Set each LED to a different color (example with random colors)
          fort_strip.setPixelColor(i, fort_strip.Color(255, 63, 0));
        }
        for (int i = 36; i < NUM_LEDS_ARMY; i++) {
          // Set each LED to a different color (example with random colors)
          fort_strip.setPixelColor(i, fort_strip.Color(0, 255, 0));
        }
      }

//    Mughal highlight
      if((millis() - run_time > minsToMillis(MUGHAL_TIMESTAMP))){
        for (int i = 36; i < NUM_LEDS_ARMY; i++) {
          // Set each LED to a different color (example with random colors)
          fort_strip.setPixelColor(i, fort_strip.Color(0, 255, 0));
        }
      }
      

  }
  

  if(millis() - led_update_timer > LED_UPDATE_RATE){
    fort_strip.show();
    army_strip.show();
    back_strip.show();
    led_update_timer = millis();
  }
}

unsigned long minsToMillis(float minutes) {
    return (unsigned long)(minutes * 60000);
}
