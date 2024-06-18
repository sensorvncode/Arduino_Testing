#include <Wire.h>

#define BMP180_ADDRESS 0x77  // I2C address of BMP180

// Calibration coefficients
int16_t AC1, AC2, AC3;
uint16_t AC4, AC5, AC6;
int16_t BMP_B1, B2, MB, MC, MD;  // Renamed B1 to BMP_B1
int32_t B5;  // Variable used in temperature and pressure calculations

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Read calibration data from the BMP180 sensor
  readCalibrationData();
}

void loop() {
  // Read temperature and pressure
  int32_t temperature = readTemperature();
  int32_t pressure = readPressure();

  // Display the results
  Serial.print("Temperature: ");
  Serial.print(temperature / 10.0);
  Serial.println(" *C");

  Serial.print("Pressure: ");
  Serial.print(pressure / 100.0);
  Serial.println(" Pa");

  delay(5000);  // Delay for 5 seconds before the next reading
}

void writeRegister(uint8_t reg, uint8_t value) {
  // Write a byte to a BMP180 register using I2C
  Wire.beginTransmission(BMP180_ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

uint8_t readRegister(uint8_t reg) {
  // Read a byte from a BMP180 register using I2C
  Wire.beginTransmission(BMP180_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(BMP180_ADDRESS, 1);
  return Wire.read();
}

uint16_t read16(uint8_t reg) {
  // Read a 16-bit value from a BMP180 register using I2C
  Wire.beginTransmission(BMP180_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(BMP180_ADDRESS, 2);
  uint16_t value = (Wire.read() << 8) | Wire.read();
  return value;
}

void readCalibrationData() {
  // Read calibration coefficients from BMP180
  AC1 = read16(0xAA);
  AC2 = read16(0xAC);
  AC3 = read16(0xAE);
  AC4 = read16(0xB0);
  AC5 = read16(0xB2);
  AC6 = read16(0xB4);
  BMP_B1 = read16(0xB6);  // Use BMP_B1 instead of B1
  B2 = read16(0xB8);
  MB = read16(0xBA);
  MC = read16(0xBC);
  MD = read16(0xBE);
}

int32_t readTemperature() {
  // Read temperature from BMP180 sensor
  writeRegister(0xF4, 0x2E);  // Start temperature measurement
  delay(5);  // Wait for conversion to complete

  int32_t UT = read16(0xF6);  // Read raw temperature

  int32_t X1 = ((UT - (int32_t)AC6) * (int32_t)AC5) >> 15;
  int32_t X2 = ((int32_t)MC << 11) / (X1 + (int32_t)MD);
  B5 = X1 + X2;
  int32_t temperature = (B5 + 8) >> 4;  // Temperature in 0.1°C

  return temperature;
}

int32_t readPressure() {
  // Read pressure from BMP180 sensor
  writeRegister(0xF4, 0x34);  // Start pressure measurement
  delay(5);  // Wait for conversion to complete

  int32_t UP = read16(0xF6) << 8 | readRegister(0xF8);  // Read raw pressure

  UP >>= (8 - 3);  // Adjust for oversampling setting 3

  int32_t B6 = B5 - 4000;
  int32_t X1 = (B2 * (B6 * B6 >> 12)) >> 11;
  int32_t X2 = (AC2 * B6) >> 11;
  int32_t X3 = X1 + X2;
  int32_t B3 = (((AC1 * 4 + X3) << 1) + 2) >> 2;
  X1 = (AC3 * B6) >> 13;
  X2 = (BMP_B1 * (B6 * B6 >> 12)) >> 16;  // Use BMP_B1 instead of B1
  X3 = ((X1 + X2) + 2) >> 2;
  uint32_t B4 = (AC4 * (uint32_t)(X3 + 32768)) >> 15;
  uint32_t B7 = ((uint32_t)UP - B3) * (50000 >> 3);
  int32_t pressure;

  if (B7 < 0x80000000) {
    pressure = (B7 << 1) / B4;
  } else {
    pressure = (B7 / B4) << 1;
  }

  X1 = (pressure >> 8) * (pressure >> 8);
  X1 = (X1 * 3038) >> 16;
  X2 = (-7357 * pressure) >> 16;
  pressure = pressure + ((X1 + X2 + 3791) >> 4);  // Pressure in Pa

  return pressure;
}
