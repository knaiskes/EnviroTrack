import paho.mqtt.client as mqtt
from datetime import datetime
import psycopg2

MQTT_BROKER_ADDRESS = 'mqtt'
MQTT_BROKER_PORT = 1883
MQTT_USERNAME = 'test'
MQTT_PASSWORD = 'test'
MQTT_TOPIC = 'sensor/dht22/measurements'

POSTGRES_HOST = 'db'
POSTGRES_PORT = 5432
POSTGRES_DBNAME = 'measurements'
POSTGRES_USERNAME = 'postgres'
POSTGRES_PASSWORD = 'postgres'

conn = psycopg2.connect(
    host=POSTGRES_HOST,
    port=POSTGRES_PORT,
    dbname=POSTGRES_DBNAME,
    user=POSTGRES_USERNAME,
    password=POSTGRES_PASSWORD
)

def on_message(client, userdata, message):
    payload = message.payload.decode('utf-8')
    timestamp = datetime.now()
    temperature, humidity = payload.split(',')
    try:
        float(temperature)
        float(humidity)
    except ValueError:
        temperature = 0
        humidity = 0
    cursor = conn.cursor()
    cursor.execute(
        'INSERT INTO dht22 (timestamp, temperature, humidity) VALUES (%s, %s)',
        (timestamp, payload)
    )
    conn.commit()

client = mqtt.Client()
client.username_pw_set(MQTT_USERNAME, MQTT_PASSWORD)
client.on_message = on_message
client.connect(MQTT_BROKER_ADDRESS, MQTT_BROKER_PORT)
client.subscribe(MQTT_TOPIC)

client.loop_forever()
