from vpython import *
import serial

ser = serial.Serial('/dev/ttyUSB0', 115200)

scene.title = "MPU6050 Attitude Indicator"
scene.width = 1200
scene.height = 800

body = box(
    length=4,
    height=0.2,
    width=2
)

while True:
    rate(60)

    try:
        line = ser.readline().decode().strip()

        parts = line.split(',')

        if len(parts) != 2:
            continue

        roll = radians(float(parts[0]))
        pitch = radians(float(parts[1]))

        body.axis = vector(
            cos(pitch),
            sin(roll),
            sin(pitch)
        )

    except Exception as e:
        print(e)