#include "painlessMesh.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#define MESH_PREFIX "Abhishek"
#define MESH_PASSWORD "12345678"
#define MESH_PORT 5555

painlessMesh mesh;
WiFiClient wifiClient;

const char *ssid = "YourWiFiSSID";       // Replace with your actual WiFi SSID
const char *password = "YourWiFiPassword"; // Replace with your actual WiFi password
const char *endpoint = "YourEndpointURL";  // Replace with your actual endpoint URL

const int currentPin = D0;
const int voltagePin = D1;
const float voltageReference = 3.3;

void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Master Node: Received from %u msg=%s\n", from, msg.c_str());
  sendToServer(msg);
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("Master Node: New Connection, nodeId = %u\n", nodeId);
}

void sendToServer(const String &data) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(wifiClient, endpoint);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(data);
    if (httpResponseCode > 0) {
      Serial.printf("HTTP Response Code: %d\n", httpResponseCode);
    } else {
      Serial.printf("HTTP Request failed, error: %s\n", http.errorToString(httpResponseCode).c_str());
    }

    http.end();
  } else {
    Serial.println("WiFi not connected!");
  }
}

void sendDataToMesh() {
  int currentSensorValue = analogRead(currentPin);
  int voltageSensorValue = analogRead(voltagePin);
  float voltage = (voltageSensorValue / 1023.0) * voltageReference;

  DynamicJsonDocument jsonDoc(256);
  jsonDoc["sensor_type"] = "current_voltage";
  jsonDoc["current_value"] = currentSensorValue;
  jsonDoc["voltage_value"] = voltage;

  String jsonData;
  serializeJson(jsonDoc, jsonData);

  mesh.sendBroadcast(jsonData);
}

void connectToWiFi() {
  WiFi.begin(ssid, password);
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 30000) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to WiFi");
  } else {
    Serial.println("Failed to connect to WiFi");
  }
}

void setup() {
  Serial.begin(115200);

  // Initialize the mesh network first
  mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);

  // Now attempt to connect to WiFi
  connectToWiFi();

  Serial.println("Master Node ready!");
}

void loop() {
  mesh.update();
  sendDataToMesh();
  delay(1000);
}
