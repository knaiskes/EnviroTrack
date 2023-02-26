# EnviroTrack

A project that uses an Esp8266 board and a DHT22 sensor to collect real-time
temperature and humidity data from a room. The system is designed to send this
data to an MQTT broker, which allows the user to remotely access and monitor
the measurements in real-time. Lastly, Grafana is utilized as a data
visualization tool for displaying and analyzing the collected measurements in a
user-friendly format.

## Quick start

### Clone the project

```
$ git clone git@github.com:knaiskes/EnviroTrack.gitgit@github.com:knaiskes/EnviroTrack.git
```

### Create virtual enviroment and install dependecies

```
$ cd EnviroTrack/
$ python -m venv venv
$ source venv/bin/activate
$ pip install requirements.txt
```

## Upload code to ESP8266

```
$ cd src/esp8266
$ platformio run --target upload
```

### Run project with Docker compose

```
$ pwd # /EnviroTrack
$ docker-compose up
```
