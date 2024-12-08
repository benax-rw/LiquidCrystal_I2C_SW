#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_I2C_SW.h>
#include <SoftwareWire.h>

// Hardware I2C LCD
LiquidCrystal_I2C lcd1(0x27, 16, 2);

// Software I2C
SoftwareWire myWire(A0, A1);
LiquidCrystal_I2C_SW lcd2(0x27, 16, 2, myWire);

SoftwareWire myWire1(A2, A3);
LiquidCrystal_I2C_SW lcd3(0x27, 16, 2, myWire1);

SoftwareWire myWire2(2, 3);
LiquidCrystal_I2C_SW lcd4(0x27, 16, 2, myWire2);

SoftwareWire myWire3(4, 5);
LiquidCrystal_I2C_SW lcd5(0x27, 16, 2, myWire3);

SoftwareWire myWire4(6, 7);
LiquidCrystal_I2C_SW lcd6(0x27, 16, 2, myWire4);

void setup() {
    Serial.begin(9600);

    // Initialize hardware I2C LCD
    Wire.begin();
    lcd1.begin(16, 2);
    lcd1.backlight(); // Turn on backlight for hardware LCD
    lcd1.clear();
    lcd1.setCursor(0, 0); // Set cursor to top-left
    lcd1.print("Hello, LCD1 (HW)!");

    // Initialize software I2C LCD
    myWire.begin();
    lcd2.begin(16, 2);
    lcd2.backlight(); // Turn on backlight for software LCD
    lcd2.clear();
    lcd2.setCursor(0, 0); // Set cursor to top-left
    lcd2.print("Hello, LCD2 (SW)!");

    // Initialize software I2C LCD3
    myWire.begin();
    lcd3.begin(16, 2);
    lcd3.backlight(); // Turn on backlight for software LCD
    lcd3.clear();
    lcd3.setCursor(0, 0); // Set cursor to top-left
    lcd3.print("Hello, LCD3(SW)!");

    // Initialize software I2C LCD4
    myWire.begin();
    lcd4.begin(16, 2);
    lcd4.backlight(); // Turn on backlight for software LCD
    lcd4.clear();
    lcd4.setCursor(0, 0); // Set cursor to top-left
    lcd4.print("Hello, LCD4(SW)!");

    // Initialize software I2C LCD5
    myWire.begin();
    lcd5.begin(16, 2);
    lcd5.backlight(); // Turn on backlight for software LCD
    lcd5.clear();
    lcd5.setCursor(0, 0); // Set cursor to top-left
    lcd5.print("Hello, LCD5(SW)!");    

    // Initialize software I2C LCD5
    myWire.begin();
    lcd6.begin(16, 2);
    lcd6.backlight(); // Turn on backlight for software LCD
    lcd6.clear();
    lcd6.setCursor(0, 0); // Set cursor to top-left
    lcd6.print("Hello, LCD6(SW)!");

    // Confirmation
    Serial.println("Messages sent to both LCDs with backlight ON!");
}

void loop() {
    // No looping functionality needed for this example
}