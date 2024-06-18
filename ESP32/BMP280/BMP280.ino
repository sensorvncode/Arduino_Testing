#include <Wire.h>

// BMP280 default address.
#define BMP280_ADDRESS 0x76

// BMP280 registers.
#define BMP280_REG_TEMP_XLSB 0xFC
#define BMP280_REG_TEMP_LSB 0xFB
#define BMP280_REG_TEMP_MSB 0xFA
#define BMP280_REG_PRESS_XLSB 0xF9
#define BMP280_REG_PRESS_LSB 0xF8
#define BMP280_REG_PRESS_MSB 0xF7
#define BMP280_REG_CONFIG 0xF5
#define BMP280_REG_CTRL_MEAS 0xF4
#define BMP280_REG_ID 0xD0
#define BMP280_REG_RESET 0xE0

// Calibration data registers.
#define BMP280_REG_CALIB_00 0x88
#define BMP280_REG_CALIB_25 0xA1

// Calibration parameters.
uint16_t dig_T1;
int16_t dig_T2, dig_T3;
uint16_t dig_P1;
int16_t dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
int32_t t_fine;

// Function prototypes.
void writeRegister(uint8_t reg, uint8_t value);
uint8_t readRegister(uint8_t reg);
void readRegisters(uint8_t reg, uint8_t *buffer, uint8_t length);
void readCalibrationData();
int32_t compensateTemperature(int32_t adc_T);
uint32_t compensatePressure(int32_t adc_P);
void initializeBMP280();
void readSensorData(int32_t &temperature, uint32_t &pressure);

void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println("Code written by sensorvn.com");
  delay(5000);
  Wire.begin();
  initializeBMP280();
}

void loop() {
  int32_t temperature;
  uint32_t pressure;
  readSensorData(temperature, pressure);

  // Print temperature and pressure.
  Serial.print("Temperature: ");
  Serial.print(temperature / 100.0);
  Serial.println(" °C");
  Serial.print("Pressure: ");
  Serial.print(pressure / 25600.0);
  Serial.println(" hPa");

  delay(1000);
}

void initializeBMP280() {
  // Read and verify chip ID.
  uint8_t chipID = readRegister(BMP280_REG_ID);
  if (chipID != 0x58) {
    Serial.println("BMP280 not found!");
    while (1)
      ;
  }

  // Reset the sensor.
  writeRegister(BMP280_REG_RESET, 0xB6);
  delay(100);

  // Read calibration data.
  readCalibrationData();

  // Set configuration and control measurement registers.
  writeRegister(BMP280_REG_CONFIG, 0x00);     // No IIR filter.
  writeRegister(BMP280_REG_CTRL_MEAS, 0x27);  // Temperature and pressure oversampling rate = 1, normal mode.
}

void readSensorData(int32_t &temperature, uint32_t &pressure) {
  // Read raw temperature and pressure data.
  uint8_t data[6];
  readRegisters(BMP280_REG_PRESS_MSB, data, 6);

  int32_t adc_P = (int32_t)(((uint32_t)data[0] << 12) | ((uint32_t)data[1] << 4) | ((data[2] >> 4) & 0x0F));
  int32_t adc_T = (int32_t)(((uint32_t)data[3] << 12) | ((uint32_t)data[4] << 4) | ((data[5] >> 4) & 0x0F));

  // Compensate temperature and pressure.
  temperature = compensateTemperature(adc_T);
  pressure = compensatePressure(adc_P);
}

void writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(BMP280_ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

uint8_t readRegister(uint8_t reg) {
  Wire.beginTransmission(BMP280_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(BMP280_ADDRESS, 1);
  return Wire.read();
}

void readRegisters(uint8_t reg, uint8_t *buffer, uint8_t length) {
  Wire.beginTransmission(BMP280_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(BMP280_ADDRESS, length);
  for (uint8_t i = 0; i < length; i++) {
    buffer[i] = Wire.read();
  }
}

void readCalibrationData() {
  uint8_t calib[24];
  readRegisters(BMP280_REG_CALIB_00, calib, 24);

  dig_T1 = (uint16_t)(((uint16_t)calib[1] << 8) | calib[0]);
  dig_T2 = (int16_t)(((int16_t)calib[3] << 8) | calib[2]);
  dig_T3 = (int16_t)(((int16_t)calib[5] << 8) | calib[4]);
  dig_P1 = (uint16_t)(((uint16_t)calib[7] << 8) | calib[6]);
  dig_P2 = (int16_t)(((int16_t)calib[9] << 8) | calib[8]);
  dig_P3 = (int16_t)(((int16_t)calib[11] << 8) | calib[10]);
  dig_P4 = (int16_t)(((int16_t)calib[13] << 8) | calib[12]);
  dig_P5 = (int16_t)(((int16_t)calib[15] << 8) | calib[14]);
  dig_P6 = (int16_t)(((int16_t)calib[17] << 8) | calib[16]);
  dig_P7 = (int16_t)(((int16_t)calib[19] << 8) | calib[18]);
  dig_P8 = (int16_t)(((int16_t)calib[21] << 8) | calib[20]);
  dig_P9 = (int16_t)(((int16_t)calib[23] << 8) | calib[22]);
}

int32_t compensateTemperature(int32_t adc_T) {
  int32_t var1, var2, T;
  var1 = ((((adc_T >> 3) - ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
  var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) * ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;
  t_fine = var1 + var2;
  T = (t_fine * 5 + 128) >> 8;
  return T;
}

uint32_t compensatePressure(int32_t adc_P) {
  int64_t var1, var2, p;
  var1 = ((int64_t)t_fine) - 128000;
  var2 = var1 * var1 * (int64_t)dig_P6;
  var2 = var2 + ((var1 * (int64_t)dig_P5) << 17);
  var2 = var2 + (((int64_t)dig_P4) << 35);
  var1 = ((var1 * var1 * (int64_t)dig_P3) >> 8) + ((var1 * (int64_t)dig_P2) << 12);
  var1 = (((((int64_t)1) << 47) + var1) * ((int64_t)dig_P1)) >> 33;
  if (var1 == 0) {
    return 0;  // Avoid division by zero.
  }
  p = 1048576 - adc_P;
  p = (((p << 31) - var2) * 3125) / var1;
  var1 = (((int64_t)dig_P9) * (p >> 13) * (p >> 13)) >> 25;
  var2 = (((int64_t)dig_P8) * p) >> 19;
  p = ((p + var1 + var2) >> 8) + (((int64_t)dig_P7) << 4);
  return (uint32_t)p;
}
