import cv2
import numpy as np
import RPi.GPIO as GPIO
import serial
import time
ball_x = 1
ball_y = 2
goal_x = 10
goal_y = 20 
GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.IN)
GPIO.setup(23, GPIO.IN)
GPIO.setup(24, GPIO.IN)
GPIO.setup(25, GPIO.IN)
GPIO.add_event_detect(18, GPIO.RISING)
GPIO.add_event_detect(23, GPIO.RISING)
GPIO.add_event_detect(24, GPIO.RISING)
GPIO.add_event_detect(25, GPIO.RISING)
ser = serial.Serial(
        port='/dev/ttyS0', 
        baudrate = 115200,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
)

def data_1(channel):
	global ball_x
	ser.write(bytes([ball_x]))
def data_2(channel):
	global ball_y
	ser.write(bytes([ball_y]))
    
def data_3(channel):
	global goal_x
	ser.write(bytes([goal_x]))
def data_4(channel):
	global goal_y
	ser.write(bytes([goal_y]))
GPIO.add_event_callback(18, data_1)
GPIO.add_event_callback(23, data_2)
GPIO.add_event_callback(24, data_3)
GPIO.add_event_callback(25, data_4)

saveFile = open("camera_setings.txt","r+")



def nothing(x):
    pass

last_time = time.time()
cap = cv2.VideoCapture(0)
cap.set(3,352)
cap.set(4,288) 

cv2.namedWindow("Ball_SET")
cv2.moveWindow("Ball_SET",0,300)

cv2.createTrackbar("U - H_ball", "Ball_SET", 179, 179, nothing)
cv2.createTrackbar("L - H_ball", "Ball_SET", 0, 179, nothing)
cv2.createTrackbar("U - S_ball", "Ball_SET", 255, 255, nothing)
cv2.createTrackbar("L - S_ball", "Ball_SET", 0, 255, nothing)
cv2.createTrackbar("U - V_ball", "Ball_SET", 255, 255, nothing)
cv2.createTrackbar("L - V_ball", "Ball_SET", 0, 255, nothing)
cv2.createTrackbar("Min_ball_size", "Ball_SET", 0, 10000, nothing)


cv2.namedWindow("Goal_SET")
cv2.moveWindow("Goal_SET",350,300)
cv2.createTrackbar("U - H_goal", "Goal_SET", 179, 179, nothing)
cv2.createTrackbar("L - H_goal", "Goal_SET", 0, 179, nothing)
cv2.createTrackbar("U - S_goal", "Goal_SET", 255, 255, nothing)
cv2.createTrackbar("L - S_goal", "Goal_SET", 0, 255, nothing)
cv2.createTrackbar("U - V_goal", "Goal_SET", 255, 255, nothing)
cv2.createTrackbar("L - V_goal", "Goal_SET", 0, 255, nothing)
cv2.createTrackbar("Min_goal_size", "Goal_SET", 0, 10000, nothing)

cv2.namedWindow("DISABLE_SETUP")
cv2.moveWindow("DISABLE_SETUP",700,300)
cv2.createTrackbar("DONE_OF_SETUP", "DISABLE_SETUP", 0, 1, nothing)

int_save = []
for val in saveFile.read().split():
    int_save.append(int(val))
    saveFile = open("camera_setings.txt","r+")
l_h_ball = int_save[0]
l_s_ball = int_save[1]
l_v_ball = int_save[2]
u_h_ball = int_save[3]
u_s_ball = int_save[4]
u_v_ball = int_save[5]
ball_min_size = int_save[6]

l_h_goal = int_save[7]
l_s_goal = int_save[8]
l_v_goal = int_save[9]
u_h_goal = int_save[10]
u_s_goal = int_save[11]
u_v_goal = int_save[12]
goal_min_size = int_save[13]

cv2.namedWindow("Goal_SET")


cv2.setTrackbarPos("L - H_ball", "Ball_SET",l_h_ball)
cv2.setTrackbarPos("L - S_ball", "Ball_SET",l_s_ball)
cv2.setTrackbarPos("L - V_ball", "Ball_SET",l_v_ball)
cv2.setTrackbarPos("U - H_ball", "Ball_SET",u_h_ball)
cv2.setTrackbarPos("U - S_ball", "Ball_SET",u_s_ball)
cv2.setTrackbarPos("U - V_ball", "Ball_SET",u_v_ball)
cv2.setTrackbarPos("Min_ball_size", "Ball_SET",ball_min_size)
                                                                                                                                        
cv2.setTrackbarPos("L - H_goal", "Goal_SET",l_h_goal)
cv2.setTrackbarPos("L - S_goal", "Goal_SET",l_s_goal)
cv2.setTrackbarPos("L - V_goal", "Goal_SET",l_v_goal)
cv2.setTrackbarPos("U - H_goal", "Goal_SET",u_h_goal)
cv2.setTrackbarPos("U - S_goal", "Goal_SET",u_s_goal)
cv2.setTrackbarPos("U - V_goal", "Goal_SET",u_v_goal)
cv2.setTrackbarPos("Min_goal_size", "Goal_SET",goal_min_size)

done = 0
while done == 0:
    
    ret, frame = cap.read()
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    done = cv2.getTrackbarPos("DONE_OF_SETUP", "DISABLE_SETUP")

    l_h_ball = cv2.getTrackbarPos("L - H_ball", "Ball_SET")
    l_s_ball = cv2.getTrackbarPos("L - S_ball", "Ball_SET")
    l_v_ball = cv2.getTrackbarPos("L - V_ball", "Ball_SET")
    u_h_ball = cv2.getTrackbarPos("U - H_ball", "Ball_SET")
    u_s_ball = cv2.getTrackbarPos("U - S_ball", "Ball_SET")
    u_v_ball = cv2.getTrackbarPos("U - V_ball", "Ball_SET")
    ball_min_size = cv2.getTrackbarPos("Min_ball_size", "Ball_SET")

    l_h_goal = cv2.getTrackbarPos("L - H_goal", "Goal_SET")
    l_s_goal = cv2.getTrackbarPos("L - S_goal", "Goal_SET")
    l_v_goal = cv2.getTrackbarPos("L - V_goal", "Goal_SET")
    u_h_goal = cv2.getTrackbarPos("U - H_goal", "Goal_SET")
    u_s_goal = cv2.getTrackbarPos("U - S_goal", "Goal_SET")
    u_v_goal = cv2.getTrackbarPos("U - V_goal", "Goal_SET")
    goal_min_size = cv2.getTrackbarPos("Min_goal_size", "Goal_SET")

    lower_color_ball = np.array([l_h_ball, l_s_ball, l_v_ball])
    upper_color_ball = np.array([u_h_ball, u_s_ball, u_v_ball])
 
    lower_color_goal = np.array([l_h_goal, l_s_goal, l_v_goal])
    upper_color_goal = np.array([u_h_goal, u_s_goal, u_v_goal])

    mask = cv2.inRange(hsv, lower_color_ball, upper_color_ball)
    contours_ball, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    mask_ball = mask

    mask = cv2.inRange(hsv, lower_color_goal, upper_color_goal)
    contours_goal, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    mask_goal = mask

    contours_ball = sorted(contours_ball, key=lambda x: cv2.contourArea(x), reverse=True)
    contours_goal = sorted(contours_goal, key=lambda x: cv2.contourArea(x), reverse=True)

    for cnt in contours_ball:
        (x, y, w, h) = cv2.boundingRect(cnt)
        if w*h > ball_min_size:
            cv2.circle(frame, (x+(w//2), y+(w//2)), (w//2),(0,0,255),5)
            ball_x = x
            ball_y = y
        else:    
            ball_x = -1
            ball_y = -1
        break

    for cnt in contours_goal:
        (x, y, w, h) = cv2.boundingRect(cnt)
        if w*h > goal_min_size:
            cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 10)
            goal_x = x
            goal_y = y
        else:
            goal_x = -1
            goal_y = -1
        break

    #result = cv2.bitwise_and(frame, frame, mask=mask)
    mask_ball = cv2.bitwise_and(frame, frame, mask=mask_ball)
    mask_goal = cv2.bitwise_and(frame, frame, mask=mask_goal)
    cv2.imshow("mask_ball", mask_ball)
    cv2.moveWindow("mask_ball", 0, 0)
    cv2.imshow("mask_goal", mask_goal)
    cv2.moveWindow("mask_goal", 350, 0)
    cv2.imshow("result", frame)
    cv2.moveWindow("result", 700, 0)

    key = cv2.waitKey(1)
    if key == 27:
        break

last_time = time.time()
last_loop_time = 0
cv2.destroyWindow("mask_ball")
cv2.destroyAllWindows()
saveFile.close()
saveFile = open("camera_setings.txt","w")

saveFile.write(str(l_h_ball))
saveFile.write(" ")
saveFile.write(str(l_s_ball))
saveFile.write(" ")
saveFile.write(str(l_v_ball))
saveFile.write(" ")
saveFile.write(str(u_h_ball))
saveFile.write(" ")
saveFile.write(str(u_s_ball))
saveFile.write(" ")
saveFile.write(str(u_v_ball))
saveFile.write(" ")
saveFile.write(str(ball_min_size))
saveFile.write(" ")

saveFile.write(str(l_h_goal))
saveFile.write(" ")
saveFile.write(str(l_s_goal))
saveFile.write(" ")
saveFile.write(str(l_v_goal))
saveFile.write(" ")
saveFile.write(str(u_h_goal))
saveFile.write(" ")
saveFile.write(str(u_s_goal))
saveFile.write(" ")
saveFile.write(str(u_v_goal))
saveFile.write(" ")
saveFile.write(str(goal_min_size))
saveFile.close()



while(True):

    ret, frame = cap.read()
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    mask = cv2.inRange(hsv, lower_color_ball, upper_color_ball)
    contours_ball, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    mask_ball = mask

    mask = cv2.inRange(hsv, lower_color_goal, upper_color_goal)
    contours_goal, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    mask_goal = mask

    contours_ball = sorted(contours_ball, key=lambda x: cv2.contourArea(x), reverse=True)
    contours_goal = sorted(contours_goal, key=lambda x: cv2.contourArea(x), reverse=True)

    for cnt in contours_ball:
        (x, y, w, h) = cv2.boundingRect(cnt)
        if w*h > ball_min_size:
            cv2.circle(frame, (x+(w//2), y+(w//2)), (w//2),(0,0,255),5)
            ball_x = x
            ball_y = y
        else:    
            ball_x = -1
            ball_y = -1
        break

    for cnt in contours_goal:
        (x, y, w, h) = cv2.boundingRect(cnt)
        if w*h > goal_min_size:
            cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 10)
            goal_x = x
            goal_y = y
        else:
            goal_x = -1
            goal_y = -1
        break

cv2.destroyAllWindows()
