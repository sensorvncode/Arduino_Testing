#if defined(ESP8266)
#include <ESP8266WiFi.h>
#define THINGSBOARD_ENABLE_PROGMEM 0
#elif defined(ESP32) || defined(RASPBERRYPI_PICO) || defined(RASPBERRYPI_PICO_W)
#include <WiFi.h>
#endif

#include <Arduino_MQTT_Client.h>
#include <ThingsBoard.h>

/* Variables */
constexpr char WIFI_SSID[] = "sensorvn.com";
constexpr char WIFI_PASSWORD[] = "@sensorvn.com";
constexpr char TOKEN[] = "A8R5OfeE6GQdIfHiGaKV";
constexpr char THINGSBOARD_SERVER[] = "demo.thingsboard.io";
constexpr uint16_t THINGSBOARD_PORT = 1883U;
constexpr uint32_t MAX_MESSAGE_SIZE = 1024U;
constexpr uint32_t SERIAL_DEBUG_BAUD = 115200U;
constexpr size_t MAX_ATTRIBUTES = 2U;
WiFiClient wifiClient;
Arduino_MQTT_Client mqttClient(wifiClient);
ThingsBoardSized<Default_Fields_Amount, Default_Subscriptions_Amount, MAX_ATTRIBUTES> tb(mqttClient, MAX_MESSAGE_SIZE);
// For telemetry
constexpr int16_t telemetrySendInterval = 2000U;
uint32_t previousDataSend;

/* My Functions */
void InitWiFi() {
  Serial.println("Connecting to AP ...");
  // Attempting to establish a connection to the given WiFi network
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    // Delay 500ms until a connection has been succesfully established
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
}
const bool reconnect() {
  // Check to ensure we aren't connected yet
  const wl_status_t status = WiFi.status();
  if (status == WL_CONNECTED) {
    return true;
  }
  // If we aren't establish a new connection to the given WiFi network
  InitWiFi();
  return true;
}

/* Main Function */
void setup() {
  // Initialize serial connection for debugging
  Serial.begin(SERIAL_DEBUG_BAUD);
  delay(1000);
  InitWiFi();
}

void loop() {
  delay(10);
  if (!reconnect()) {
    return;
  }
  if (!tb.connected()) {
    // Connect to the ThingsBoard
    Serial.print("Connecting to: ");
    Serial.print(THINGSBOARD_SERVER);
    Serial.print(" with token ");
    Serial.println(TOKEN);
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN, THINGSBOARD_PORT)) {
      Serial.println("Failed to connect");
      return;
    }
    Serial.println("Subscribe done");
  }
  // Sending telemetry every telemetrySendInterval time
  if (millis() - previousDataSend > telemetrySendInterval) {
    previousDataSend = millis();
    tb.sendTelemetryData("temperature", random(10, 20));
    tb.sendAttributeData("rssi", WiFi.RSSI());
    tb.sendAttributeData("channel", WiFi.channel());
    tb.sendAttributeData("bssid", WiFi.BSSIDstr().c_str());
    tb.sendAttributeData("localIp", WiFi.localIP().toString().c_str());
    tb.sendAttributeData("ssid", WiFi.SSID().c_str());
  } 
  tb.loop(); 
}
