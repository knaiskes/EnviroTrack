FROM python:3.10.10-alpine3.17

WORKDIR /app

COPY requirements.txt .

RUN pip install --no-cache-dir -r requirements.txt

COPY /src/measurements .

CMD [ "python", "measurements.py"]
