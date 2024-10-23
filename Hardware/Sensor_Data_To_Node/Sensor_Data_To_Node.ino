#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h> // Include for SoftwareSerial
#define ONE_WIRE_BUS 8

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Temperature variable (only Celsius)
float Celsius = 0;

#include <EEPROM.h>
#include "GravityTDS.h"

#define TdsSensorPin A0 // Pin for TDS sensor
#define TurbiditySensorPin A1 // Pin for Turbidity sensor
#define PhSensorPin A2 // Pin for pH sensor

GravityTDS gravityTds;

// Variables for TDS, turbidity (NTU), and pH
float temperature = 25, tdsValue = 0;
float turbidityValue = 0, turbidityNTU = 0;
int buf[10], temp = 0;
unsigned long avgValue;
float pHValue;
const float scaleFactor = 3000.0; // Calibration factor for NTU conversion

// Additional metadata
const char* area = "Riverbank";
const char* district = "Central District";
const char* state = "California";
const char* country = "USA";

float calculatePH() {
  for (int i = 0; i < 10; i++) {
    buf[i] = analogRead(PhSensorPin);
    delay(10);
  }

  // Sort the buffer for noise reduction
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (buf[i] > buf[j]) {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }

  avgValue = 0;
  // Average the middle 6 values to avoid extreme readings
  for (int i = 2; i < 8; i++) {
    avgValue += buf[i];
  }

  float pHVol = (float)avgValue * 5.0 / 1024 / 6;
  float phValue = -5.70 * pHVol + 22.8;
  phValue = 14.2 - phValue;

  return phValue;
}

void setup() {
  sensors.begin();
  Serial.begin(9600);

  // Initialize TDS sensor
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);
  gravityTds.setAdcRange(1024);
  gravityTds.begin();
}

void loop() {
  // Get temperature in Celsius
  sensors.requestTemperatures();
  Celsius = sensors.getTempCByIndex(0);

  // Get TDS value
  gravityTds.setTemperature(temperature);
  gravityTds.update();
  tdsValue = gravityTds.getTdsValue();

  // Read turbidity value (analog input)
  turbidityValue = analogRead(TurbiditySensorPin);
  turbidityNTU = (turbidityValue * 5.0 / 1024) * scaleFactor; // Convert to NTU

  // Read pH value (analog input)
  pHValue = calculatePH();

  // Prepare JSON data for all sensors including metadata
  String json = "{";
  json += "\"temperature\":" + String(Celsius, 2) + ","; // Only Celsius included
  json += "\"tds\":" + String(tdsValue, 0) + ",";
  json += "\"turbidity\":" + String(turbidityNTU, 2) + ",";
  json += "\"ph\":" + String(pHValue, 2) + ",";
  json += "\"area\":\"" + String(area) + "\",";
  json += "\"district\":\"" + String(district) + "\",";
  json += "\"state\":\"" + String(state) + "\",";
  json += "\"country\":\"" + String(country) + "\"";
  json += "}";

  // Send JSON data to Serial
  Serial.println(json);

  delay(1000); // Wait for 1 second before the next reading
}
  
