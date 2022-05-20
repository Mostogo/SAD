# import the necessary packages
from collections import deque
from imutils.video import VideoStream
import numpy as np
import argparse
import cv2
import imutils
import time
import math
import serial

#communication avec la liaison serie
serial_port = serial.Serial(port='COM6', baudrate=115200, timeout=0.1)

def write_read(valeur):
    serial_port.write(bytes(valeur,'utf-8'))
    
    data = serial_port.readline()
    return data

    # on vide le buffer
    serial_port.flushInput()

# construct the argument parse and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-v", "--video",
    help="path to the (optional) video file")
ap.add_argument("-b", "--buffer", type=int, default=64,
    help="max buffer size")
args = vars(ap.parse_args())
# define the lower and upper boundaries of the "green"
# ball in the HSV color space, then initialize the
# list of tracked points
greenLower = (29, 86, 6)
greenUpper = (64, 255, 255)
pts = deque(maxlen=args["buffer"])

resolutionX = 1920     
resolutionY = 1080


centerObject = None
centerObjectX = 0
centerObjectY = 0
radius = 0
tirer=0

valeurHaut = 0
valeurBas = 0

minObjectSize = 50

# if a video path was not supplied, grab the reference
# to the webcam
if not args.get("video", False):
    vs = VideoStream(src=1).start()
# otherwise, grab a reference to the video file
else:
    vs = cv2.VideoCapture(args["video"])
# allow the camera or video file to warm up
#time.sleep(2.0)
# keep looping
while True:
    #time.sleep(0.5)
    # grab the current frame
    frame = vs.read()
    # handle the frame from VideoCapture or VideoStream
    frame = frame[1] if args.get("video", False) else frame
    # if we are viewing a video and we did not grab a frame,
    # then we have reached the end of the video
    if frame is None:
        break
    # resize the frame, blur it, and convert it to the HSV
    # color space
    frame = cv2.resize(frame, (resolutionX, resolutionY))
    # Centre camera
    middleScreenX = int(resolutionX/2)
    middleScreenY = int(resolutionY/2)
    middleScreen = (middleScreenX,middleScreenY)
    blurred = cv2.GaussianBlur(frame, (11, 11), 0)
    hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)
    # construct a mask for the color "green", then perform
    # a series of dilations and erosions to remove any small
    # blobs left in the mask
    mask = cv2.inRange(hsv, greenLower, greenUpper)
    mask = cv2.erode(mask, None, iterations=2)
    mask = cv2.dilate(mask, None, iterations=2)
 # find contours in the mask and initialize the current
    # (x, y) center of the ball
    cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
        cv2.CHAIN_APPROX_SIMPLE)
    cnts = imutils.grab_contours(cnts)
    # only proceed if at least one contour was found
    if len(cnts) > 0:
        # find the largest contour in the mask, then use
        # it to compute the minimum enclosing circle and
        # centroid
        c = max(cnts, key=cv2.contourArea)
        ((x, y), radius) = cv2.minEnclosingCircle(c)
        M = cv2.moments(c)
        centerObjectX = int(M["m10"] / M["m00"])
        centerObjectY = int(M["m01"] / M["m00"])
        centerObject = (centerObjectX, centerObjectY)
        # only proceed if the radius meets a minimum size
        if radius > minObjectSize:
            # draw the circle and centroid on the frame,
            # then update the list of tracked points
            cv2.circle(frame, (int(x), int(y)), int(radius),
                (0, 255, 255), 2)
            cv2.circle(frame, centerObject, 5, (0, 0, 255), -1)
            
            # Zone pour tirer, cercle initial divise par 2
            cv2.circle(frame, (int(x), int(y)), int(radius/2), (0, 0, 255), 2)
            messageDistance = "x = " + str(valeurBas) +",    y = " + str(valeurHaut)
            #cv2.putText(frame, text=messageDistance, org=(int(x), int(y+20)), fontFace=cv2.FONT_HERSHEY_TRIPLEX, fontScale=1, color=(255,0, 255),thickness=1)
            # Distance entre middleScreen et centre objet detecte
            cv2.line(frame, middleScreen, centerObject, (255,0,0), 5)

    # update the points queue
    pts.appendleft(centerObject)
 # loop over the set of tracked points
    for i in range(1, len(pts)):
        # if either of the tracked points are None, ignore
        # them
        if pts[i - 1] is None or pts[i] is None:
            continue
        # otherwise, compute the thickness of the line and
        # draw the connecting lines
        #thickness = int(np.sqrt(args["buffer"] / float(i + 1)) * 2.5)
        #cv2.line(frame, pts[i - 1], pts[i], (0, 0, 255), thickness)
    # Point central
    cv2.circle(frame, middleScreen, 1, (0,0,255),10)
    
    distance = math.sqrt((centerObjectX - middleScreenX)**2 + (centerObjectY - middleScreenY)**2)
    #print(distance)
    #print(centerObjectY)
    # show the frame to our screen
    cv2.imshow("Frame", frame)

    if radius > minObjectSize:
        if not ((middleScreenX == centerObjectX) & (middleScreenY == centerObjectY)):
            if not (middleScreenX == centerObjectX):
                if (centerObjectX < middleScreenX):
                    valeurBas = int((centerObjectX - middleScreenX))
                    #print(int(valeurBas))
                    #print("GAUCHE")
                else:
                    valeurBas = int((centerObjectX - middleScreenX))
                    #print(int(valeurBas))
                    #print("DROITE")
            if not (middleScreenY == centerObjectY):
                if (centerObjectY < middleScreenY):
                    valeurHaut = int((middleScreenY - centerObjectY))
                    #print(int(valeurHaut))
                    #print("HAUT")
                else:
                    valeurHaut = int((middleScreenY - centerObjectY))
                    #print(int(valeurHaut))
                    #print("BAS")
        
        if ((middleScreenX - radius/2 < centerObjectX < middleScreenX + radius/2) & (middleScreenY - radius/2 < centerObjectY < middleScreenY + radius/2)):
            tirer=1
            print("TIRRRREEEEEERRR")
        else:
            tirer=0
            print(" noooooooonn ")
    else:
        valeurBas=0
        valeurHaut=0

    #envoyer donnee 

    message="/"+str(valeurHaut)+"/"+str(valeurBas)+"/"+str(tirer)+"/"+str(radius)
    value = write_read(message)
    #print(message) 
    #print(value) 
    key = cv2.waitKey(1) & 0xFF
    # if the 'q' key is pressed, stop the loop
    if key == ord("q"):
        break
# if we are not using a video file, stop the camera video stream
if not args.get("video", False):
    vs.stop()
# otherwise, release the camera
else:
    vs.release()
# close all windows
cv2.destroyAllWindows()
