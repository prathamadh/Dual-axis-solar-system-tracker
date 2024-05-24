#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "Good boy";
const char* password = "PAS077BCE091";
const char* server = "192.168.0.101";
const int port = 4000;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  if (Serial.available()) {
    String sensorData = Serial.readStringUntil('\n'); // Read sensor data from Arduino Nano
    sensorData.trim(); // Remove leading and trailing whitespace
    sensorData.replace("\r", ""); // Remove carriage return characters
    sensorData.replace("\n", ""); // Remove newline characters

    Serial.println("Received Data: " + sensorData); // Print received data

    // Convert the sensor data to JSON format
    String jsonData = "{\"sensorData\": \"" + sensorData + "\"}";

    sendDataToServer(jsonData);
  }

  delay(1000); // Adjust delay as needed
}

void sendDataToServer(String data) {
  WiFiClient client;

  Serial.println("Sending Data to Server: " + data); // Print data before sending to server

  if (client.connect(server, port)) {
    client.println("POST / HTTP/1.1");
    client.println("Host: 192.168.16.28:4000");
    client.println("Content-Type: application/json"); // Specify content type as JSON
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.println(data);

    while (client.available()) {
      Serial.write(client.read());
    }
    client.stop();
  }
}

