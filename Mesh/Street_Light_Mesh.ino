#include <painlessMesh.h>
#include <ArduinoJson.h>

#define MESH_SSID "Abhishek"
#define MESH_PASSWORD "12345678"
#define MESH_PORT 5555

painlessMesh mesh;

// Create a JSON buffer for serialization
StaticJsonDocument<200> jsonBuffer;

void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Received from %u: %s\n", from, msg.c_str());

  // Parse the received JSON message
  DeserializationError error = deserializeJson(jsonBuffer, msg);

  // Check for parsing errors
  if (error) {
    Serial.print("JSON parsing failed: ");
    Serial.println(error.c_str());
    return;
  }

  // Extract data from JSON
  float receivedCurrent = jsonBuffer["current"];
  float receivedVoltage = jsonBuffer["voltage"];
  int receivedLDR = jsonBuffer["ldr"];

  // Process the received data (you can replace this with your own logic)
  Serial.printf("Received Data: Current=%.2fA, Voltage=%.2fV, LDR=%d\n", receivedCurrent, receivedVoltage, receivedLDR);
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("New Connection, nodeId = %u\n", nodeId);
}

void readSensorData() {
  // Read sensor data from analog pin A0 on each node
  float currentSensorData = analogRead(A0) * 5.0 / 1024.0;
  int ldrSensorData = analogRead(A0);  // Using the same pin for LDR

  // Create a JSON object for serialization
  jsonBuffer.clear();
  jsonBuffer["current"] = currentSensorData;
  jsonBuffer["voltage"] = 0.0;  // Placeholder for voltage sensor data
  jsonBuffer["ldr"] = ldrSensorData;

  // Serialize the JSON object to a string
  String jsonString;
  serializeJson(jsonBuffer, jsonString);

  // Send the JSON string as a broadcast message
  mesh.sendBroadcast(jsonString);
}

void setup() {
  Serial.begin(115200);
  
  mesh.setDebugMsgTypes(ERROR | STARTUP | CONNECTION | DEBUG);  // Enable debug messages

  mesh.init(MESH_SSID, MESH_PASSWORD, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);

  Serial.println("Mesh started");
}

void loop() {
  mesh.update();

  // Read sensor data and send it to the mesh every 5 seconds (adjust as needed)
  static unsigned long lastSendTime = 0;
  if (millis() - lastSendTime > 5000) {
    readSensorData();
    lastSendTime = millis();
  }
}
