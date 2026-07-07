import serial

ser = serial.Serial('/dev/ttyUSB0', 115200)

while True:
    try:
        line = ser.readline().decode().strip()
        print(line)
    except Exception as e:
        print(e)