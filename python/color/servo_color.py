import cv2
import numpy
import serial

serial.Serial("/dev/ttyUSB0", 115200)

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        print("camera not found")
        break

    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
