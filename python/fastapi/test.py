from fastapi import FastAPI, status, HTTPException
from pydantic import BaseModel

app = FastAPI()

class SensorData(BaseModel):
    device_id: str
    temp: float
    humid: float

class SensorResponse(BaseModel):
    device_id: str
    temp: float
    humid: float

devices = [
    {
        "device_id": "esp32-01",
        "name": "sensor kamar"
    },
    {
        "device_id": "esp32-02",
        "name": "sensor garasi"
    }
]

class Device(BaseModel):
    device_id: str
    name: str

@app.post("/devices")
def create_device(device: Device):
    devices.append(device)

    return {
        "status": "created",
        "device": device
    }

@app.get("/devices")
def get_devices():
    return devices

@app.get("/devices/{device_id}")
def getdevice(device_id: str):

    for device in devices:
        if device.device_id == device_id:
            return device

    raise HTTPException(
        status_code=404,
        detail="device not found"
    )



@app.get("/sensor-secret", response_model=SensorResponse)
def get_sensor():
    return {
        "device_id" : "esp32-01",
        "temp": 21.2,
        "humid": 11.5,
        "password": "secret123"
    }


@app.get("/")
def home():
    return {"msg" : "hello esp32"}

@app.get("/hello")
def hello():
    return {"msg" : "ghello"}

# @app.post("/sensor")
# def sensor(data: SensorData ):
#     return {
#         "status" : "success",
#         "device id" : data.device_id,
#         "temperature": data.temp,
#         "humidity": data.humid
#     }

@app.get("/sensor/{device_id}")
def get_sensor(device_id: str):
    if device_id != "esp32-01":
        raise HTTPException(
            status_code=404,
            detail="device not found"
        )
    return {
        "status": "success getting device id",
        "device_id": device_id
    }

# query param (/sensor?device_id=esp123)
@app.get("/sensor")
def get_sensor(device_id: str):
    return {
        "status": "success getting device id param",
        "device_id": device_id
    }

# status
@app.post("/sensor", status_code=status.HTTP_201_CREATED)
def sensor(data: SensorData):
    return {
        "status" : "201 success created",
        "device_id" : data.device_id,
        "temperature" : data.temp,
        "humidity" : data.humid
    }

