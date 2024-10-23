#include <SoftwareSerial.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h> // Include ArduinoJson library

// Define your network credentials
const char* ssid = "Pixel";
const char* password = "123456789ak";
const char* serverUrl = "http://your_domain:5000/water";
SoftwareSerial nodemcu(D1,D2);
void setup() {
  Serial.begin(9600);
  nodemcu.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
 
  if (nodemcu.available()) {    
    String jsonData = nodemcu.readStringUntil('\n');
    Serial.println("Received JSON: " + jsonData);
    sendToServer(jsonData);
  }
  else {
    Serial.println("Not reached");
  }

  delay(1000);
}
void sendToServer(String data) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        WiFiClient client; // Create a WiFiClient object
        http.begin(client, serverUrl); // Use the WiFiClient object here
        
        http.addHeader("Content-Type", "application/json"); // Set content-type to JSON

        int httpResponseCode = http.POST(data); // Send POST request

        if (httpResponseCode > 0) {
            String response = http.getString(); // Get the response
            Serial.println("Response Code: " + String(httpResponseCode));
            Serial.println("Response: " + response);
        } else {
            Serial.println("Error in HTTP request: " + String(httpResponseCode));
        }

        http.end(); // End the HTTP request
    } else {
        Serial.println("Error: Not connected to WiFi");
    }
}
