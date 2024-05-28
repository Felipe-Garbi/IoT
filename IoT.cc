#include <WiFi.h>
#include <PubSubClient.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <ESP32Servo.h>
#include <time.h>  

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com"; 
const char* mqtt_topic = "esp32/sunset";
int BrokerPort = 1883;
const String openWeatherMapApiKey = "c8cb6b05f51dd63e37d0d17f0ab6768a";
const String city = "São Paulo";
const String countryCode = "BR";
unsigned long timerDelay = 10000; 
unsigned long lastTime = 0;

Servo myServo;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);

  myServo.attach(13);

  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("Waiting for NTP time sync...");
  while (time(nullptr) < 8 * 3600 * 2) { 
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nTime synchronized");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      getSolarData();
    } else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void getSolarData() {
  HTTPClient http;

 
  String url = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey;

  Serial.print("Connecting to OpenWeatherMap... ");
  if (http.begin(url)) {
    Serial.println("Connected!");

    int httpCode = http.GET();

    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        JSONVar data = JSON.parse(payload);

        unsigned long sunsetTime = (unsigned long)data["sys"]["sunset"];

        unsigned long currentTime = time(nullptr);

        if (currentTime > sunsetTime) {
          Serial.println("Sunset has occurred. It's time to clean. Activating servo.");
          activateServo();
          publishData("clean");
        } else {
          Serial.println("Sunset has not occurred yet.");
          publishData("no_clean");
        }
      } else {
        Serial.print("HTTP Error: ");
        Serial.println(httpCode);
      }
    } else {
      Serial.println("Failed to connect to server");
    }

    http.end();
  } else {
    Serial.println("Failed to connect to OpenWeatherMap");
  }
}

void activateServo() {
  myServo.write(90); 
  delay(2000);       
  myServo.write(0);  
}

void publishData(String status) {
  String payload = "{\"sunset_status\": \"" + status + "\"}";
  client.publish(mqtt_topic, payload.c_str());
}