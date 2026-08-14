from fastapi import FastAPI, HTTPException, status
from pydantic import BaseModel

app = FastAPI()

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
    devices.append(device.model_dump())
    return {
        "status": "created",
        "device": device
    }

@app.get("/devices")
def get_device():
    return devices

@app.get("/devices/{device_id}")
def get_device(device_id: str):
    for device in devices:
        if device["device_id"] == device_id:
            return device

    return {
        "error" : "device not found"
    }