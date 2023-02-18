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

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  dht.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  client.setServer(mqtt_server, 1883);
  while (!client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
    delay(1000);
  }
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)) {
    // Do nothing for now...
    return;
  }
  String dht22Measurements = String(humidity) + "," + String(temperature);
  client.publish("sensors/dht22/measurements", dht22Measurements.c_str());
  delay(3000);
}
