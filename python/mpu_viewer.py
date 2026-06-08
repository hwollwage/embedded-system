import serial
import pyvista as pv

ser = serial.Serial('/dev/ttyUSB0', 115200)

plotter = pv.Plotter(window_size=(1200, 800))

plotter.set_background("white")
plotter.add_axes()

plate = pv.Plane(
    i_size=4,
    j_size=2,
    i_resolution=1,
    j_resolution=1
)

texture = pv.read_texture("data/ijazah-jokowi.jpg")
# texture = pv.read_texture("data/supersemar.jpeg")
# texture = pv.read_texture("data/ijazah-jokowi.png")

actor = plotter.add_mesh(plate,texture=texture)

text_actor = plotter.add_text("",position="upper_left",font_size=12)

plotter.show(interactive_update=True)

while True:
    try:
        line = ser.readline().decode().strip()
        parts = line.split(',')

        if len(parts) != 5:
            continue

        roll = float(parts[0])
        pitch = float(parts[1])

        x = float(parts[2])
        y = float(parts[3])
        z = float(parts[4])

        # Rotate
        actor.orientation = (
            pitch,  # X axis
            0,      # Y axis
            roll    # Z axis
        )

        # Update text
        text_actor.SetText(
            2,
            f"""
MPU6050 ATTITUDE

Roll  : {roll:7.2f}°
Pitch : {pitch:7.2f}°

Accelerometer

X : {x:7.2f}
Y : {y:7.2f}
Z : {z:7.2f}

Formula:
- roll : 
arctan(y/z)
- pitch : 
archtan(-x / sqrt(y^2+z^2))

"""
        )
        plotter.update()

    except KeyboardInterrupt:
        break

    except Exception as e:
        print(e)
ser.close()