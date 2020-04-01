
import cv2
import numpy as np
from dataclasses import dataclass

@dataclass
class coordinates:
    x_1: int = -1
    y_1: int = -1
    x_2: int = -1
    y_2: int = -1

ball = coordinates()
goal_y = coordinates()
goal_b = coordinates()
robot = coordinates()
img_number = 0
path = r'C:\Users\bukaj\Desktop\robocup_ml_dataset\images\{}.png'.format(img_number) #560*320
img = cv2.imread(path) 


drawing = True
mode = 'ball'

def draw_circle(event,x,y,flags,param):
  global ix,iy,drawing,mode

  if event == cv2.EVENT_LBUTTONDOWN:
      if drawing:
          drawing = False
          if mode == "ball":
              ball.x_1 = x
              ball.y_1 = y
          elif mode == "goal_y":
              goal_y.x_1 = x
              goal_y.y_1 = y
          elif mode == "goal_b":
              goal_b.x_1 = x
              goal_b.y_1 = y 
          elif mode == "robot":
              robot.x_1 = x
              robot.y_1 = y
            
  elif event == cv2.EVENT_MOUSEMOVE:
    img = cv2.imread(path) 
    cv2.line(img, (0,y),(560, y), (0, 0, 255), thickness=1, lineType=8)
    cv2.line(img, (x,0),(x,320), (0, 0, 255), thickness=1, lineType=8)
    cv2.rectangle(img , (ball.x_1,ball.y_1), (ball.x_2,ball.y_2),(0, 116, 255),thickness=2)
    cv2.rectangle(img , (goal_b.x_1,goal_b.y_1), (goal_b.x_2,goal_b.y_2),(255, 0, 0),thickness=2)
    cv2.rectangle(img , (goal_y.x_1,goal_y.y_1), (goal_y.x_2,goal_y.y_2),(0, 255, 255),thickness=2)
    cv2.rectangle(img , (robot.x_1,robot.y_1), (robot.x_2,robot.y_2),(255, 0, 255),thickness=2)
    cv2.imshow('image',img)

  elif event == cv2.EVENT_LBUTTONUP:
       if not drawing:
          drawing = True
          if mode == "ball":
              ball.x_2 = x
              ball.y_2 = y              
          elif mode == "goal_y":
              goal_y.x_2 = x
              goal_y.y_2 = y
          elif mode == "goal_b":
              goal_b.x_2 = x
              goal_b.y_2 = y 
          elif mode == "robot":
              robot.x_2 = x
              robot.y_2 = y
def reset():
     ball.x_1,ball.x_2,ball.y_1,ball.y_2 = -1,-1,-1,-1
     goal_b.x_1,goal_b.x_2,goal_b.y_1,goal_b.y_2 = -1,-1,-1,-1
     goal_y.x_1,goal_y.x_2,goal_y.y_1,goal_y.y_2 = -1,-1,-1,-1
     robot.x_1, robot.x_2, robot.y_1, robot.y_2 = -1,-1,-1,-1

def rectangles():
    img = cv2.imread(path) 
    cv2.line(img, (0,y),(560, y), (0, 0, 255), thickness=1, lineType=8)
    cv2.line(img, (x,0),(x,320), (0, 0, 255), thickness=1, lineType=8)
    cv2.rectangle(img , (ball.x_1,ball.y_1), (ball.x_2,ball.y_2),(0, 116, 255),thickness=2)
    cv2.rectangle(img , (goal_b.x_1,goal_b.y_1), (goal_b.x_2,goal_b.y_2),(255, 0, 0),thickness=2)
    cv2.rectangle(img , (goal_y.x_1,goal_y.y_1), (goal_y.x_2,goal_y.y_2),(0, 255, 255),thickness=2)
    cv2.rectangle(img , (robot.x_1,robot.y_1), (robot.x_2,robot.y_2),(255, 0, 255),thickness=2)
    cv2.imshow('image',img)

img = cv2.imread(path) 
cv2.namedWindow('image')
cv2.setMouseCallback('image',draw_circle)

cv2.namedWindow('parameters')
parameters = np.zeros((600,600,3), np.uint8)

while(1):
 path = r'C:\Users\bukaj\Desktop\robocup_ml_dataset\images\{}.png'.format(img_number)

 parameters = np.zeros((600,600,3), np.uint8)
 cv2.putText(parameters, 'image number = {}'.format(img_number) , (10,30), cv2.FONT_HERSHEY_SIMPLEX ,1, (255,0,0), 2, cv2.LINE_AA)
 cv2.putText(parameters, 'ball = {}, {}, {}, {}'.format(ball.x_1,ball.y_1,ball.x_2,ball.y_2) , (10,70), cv2.FONT_HERSHEY_SIMPLEX ,1, (255,0,0), 2, cv2.LINE_AA)
 cv2.putText(parameters, 'goal yelow = {}, {}, {}, {}'.format(goal_y.x_1,goal_y.y_1,goal_y.x_2,goal_y.y_2) , (10,110), cv2.FONT_HERSHEY_SIMPLEX ,1, (255,0,0), 2, cv2.LINE_AA)
 cv2.putText(parameters, 'goal blue = {}, {}, {}, {}'.format(goal_b.x_1,goal_b.y_1,goal_b.x_2,goal_b.y_2) , (10,150), cv2.FONT_HERSHEY_SIMPLEX ,1, (255,0,0), 2, cv2.LINE_AA)
 cv2.putText(parameters, 'robot = {}, {}, {}, {}'.format(robot.x_1,robot.y_1,robot.x_2,robot.y_2) , (10,190), cv2.FONT_HERSHEY_SIMPLEX ,1, (255,0,0), 2, cv2.LINE_AA)

 cv2.putText(parameters, 'mode = ' + mode, (10,230) , cv2.FONT_HERSHEY_SIMPLEX ,1, (0, 255, 255), 2, cv2.LINE_AA)

 cv2.putText(parameters, 'z = goal_yelow', (10,300) , cv2.FONT_HERSHEY_SIMPLEX ,1, (0, 255, 255), 2, cv2.LINE_AA)
 cv2.putText(parameters, 'm = goal_blue', (10,340) , cv2.FONT_HERSHEY_SIMPLEX ,1, (255,0,0), 2, cv2.LINE_AA)
 cv2.putText(parameters, 'l = ball', (10,380) , cv2.FONT_HERSHEY_SIMPLEX ,1, (0, 116, 255), 2, cv2.LINE_AA)
 cv2.putText(parameters, 'r = robot ', (10,420) , cv2.FONT_HERSHEY_SIMPLEX ,1, (255, 0, 255), 2, cv2.LINE_AA)

 cv2.putText(parameters, 'd = next', (10,500) , cv2.FONT_HERSHEY_SIMPLEX ,1, (255, 0, 0), 2, cv2.LINE_AA)
 cv2.putText(parameters, 'a = back', (10,540) , cv2.FONT_HERSHEY_SIMPLEX ,1, (255, 0, 0), 2, cv2.LINE_AA)
 cv2.putText(parameters, 'esc = end', (10,580) , cv2.FONT_HERSHEY_SIMPLEX ,1, (255, 0, 0), 2, cv2.LINE_AA)
 cv2.imshow('parameters',parameters)

 cv2.moveWindow('parameters',700,50)
 cv2.moveWindow('image',100,50)
 k = cv2.waitKey(1) & 0xFF
 if k == ord('l'):
    mode = "ball"
 elif k == ord('m'):
     mode = "goal_b"
 elif k == ord('z'):
     mode = "goal_y"
 elif k == ord('r'):
     mode = "robot"
 elif k == ord('q'):
     reset()
 elif k == ord('d'):   
     with open(r'C:\Users\bukaj\Desktop\robocup_ml_dataset\data.txt', 'r') as file:
        data = file.readlines()
     data[img_number] = '{} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} \n'.format(
     ball.x_1,ball.y_1,ball.x_2,ball.y_2,
     goal_y.x_1,goal_y.y_1,goal_y.x_2,goal_y.y_2,
     goal_b.x_1,goal_b.y_1,goal_b.x_2,goal_b.y_2,
     robot.x_1,robot.y_1,robot.x_2,robot.y_2)
     with open(r'C:\Users\bukaj\Desktop\robocup_ml_dataset\data.txt', 'w') as file:
        file.writelines( data )
     img_number += 1
     with open(r'C:\Users\bukaj\Desktop\robocup_ml_dataset\data.txt', 'r') as file:
        data = file.readlines()
        ball.x_1,ball.y_1,ball.x_2,ball.y_2,goal_y.x_1,goal_y.y_1,goal_y.x_2,goal_y.y_2,goal_b.x_1,goal_b.y_1,goal_b.x_2,goal_b.y_2,robot.x_1,robot.y_1,robot.x_2,robot.y_2 = map(int, data[img_number].split())
        img = cv2.imread(path) 
        cv2.imshow('image',img)
 elif k == ord('a'):
     with open(r'C:\Users\bukaj\Desktop\robocup_ml_dataset\data.txt', 'r') as file:
        data = file.readlines()
     data[img_number] = '{} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} \n'.format(
     ball.x_1,ball.y_1,ball.x_2,ball.y_2,
     goal_y.x_1,goal_y.y_1,goal_y.x_2,goal_y.y_2,
     goal_b.x_1,goal_b.y_1,goal_b.x_2,goal_b.y_2,
     robot.x_1,robot.y_1,robot.x_2,robot.y_2)    
     with open(r'C:\Users\bukaj\Desktop\robocup_ml_dataset\data.txt', 'w') as file:
        file.writelines( data )
     img_number -= 1
     with open(r'C:\Users\bukaj\Desktop\robocup_ml_dataset\data.txt', 'r') as file:
         data = file.readlines()
         ball.x_1,ball.y_1,ball.x_2,ball.y_2,goal_y.x_1,goal_y.y_1,goal_y.x_2,goal_y.y_2,goal_b.x_1,goal_b.y_1,goal_b.x_2,goal_b.y_2,robot.x_1,robot.y_1,robot.x_2,robot.y_2= map(int, data[img_number].split())
         img = cv2.imread(path) 
         cv2.imshow('image',img)
 elif k == 27:
    break


cv2.destroyAllWindows() 