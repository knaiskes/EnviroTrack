# EnviroTrack

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
