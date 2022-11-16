# Projeto: Braço Robótico com Reconhecimento de Imagens
# Prof. Dr. Marcel Stefan Wagner
# UAM - Projeto de Extensão - 2022/1
# v1.0 - Arduino UNO (Arduino IDE) | Python (PyCharm)
# Interface Arduino (HW) para controle do braço robótico e programação da Visão
# computacional com uso de PyCharm IDE e linguagem Python com OpenCV e CVzone
# --- Configuração da Visão Computacional ---


import cv2
import time
from cvzone.HandTrackingModule import HandDetector
from cvzone.SerialModule import SerialObject

cap = cv2.VideoCapture(0) #VideoCapture(0) = webcamNotebook | VideoCapture(1) = webcamUSB

detector = HandDetector(detectionCon=0.8, maxHands=1)
mySerial = SerialObject("COM6", 1200, 1) #Colocar a COM do Arduino UNO e velocidade em BAUDS

pTime = 0
cTime = 0

while True:
    success, img = cap.read()
    hands, img = detector.findHands(img)

    if hands:
        hand1 = hands[0]
        fingers = detector.fingersUp(hand1)
        print(fingers)
        mySerial.sendData(fingers)

    cTime = time.time()
    fps = 1/(cTime-pTime)
    pTime = cTime

    cv2.putText(img, str(int(fps)), (10,70), cv2.FONT_HERSHEY_PLAIN, 3, (255,0,255), 3)
    cv2.imshow("Controlador de Braco Robotico - MSW", img)
    key = cv2.waitKey(1)
    if key == 27: #ESC (em ASCII 27d = 1Bh)
        break

cap.release()
cv2.destroyAllWindows()
