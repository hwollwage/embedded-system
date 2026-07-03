import cv2
import serial
import time

esp = serial.Serial("/dev/ttyUSB0", 115200)
time.sleep(2)


mouse_x = 0
mouse_y = 0
message = ""
message_color = (255,255,255)
lastangle = -1

def mouse(event, x, y, flags, param):
    global mouse_x, mouse_y, message, message_color

    mouse_x = x
    mouse_y = y

    if event == cv2.EVENT_LBUTTONDOWN:
        message = "Left button clicked"
        message_color = (0, 0, 255)
        esp.write(b"LEFT\n") 

    elif event == cv2.EVENT_RBUTTONDOWN:
        message = "Right button clicked"
        message_color = (255, 0, 0)
        esp.write(b"RIGHT\n")

cap = cv2.VideoCapture(0)

cv2.namedWindow("camera")
cv2.setMouseCallback("camera", mouse)

while True:
    ret, frame = cap.read()
    if not ret:
        print("camera not found")
        break
    
    key = cv2.waitKey(1) & 0xFF
    if key == ord('q'):
        break

    height, width, _ = frame.shape
    servo_angle = int(mouse_x / width * 180)
    if servo_angle != lastangle:
        print(f"Sending: {servo_angle}")
        esp.write(f"ANGLE: {servo_angle}\n".encode())
        lastangle = servo_angle
        time.sleep(0.01)

    center_x = width // 2
    center_y = height // 2

    # center circle
    cv2.circle(
        frame,
        (center_x, center_y),
        3,
        (255,255,255),
        -1
    )
    # circle follow EVENT_MOUSEMOVE
    cv2.circle(
        frame, 
        (mouse_x, mouse_y), 
        10, 
        (0, 255, 0), 
        -1
    )
    # mouse coordinate
    cv2.putText(
        frame,
        f"mouse: ({mouse_x}, {mouse_y})",
        (10,30),
        cv2.FONT_HERSHEY_SIMPLEX,
        1,
        (255,255,255),
        2
    )
    # right click left click
    cv2.putText(
        frame,
        message,
        (10,70),
        cv2.FONT_HERSHEY_SIMPLEX,
        1,
        message_color,
        2
    )
    # servo angle
    cv2.putText(
        frame,
        f"servo: {servo_angle}°",
        (10, 100),
        cv2.FONT_HERSHEY_SIMPLEX,
        1,
        (0,255,255),
        2
    )

    cv2.line(
        frame,
        (mouse_x, 0),
        (mouse_x, height),
        (0, 255,255),
        2
    )
    
    cv2.imshow("camera", frame)

cap.release()
cv2.destroyAllWindows()
esp.close()

    # cv2.putText()
    # image_frame, text, position, font, fontscale, color, thickness
    # cv2.putText(frame, "hello", (10,50), cv2.FONT_HERSHEY_SIMPLEX, 1, (255,255,255), 2)

    # SHAPE CV2.CIRCLE
    # param = img_frame, center, radius, rgb_color, filled
    # cv2.circle(frame, (0, 0), 8, (0,0,255), -1)
    # cv2.circle(frame, (width-1, 0), 8, (0,255,0), -1)
    # cv2.circle(frame, (0, height-1), 8, (255,0,0), -1)
    # cv2.circle(frame, (width-1, height-1), 8, (255,255,0), -1)
    # cv2.circle(frame, (width//2, height//2), 8, (255,255,255), -1)