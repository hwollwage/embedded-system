from fastapi import FastAPI, HTTPException, status
from pydantic import BaseModel
from db import Base, engine
from sqlalchemy import Column, String

app = FastAPI()

class DeviceDB(Base):
    __tablename__ = "devices"
    device_id = Column(String, primary_key=True)
    name = Column(String(100))

class Device(BaseModel):
    device_id: str
    name: str

Base.metadata.create_all(bind=engine)