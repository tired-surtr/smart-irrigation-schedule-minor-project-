#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define pins
const int moisturePin = A0;
const int relayPin = 7;

// Moisture threshold
const int threshold = 650;

// Initialize LCD: address 0x27, 16 columns, 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(moisturePin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Relay off (active LOW)

  lcd.init();       // Initialize LCD
  lcd.backlight();  // Turn on backlight

  lcd.setCursor(0, 0);
  lcd.print("AI Irrigation");
  delay(2000);
  lcd.clear();
}

void loop() {
  int moisture = analogRead(moisturePin);

  lcd.setCursor(0, 0);
  lcd.print("Moisture: ");
  lcd.print(moisture);

  if (moisture < threshold) {
    lcd.setCursor(0, 1);
    lcd.print("Status: Watering");
    digitalWrite(relayPin, LOW); // Turn pump ON
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Status: Not Watering       ");
    digitalWrite(relayPin, HIGH); // Turn pump OFF
  }

  delay(1000);
}
