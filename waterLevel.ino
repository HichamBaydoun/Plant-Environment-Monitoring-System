#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Library initialization with 16x2 size settings
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 or 0x3f
const int sensorPin = A0;
int waterLevel = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(sensorPin, INPUT); 
}

void loop() {
  lcd.clear();
  waterLevel = analogRead(sensorPin);
  
  lcd.setCursor(1, 0); // Set the cursor to column 1, row 0
  lcd.print("WATER LEVEL: ");
  
  lcd.setCursor(1, 1); // Set the cursor to column 1, row 1
  // Displaying water level status based on water level value:
  if (waterLevel <= 100)
    lcd.print("Empty");
  else if (waterLevel > 100 && waterLevel <= 260)
    lcd.print("Low");
  else if (waterLevel > 260 && waterLevel <= 310)
    lcd.print("Medium");
  else if (waterLevel > 310)
    lcd.print("High");
    
  lcd.setCursor(8, 1); // Set the cursor to column 8, row 1
  lcd.print(waterLevel);
  delay(1000);
  }
