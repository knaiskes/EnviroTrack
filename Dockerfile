FROM python:3.10.10-bullseye

WORKDIR /app

COPY requirements.txt .

RUN pip install --no-cache-dir -r requirements.txt

COPY /src/measurements .

CMD [ "python", "measurements.py"]
