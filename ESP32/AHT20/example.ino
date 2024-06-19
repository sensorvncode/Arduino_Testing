#include <Wire.h>

#define AHT20_ADDRESS 0x38
#define AHT20_INIT_CMD 0xBE
#define AHT20_MEAS_CMD 0xAC
#define AHT20_STATUS_CMD 0x71

void setup() {
  Serial.begin(115200);
  Wire.begin();
  // sensorvn.com
  delay(500);
  Serial.println("Code written by sensorvn.com");
  delay(5000);

  // Initialize the AHT20 sensor
  Wire.beginTransmission(AHT20_ADDRESS);
  Wire.write(AHT20_INIT_CMD);
  Wire.write(0x08);  // Calibration enable
  Wire.write(0x00);
  if (Wire.endTransmission() != 0) {
    Serial.println("Failed to initialize AHT20 sensor!");
    while (1) delay(10);
  }
  delay(100);  // Wait for initialization
  Serial.println("AHT20 initialized");
}

void loop() {
  // Trigger a measurement
  Wire.beginTransmission(AHT20_ADDRESS);
  Wire.write(AHT20_MEAS_CMD);
  Wire.write(0x33);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(80);  // Measurement time

  // Read the result
  Wire.requestFrom(AHT20_ADDRESS, 7);
  if (Wire.available() == 7) {
    uint8_t data[7];
    for (int i = 0; i < 7; i++) {
      data[i] = Wire.read();
    }

    // Process the data
    uint32_t rawHumidity = ((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | ((uint32_t)data[3] >> 4);
    uint32_t rawTemperature = (((uint32_t)data[3] & 0x0F) << 16) | ((uint32_t)data[4] << 8) | (uint32_t)data[5];

    float humidity = ((rawHumidity * 100.0) / 1048576.0);
    float temperature = ((rawTemperature * 200.0) / 1048576.0) - 50.0;

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" degrees C");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" % rH");
  } else {
    Serial.println("Failed to read data from AHT20 sensor!");
  }

  delay(1000);
}
