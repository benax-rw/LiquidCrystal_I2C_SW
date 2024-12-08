#include "LiquidCrystal_I2C_SW.h"

LiquidCrystal_I2C_SW::LiquidCrystal_I2C_SW(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows, SoftwareWire &wire) {
    _Addr = lcd_Addr;
    _cols = lcd_cols;
    _rows = lcd_rows;
    _wire = &wire; // Assign the SoftwareWire object
    _backlightval = LCD_BACKLIGHT;
}

void LiquidCrystal_I2C_SW::begin(uint8_t cols, uint8_t rows, uint8_t charsize) {
    _wire->begin();
    Serial.println("Initializing LCD...");

    expanderWrite(0x00);
    delay(50);

    // Send initialization sequence
    write4bits(0x03 << 4);
    delay(5);

    write4bits(0x03 << 4);
    delay(5);

    write4bits(0x03 << 4);
    delay(5);

    write4bits(0x02 << 4); // 4-bit mode
    delay(5);

    // Basic commands
    command(LCD_FUNCTIONSET | LCD_2LINE | LCD_5x8DOTS); // Function set
    command(LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF); // Display ON
    command(LCD_CLEARDISPLAY); // Clear display
    delay(2);
    command(LCD_ENTRYMODESET | LCD_ENTRYLEFT); // Entry mode
    delay(2);

    Serial.println("LCD initialized and ready.");
}

void LiquidCrystal_I2C_SW::setCursor(uint8_t col, uint8_t row) {
    static const uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    if (row > _numlines) {
        row = _numlines - 1; // Clamp to max row count
    }
    command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void LiquidCrystal_I2C_SW::clear() {
    command(LCD_CLEARDISPLAY);
    delayMicroseconds(2000);
}

void LiquidCrystal_I2C_SW::home() {
    command(LCD_RETURNHOME);
    delayMicroseconds(2000);
}

void LiquidCrystal_I2C_SW::noDisplay() {
    _displaycontrol &= ~LCD_DISPLAYON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LiquidCrystal_I2C_SW::display() {
    _displaycontrol |= LCD_DISPLAYON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LiquidCrystal_I2C_SW::noBacklight() {
    _backlightval = LCD_NOBACKLIGHT;
    expanderWrite(0);
}

void LiquidCrystal_I2C_SW::backlight() {
    _backlightval = LCD_BACKLIGHT;
    expanderWrite(0);
}

inline void LiquidCrystal_I2C_SW::command(uint8_t value) {
    send(value, 0);
}

inline size_t LiquidCrystal_I2C_SW::write(uint8_t value) {
    send(value, Rs);
    return 1;
}

void LiquidCrystal_I2C_SW::send(uint8_t value, uint8_t mode) {
    uint8_t highnib = value & 0xf0;
    uint8_t lownib = (value << 4) & 0xf0;
    write4bits((highnib) | mode);
    write4bits((lownib) | mode);
}

void LiquidCrystal_I2C_SW::write4bits(uint8_t value) {
    expanderWrite(value);
    pulseEnable(value);
}

void LiquidCrystal_I2C_SW::expanderWrite(uint8_t _data) {
    _wire->beginTransmission(_Addr);
    _wire->write((int)(_data) | _backlightval);
    _wire->endTransmission();
    delay(1); // Add small delay
}

void LiquidCrystal_I2C_SW::pulseEnable(uint8_t _data) {
    expanderWrite(_data | En);
    delayMicroseconds(1);
    expanderWrite(_data & ~En);
    delayMicroseconds(50);
}