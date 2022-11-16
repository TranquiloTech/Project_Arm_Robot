/*
/ Projeto: Braço Robótico com Reconhecimento de Imagens
/ Prof. Dr. Marcel Stefan Wagner
/ UAM - Projeto de Extensão - 2022/1
/ v1.0 - Arduino UNO (Arduino IDE) | Python (PyCharm)
/ Interface Arduino (HW) para controle do braço robótico e programação da Visão 
/ computacional com uso de PyCharm IDE e linguagem Python com OpenCV e CVzone
*/

//$PinkyRingMiddleIndexThumb ($PRMIT) = $MínimoAnelarMédioIndicadorPolegar ($MAMIP)

#include <Servo.h>

#define numOfValsRec 5
#define digitsPerValRec 1

Servo servoPinky;
Servo servoRing;
Servo servoMiddle;
Servo servoIndex;
Servo servoThumb;

int valsRec[numOfValsRec];
int stringLenght = numOfValsRec * digitsPerValRec + 1; //$00000
int counter = 0;

bool counterStart = false;

String receivedString;

void setup(){
  
  Serial.begin(1200);
  
  servoPinky.attach(11);
  servoRing.attach(10);
  servoMiddle.attach(9);
  servoIndex.attach(6);
  servoThumb.attach(5);
  
}

void receivedData(){
  while(Serial.available()){
   char c = Serial.read();
   
   if(c == '$'){
     counterStart = true;
   }
   if(counterStart){
     if(counter < stringLenght){
       receivedString = String(receivedString + c);
       counter++;
     }
     if(counter >= stringLenght){
       //$PRMIT
       for(int i = 0; i < numOfValsRec; i++){
         int num = (i * digitsPerValRec) + 1;
         valsRec[i] = receivedString.substring(num, num + digitsPerValRec).toInt();
       }
       receivedString = "";
       counter = 0;
       counterStart = false;
     }
   }
  }
}

void loop(){
  
  receivedData();
  
  Serial.print("$");
  for(int j = 0; j < 5; j++){
    Serial.print(valsRec[j]);
  }
  for(int k = 0; k < 5; k++){
    if(valsRec[k] != 0 && valsRec[k] != 1){
      Serial.println("Valor Incorreto!");
    }
  }
  Serial.println();
  
  if(valsRec[0] == 1){
    servoThumb.write(180);
  } else{
    servoThumb.write(0);
  }
  
  if(valsRec[1] == 1){
    servoIndex.write(180);
  } else{
    servoIndex.write(0);
  }
  
  if(valsRec[2] == 1){
    servoMiddle.write(180);
  } else{
    servoMiddle.write(0);
  }
  
  if(valsRec[3] == 1){
    servoRing.write(180);
  } else{
    servoRing.write(0);
  }
  
  if(valsRec[4] == 1){
    servoPinky.write(180);
  } else{
    servoPinky.write(0);
  }
  
  delay(100);
  
}

