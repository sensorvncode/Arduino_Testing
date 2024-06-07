#include <Wire.h>

#define TCS37425_ADDR 0x29  // Default I2C address of TCS34725

// Registers for TCS34725
#define ENABLE_REG 0x80
#define ATIME_REG 0x81
#define CONTROL_REG 0x8F
#define ID_REG 0x92
#define CDATAL 0x94
#define RDATAL 0x96
#define GDATAL 0x98
#define BDATAL 0x9A

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize the sensor
  initTCS34725();
}

void loop() {
  // Read color values
  uint16_t clear = readRegister16(CDATAL);
  uint16_t red = readRegister16(RDATAL);
  uint16_t green = readRegister16(GDATAL);
  uint16_t blue = readRegister16(BDATAL);

  // Print the values to the serial monitor
  Serial.print("Clear: ");
  Serial.print(clear);
  Serial.print(" Red: ");
  Serial.print(red);
  Serial.print(" Green: ");
  Serial.print(green);
  Serial.print(" Blue: ");
  Serial.println(blue);

  delay(1000);  // Wait for 1 second before reading again
}

void initTCS34725() {
  // Power on the sensor and enable ADC
  writeRegister(ENABLE_REG, 0x03);

  // Set integration time (e.g., 100ms)
  writeRegister(ATIME_REG, 0xD6);

  // Set control register (e.g., gain setting)
  writeRegister(CONTROL_REG, 0x00);
}

void writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(TCS37425_ADDR);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

uint16_t readRegister16(uint8_t reg) {
  Wire.beginTransmission(TCS37425_ADDR);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(TCS37425_ADDR, 2);
  uint16_t value = Wire.read();
  value |= (Wire.read() << 8);

  return value;
}
