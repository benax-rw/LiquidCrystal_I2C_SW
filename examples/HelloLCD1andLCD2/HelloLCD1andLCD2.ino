#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_I2C_SW.h>
#include <SoftwareWire.h>

// Hardware I2C LCD
LiquidCrystal_I2C lcd1(0x27, 16, 2);

// Software I2C
SoftwareWire myWire(A0, A1);
LiquidCrystal_I2C_SW lcd2(0x27, 16, 2, myWire);

void setup() {
    Serial.begin(9600);

    // Initialize hardware I2C LCD
    Wire.begin();
    lcd1.begin(16, 2);
    lcd1.backlight(); // Turn on backlight for hardware LCD
    lcd1.clear();
    lcd1.setCursor(0, 0); // Set cursor to top-left
    lcd1.print("Hello, Hardware!");

    // Initialize software I2C LCD
    myWire.begin();
    lcd2.begin(16, 2);
    lcd2.backlight(); // Turn on backlight for software LCD
    lcd2.clear();
    lcd2.setCursor(0, 0); // Set cursor to top-left
    lcd2.print("Hello, Software!");

    // Confirmation
    Serial.println("Messages sent to both LCDs with backlight ON!");
}

void loop() {
    // No looping functionality needed for this example
}