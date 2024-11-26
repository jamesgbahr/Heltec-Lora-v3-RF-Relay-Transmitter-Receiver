#define HELTEC_POWER_BUTTON   // must be before "#include <heltec_unofficial.h>"
#include <heltec_unofficial.h>

// Relay pin definitions
#define RELAY1_PIN    42  // GPIO pin for Relay 1
#define RELAY2_PIN    4   // GPIO pin for Relay 2
#define RELAY3_PIN    15  // GPIO pin for Relay 3 (Adjust as needed)

// Frequency settings
#define FREQUENCY           866.3       // for Europe (adjust if needed)
#define BANDWIDTH           250.0
#define SPREADING_FACTOR    9
#define TRANSMIT_POWER      5

String rxdata;
volatile bool rxFlag = false;
long counter = 0;

void setup() {
  heltec_setup();

  // Initialize the display
  display.init();
  display.setFont(ArialMT_Plain_10);
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0, "LoRa Receiver");
  display.display(); // Update display once

  // Initialize Serial Communication
  Serial.begin(115200);  // Initialize Serial Monitor at 115200 baud rate
  Serial.println("Radio init");

  // Initialize LoRa radio
  RADIOLIB_OR_HALT(radio.begin());

  // Set the callback function for received packets
  radio.setDio1Action(rx);

  // Set radio parameters
  Serial.printf("Frequency: %.2f MHz\n", FREQUENCY);
  RADIOLIB_OR_HALT(radio.setFrequency(FREQUENCY));
  Serial.printf("Bandwidth: %.1f kHz\n", BANDWIDTH);
  RADIOLIB_OR_HALT(radio.setBandwidth(BANDWIDTH));
  Serial.printf("Spreading Factor: %i\n", SPREADING_FACTOR);
  RADIOLIB_OR_HALT(radio.setSpreadingFactor(SPREADING_FACTOR));
  Serial.printf("TX power: %i dBm\n", TRANSMIT_POWER);
  RADIOLIB_OR_HALT(radio.setOutputPower(TRANSMIT_POWER));

  // Initialize relay pins as outputs
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(RELAY3_PIN, OUTPUT);

  // Ensure all relays are off initially
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);
  digitalWrite(RELAY3_PIN, HIGH);

  // Start receiving
  RADIOLIB_OR_HALT(radio.startReceive(RADIOLIB_SX126X_RX_TIMEOUT_INF));
}

void loop() {
  heltec_loop();

  // If a packet was received, display it and the RSSI and SNR
  if (rxFlag) {
    rxFlag = false;
    radio.readData(rxdata);
    if (_radiolib_status == RADIOLIB_ERR_NONE) {
      // Print received data to the Serial Monitor
      Serial.printf("RX [%s]\n", rxdata.c_str());

      // Update relay states based on received data
      handleRelayActivation(rxdata);
      
      // Display relay states on the OLED
      updateOLED();
    }
    // Restart receiving
    RADIOLIB_OR_HALT(radio.startReceive(RADIOLIB_SX126X_RX_TIMEOUT_INF));
  }
}

// Interrupt function to handle received data
void rx() {
  rxFlag = true;
}

// Function to handle relay activation based on received data
void handleRelayActivation(String data) {
  if (data == "100") {
    // Relay 1 ON, others OFF
    digitalWrite(RELAY1_PIN, LOW);   // ON
    digitalWrite(RELAY2_PIN, HIGH);  // OFF
    digitalWrite(RELAY3_PIN, HIGH);  // OFF
  } else if (data == "010") {
    // Relay 2 ON, others OFF
    digitalWrite(RELAY1_PIN, HIGH);  // OFF
    digitalWrite(RELAY2_PIN, LOW);   // ON
    digitalWrite(RELAY3_PIN, HIGH);  // OFF
  } else if (data == "001") {
    // Relay 3 ON, others OFF
    digitalWrite(RELAY1_PIN, HIGH);  // OFF
    digitalWrite(RELAY2_PIN, HIGH);  // OFF
    digitalWrite(RELAY3_PIN, LOW);   // ON
  } else if (data == "000") {
    // All relays OFF
    digitalWrite(RELAY1_PIN, HIGH);  // OFF
    digitalWrite(RELAY2_PIN, HIGH);  // OFF
    digitalWrite(RELAY3_PIN, HIGH);  // OFF
  }
}

// Function to update OLED with relay states
void updateOLED() {
  // Get current relay states
  String relay1Status = digitalRead(RELAY1_PIN) ? "OFF" : "ON";
  String relay2Status = digitalRead(RELAY2_PIN) ? "OFF" : "ON";
  String relay3Status = digitalRead(RELAY3_PIN) ? "OFF" : "ON";

  // Display relay states on OLED
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0, "Relay Status:");
  display.drawString(0, 20, "Relay 1: " + relay1Status);
  display.drawString(0, 40, "Relay 2: " + relay2Status);
  display.drawString(0, 60, "Relay 3: " + relay3Status);
  display.display(); // Update OLED display
}
