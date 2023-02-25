#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTTYPE DHT22

const uint8_t DHTPIN = D3;
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "";
const char* password = "";
const char* mqtt_server = "";
const char* mqtt_user = "";
const char* mqtt_password = "";
const int mqtt_port = 1883;
const char* topic = "sensors/dht22/measurements";
const unsigned long millisInMinutes = 300000; // 5 minutes

WiFiClient espClient;
PubSubClient client(espClient);

void reconnectWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
}

void reconnectMQTT() {
  while (!client.connected()) {
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
    } else {
      delay(5000);
    }
  }
}

void setup() {
  dht.begin();
  reconnectWiFi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  static unsigned long lastMsg = 0;
  if (millis() - lastMsg > millisInMinutes) {
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    if (isnan(humidity) || isnan(temperature)) {
      // Do nothing for now...
      return;
    }

    lastMsg = millis();
    String dht22Measurements = String(temperature) + "," + String(humidity);
    client.publish(topic, dht22Measurements.c_str());
  }
}
