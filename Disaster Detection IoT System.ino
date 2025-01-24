/*
  ESP32 publish telemetry data to VOne Cloud (Agriculture)
*/

#include "VOneMqttClient.h"
#include "DHT.h"

int MinMoistureValue = 4095;
int MaxMoistureValue = 1800;
int MinMoisture = 0;
int MaxMoisture = 100;
int Moisture = 0;

// Define device id
const char* DHT11Sensor = "9dbc11f6-3727-4cf8-a2ee-132ec25246a1";     // Replace with YOUR deviceID for the DHT11 sensor
const char* UltrasonicSensor = "4298d3b7-a643-4f45-9eb7-7fe39d0da707"; // Replace with YOUR deviceID for the ultrasonic sensor
const char* MoistureSensor = "effd02cb-e26e-4f55-91e8-e10979464fe5";  // Replace with YOUR deviceID for the moisture sensor

// Used Pins
const int dht11Pin = 42;         // Right side Maker Port
const int trigPin = 5;           // Trigger pin of Ultrasonic sensor
const int echoPin = 4;           // Echo pin of Ultrasonic sensor
const int moisturePin = 6;       // Middle Maker Port
const int buzzerPin = 8;         // Buzzer connected to GPIO 8
const int greenLedPin = 18;      // Green LED for Ultrasonic connected to GPIO 18
const int yellowLedPin = 16;     // Yellow LED for Ultrasonic connected to GPIO 16
const int redLedPin = 15;        // Red LED for Ultrasonic connected to GPIO 15

const int soilGreenLedPin = 38;       // Green LED for soil moisture connected to GPIO 17
const int soilYellowLedPin = 39;      // Yellow LED for soil moisture connected to GPIO 14
const int soilRedLedPin = 40;         // Red LED for soil moisture connected to GPIO 13

// Input sensor
#define DHTTYPE DHT11
DHT dht(dht11Pin, DHTTYPE);

// Create an instance of VOneMqttClient
VOneMqttClient voneClient;

// Last message time
unsigned long lastMsgTime = 0;

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  setup_wifi();
  voneClient.setup();

  // Sensor setup
  dht.begin();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);        // Ultrasonic Green LED
  pinMode(yellowLedPin, OUTPUT);       // Ultrasonic Yellow LED
  pinMode(redLedPin, OUTPUT);          // Ultrasonic Red LED
  pinMode(soilGreenLedPin, OUTPUT);    // Soil Green LED
  pinMode(soilYellowLedPin, OUTPUT);   // Soil Yellow LED
  pinMode(soilRedLedPin, OUTPUT);      // Soil Red LED
}

void loop() {
  if (!voneClient.connected()) {
    voneClient.reconnect();
    String errorMsg = "DHTSensor Fail";
    voneClient.publishDeviceStatusEvent(DHT11Sensor, true);
    voneClient.publishDeviceStatusEvent(UltrasonicSensor, true);
    voneClient.publishDeviceStatusEvent(MoistureSensor, true);
  }
  voneClient.loop();

  unsigned long cur = millis();
  if (cur - lastMsgTime > INTERVAL) {
    lastMsgTime = cur;

    // Publish telemetry data 1
    float h = dht.readHumidity();
    int t = dht.readTemperature();
    JSONVar payloadObject;
    payloadObject["Humidity"] = h;
    payloadObject["Temperature"] = t;
    voneClient.publishTelemetryData(DHT11Sensor, payloadObject);

    // Publish telemetry data 2 (Ultrasonic Sensor)
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    int distance = duration * 0.034 / 2; // Calculate the distance in cm

    Serial.print("Distance to publish: ");
    Serial.println(distance);
    voneClient.publishTelemetryData(UltrasonicSensor, "Ultrasonic Sensor", distance);

    // LED Indicators for Ultrasonic
    if (distance > 10) {
      digitalWrite(greenLedPin, HIGH);
      digitalWrite(yellowLedPin, LOW);
      digitalWrite(redLedPin, LOW);
    } else if (distance > 5 && distance <= 10) {
      digitalWrite(greenLedPin, LOW);
      digitalWrite(yellowLedPin, HIGH);
      digitalWrite(redLedPin, LOW);
    } else if (distance <= 5) {
      digitalWrite(greenLedPin, LOW);
      digitalWrite(yellowLedPin, LOW);
      digitalWrite(redLedPin, HIGH);
      
      // Blink Red LED for Ultrasonic
      for (int i = 0; i < 10; i++) {
        digitalWrite(redLedPin, HIGH);    // Turn on red LED
        delay(200);                       // Adjust delay for beep duration
        digitalWrite(redLedPin, LOW);     // Turn off red LED
        delay(200);                       // Adjust delay between beeps
      }
    } else {
      digitalWrite(buzzerPin, LOW);       // Turn off buzzer if distance >= 10 cm
      digitalWrite(redLedPin, LOW);       // Turn off red LED if distance >= 10 cm
    }

    // Publish telemetry data 3 (Soil Moisture)
    int sensorValue = analogRead(moisturePin);
    Moisture = map(sensorValue, MinMoistureValue, MaxMoistureValue, MinMoisture, MaxMoisture);
    voneClient.publishTelemetryData(MoistureSensor, "Soil moisture", Moisture);

    // LED Indicators for Soil Moisture
    if (Moisture >= 30 && Moisture <=80) {
      // Green LED: Ideal moisture level
      digitalWrite(soilGreenLedPin, HIGH);
      digitalWrite(soilYellowLedPin, LOW);
      digitalWrite(soilRedLedPin, LOW);
    } else if ((Moisture >= 10 && Moisture < 30) || (Moisture > 80 && Moisture <= 100)) {
      // Yellow LED: Warning for drought or excessive moisture (landslides)
      digitalWrite(soilGreenLedPin, LOW);
      digitalWrite(soilYellowLedPin, HIGH);
      digitalWrite(soilRedLedPin, LOW);
    } else if (Moisture < 10 || Moisture > 100) {
      // Red LED: Critical drought or landslide conditions
      digitalWrite(soilGreenLedPin, LOW);
      digitalWrite(soilYellowLedPin, LOW);
      digitalWrite(soilRedLedPin, HIGH);
      
      // Blink Red LED and turn on Buzzer for Critical Soil Moisture
      for (int i = 0; i < 10; i++) {
        digitalWrite(buzzerPin, HIGH);    // Turn on buzzer
        digitalWrite(soilRedLedPin, HIGH); // Turn on red LED
        delay(200);                       // Adjust delay for beep duration
        digitalWrite(buzzerPin, LOW);     // Turn off buzzer
        digitalWrite(soilRedLedPin, LOW); // Turn off red LED
        delay(200);                       // Adjust delay between beeps
      }
    }
  }
}
