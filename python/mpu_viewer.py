import serial
import pyvista as pv

ser = serial.Serial('/dev/ttyUSB0', 115200)

plotter = pv.Plotter()

plane = pv.Cube(
    x_length=4,
    y_length=0.2,
    z_length=2
)

actor = plotter.add_mesh(
    plane,
    show_edges=True
)

plotter.show(interactive_update=True)

while True:
    try:
        line = ser.readline().decode().strip()

        parts = line.split(',')

        if len(parts) != 2:
            continue

        roll = float(parts[0])
        pitch = float(parts[1])

        actor.orientation = (pitch, 0, roll)

        plotter.update()

    except Exception as e:
        print(e)