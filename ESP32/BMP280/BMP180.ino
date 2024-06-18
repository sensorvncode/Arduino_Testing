#include <Wire.h>

#define BMP180_ADDRESS 0x77  // I2C address of BMP180

// Calibration coefficients
int16_t AC1, AC2, AC3;
uint16_t AC4, AC5, AC6;
int16_t B1_coef, B2_coef, MB_coef, MC_coef, MD_coef;
int32_t B5;  // Declare B5 as a global variable

void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println("Code written by sensorvn.com");
  delay(5000);
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
  Serial.println(" hPa");
  delay(1000);
}

void writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(BMP180_ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

uint8_t readRegister(uint8_t reg) {
  Wire.beginTransmission(BMP180_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(BMP180_ADDRESS, 1);
  return Wire.read();
}

uint16_t read16(uint8_t reg) {
  Wire.beginTransmission(BMP180_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(BMP180_ADDRESS, 2);
  uint16_t value = (Wire.read() << 8) | Wire.read();
  return value;
}

void readCalibrationData() {
  AC1 = read16(0xAA);
  AC2 = read16(0xAC);
  AC3 = read16(0xAE);
  AC4 = read16(0xB0);
  AC5 = read16(0xB2);
  AC6 = read16(0xB4);
  B1_coef = read16(0xB6);
  B2_coef = read16(0xB8);
  MB_coef = read16(0xBA);
  MC_coef = read16(0xBC);
  MD_coef = read16(0xBE);
}

int32_t readTemperature() {
  writeRegister(0xF4, 0x2E);
  delay(5);  // Wait for conversion to complete

  int32_t UT = read16(0xF6);

  int32_t X1 = ((UT - (int32_t)AC6) * (int32_t)AC5) >> 15;
  int32_t X2 = ((int32_t)MC_coef << 11) / (X1 + MD_coef);
  B5 = X1 + X2;
  int32_t temperature = (B5 + 8) >> 4;

  return temperature;
}

int32_t readPressure() {
  writeRegister(0xF4, 0x34);
  delay(5);  // Wait for conversion to complete

  int32_t UP = read16(0xF6);
  UP = (UP << 8) | readRegister(0xF8);
  UP >>= (8 - 3);  // For standard sea level pressure, use oversampling setting 3

  int32_t B6 = B5 - 4000;
  int32_t X1 = (B2_coef * (B6 * B6 >> 12)) >> 11;
  int32_t X2 = AC2 * B6 >> 11;
  int32_t X3 = X1 + X2;
  int32_t B3 = (((AC1 * 4 + X3) << 3) + 2) >> 2;
  X1 = AC3 * B6 >> 13;
  X2 = (B1_coef * (B6 * B6 >> 12)) >> 16;
  X3 = ((X1 + X2) + 2) >> 2;
  uint32_t B4 = AC4 * (uint32_t)(X3 + 32768) >> 15;
  uint32_t B7 = ((uint32_t)UP - B3) * (50000 >> 3);
  int32_t p;

  if (B7 < 0x80000000) {
    p = (B7 * 2) / B4;
  } else {
    p = (B7 / B4) * 2;
  }

  X1 = (p >> 8) * (p >> 8);
  X1 = (X1 * 3038) >> 16;
  X2 = (-7357 * p) >> 16;
  p = p + ((X1 + X2 + 3791) >> 4);

  return p;
}
