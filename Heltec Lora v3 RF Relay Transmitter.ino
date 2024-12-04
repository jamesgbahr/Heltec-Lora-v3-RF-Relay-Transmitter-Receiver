#define HELTEC_POWER_BUTTON  
#include <heltec_unofficial.h>
#include <images.h>

#define BUTTON1_PIN 0  // Change to your actual pin numbers
#define BUTTON2_PIN 1  
#define BUTTON3_PIN 2

#define PAUSE 300  
#define FREQUENCY 866.3  
#define BANDWIDTH 250.  
#define SPREADING_FACTOR 9  
#define TRANSMIT_POWER 5 // Set a valid transmit power


#define _1731044846953_width 128
#define _1731044846953_height 64

String buttonState = "000"; // Initial state for three buttons  
long last_tx = 0; // Initialize last_tx to 0



void setup() {
  heltec_setup();
  heltec_ve(true);
  Serial.begin(115200); // Initialize serial communication at 115200 baud
  Serial.println();

  // Initialize the display  
  display.init();
  display.setFont(ArialMT_Plain_10);

  // Display startup image
  display.clear();

  display.drawXbm(0, 0, _1731044846953_width, _1731044846953_height, _1731044846953_bits);
  display.display();
  delay(2000); // Display the image for 2 seconds

  // Initialize button pins
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
 
  radio.begin();
  radio.setFrequency(FREQUENCY);
  radio.setBandwidth(BANDWIDTH);
  radio.setSpreadingFactor(SPREADING_FACTOR);
  radio.setOutputPower(TRANSMIT_POWER);
  radio.startReceive();
}

void loop() {
  if (millis() - last_tx > PAUSE) {
    // Read button states  
    buttonState[0] = digitalRead(BUTTON1_PIN) == LOW ? '1' : '0';
    buttonState[1] = digitalRead(BUTTON2_PIN) == LOW ? '1' : '0';
    buttonState[2] = digitalRead(BUTTON3_PIN) == LOW ? '1' : '0';

    // Transmit button state  
    radio.transmit(buttonState);
    Serial.println("Transmitted button state: " + buttonState);
    last_tx = millis();
  }

  // Display button states on OLED  
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0, "FlameFX Status");
  display.drawString(0, 10, "FX Relay 1: " + String(buttonState[0] == '1' ? "ON" : "OFF"));
    display.drawString(0, 20, "FX Relay 2: " + String(buttonState[1] == '1' ? "ON" : "OFF"));
    display.drawString(0, 30, "FX Relay 3: " + String(buttonState[2] == '1' ? "ON" : "OFF"));
  display.display(); // Update the display  
}
