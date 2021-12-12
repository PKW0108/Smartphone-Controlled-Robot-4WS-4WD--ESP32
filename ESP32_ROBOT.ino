#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

static const int servoPin =13 ;  
static const int servoPin1 =2;                 
static const int servoPin2 =18;
static const int servoPin3 =19;

const int in1 = 26; 
const int in2 = 27; 
const int in3 = 33;
const int in4 = 32;
const int en1 = 5;
const int en2 = 12;

const int freq = 3000;
const int pwmChannel1 = 0;
const int pwmChannel2 = 1;
const int resolution = 8;

int bt_data = 0;
int Speed=220;   // original speed

int angle  = 100;   // when the robot is powered on, the servos go to straight position
int angle2 = 90;
int angle3 = 95;
int angle4 = 90;

const int freqservo = 50;
const int ServoChannel1 = 2;
const int ServoChannel2 = 3;
const int ServoChannel3 = 4;
const int ServoChannel4 = 5;
const int resolution16 = 16;

void setup() {
  
  Serial.begin(115200);
  SerialBT.begin("ESP32_PARK"); //Bluetooth device name
  
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);


ledcSetup(ServoChannel1, freqservo, resolution16);
ledcSetup(ServoChannel2, freqservo, resolution16);
ledcSetup(ServoChannel3, freqservo, resolution16);
ledcSetup(ServoChannel4, freqservo, resolution16);

  ledcAttachPin(servoPin,ServoChannel1);
  ledcAttachPin(servoPin1,ServoChannel2);
  ledcAttachPin(servoPin2,ServoChannel3);
  ledcAttachPin(servoPin3,ServoChannel4); 

  ledcSetup(pwmChannel1, freq, resolution);
  ledcSetup(pwmChannel2, freq, resolution);
  ledcAttachPin(en1, pwmChannel1);
  ledcAttachPin(en2, pwmChannel2);


}

void loop() {

    if (SerialBT.available()){
     bt_data = SerialBT.read();
     SerialBT.print(bt_data);
    }

  ledcWrite(pwmChannel1, Speed);
  ledcWrite(pwmChannel2, Speed);
  
  ledcWrite(2,map(angle,  0, 180, 1638, 7864)); // converting to 0 - 180 degrees
  ledcWrite(3,map(angle2, 0, 180, 1638, 7864));
  ledcWrite(4,map(angle3, 0, 180, 1638, 7864));
  ledcWrite(5,map(angle4, 0, 180, 1638, 7864));

  
     if(bt_data == 1){ forward(); 

     if(Speed<255) {                // line of code for gradually speeding up when going foward.
  ledcWrite(pwmChannel1, Speed);   
  ledcWrite(pwmChannel2, Speed); 
  Speed+=1;
}
     } 
           
else if(bt_data == 2){backward(); 

     if(Speed<255) {              // line of code for gradually speeding up when going backward.
  ledcWrite(pwmChannel1, Speed);   
  ledcWrite(pwmChannel2, Speed); 
  Speed+=1;
}
}
                      
else if(bt_data == 3 ){  turnLeft(); }                       
else if(bt_data == 4 ){  turnRight(); }                      
else if(bt_data == 5){  Stop(); Speed = 220;    }  // resets the speed to 220

   else if(bt_data == 6) { straight(); }    // servo controls
   else if(bt_data == 7) { circle();   }
   else if(bt_data == 8) { left();     }
   else if(bt_data == 9) { Hardleft();     }
   else if(bt_data == 10) { right();     }
   else if(bt_data == 11) { Hardright();     }
   else if(bt_data == 12) { horizontal(); }
   else if(bt_data == 13) { DiaLR(); }
   else if(bt_data == 14) { DiaRL(); } 
  delay(20);  

  }


  void forward(){  //forword
digitalWrite(in1, HIGH); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
digitalWrite(in3, LOW);  //Left Motor backword Pin 
digitalWrite(in4, HIGH); //Left Motor forword Pin 

}

void backward(){ //backword
digitalWrite(in1, LOW);  //Right Motor forword Pin 
digitalWrite(in2, HIGH); //Right Motor backword Pin 
digitalWrite(in3, HIGH); //Left Motor backword Pin 
digitalWrite(in4, LOW);  //Left Motor forword Pin 

}

void turnRight(){ //turnRight
digitalWrite(in1, LOW);  //Right Motor forword Pin 
digitalWrite(in2, HIGH); //Right Motor backword Pin  
digitalWrite(in3, LOW);  //Left Motor backword Pin 
digitalWrite(in4, HIGH); //Left Motor forword Pin 
}

void turnLeft(){ //turnLeft
digitalWrite(in1, HIGH); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
digitalWrite(in3, HIGH); //Left Motor backword Pin 
digitalWrite(in4, LOW);  //Left Motor forword Pin 
}

void Stop(){ //stop
digitalWrite(in1, LOW); //Right Motor forword Pin 
digitalWrite(in2, LOW); //Right Motor backword Pin 
digitalWrite(in3, LOW); //Left Motor backword Pin 
digitalWrite(in4, LOW); //Left Motor forword Pin 
}  

void straight() {
  angle  = 100;
  angle2 = 90;
  angle3 = 95;
  angle4 = 90;
}
void circle() {
  angle  = 55;
  angle2 = 135;
  angle3 = 50;
  angle4 = 135;
  
}

void left() {
  angle  = 74;
  angle2 = 45;
  angle3 = 95;
  angle4 = 90;
}

void Hardleft() {
  angle  = 74;
  angle2 = 45;
  angle3 = 140;
  angle4 = 116;
}

void right() {
  angle  = 145;
  angle2 = 116;
  angle3 = 95;
  angle4 = 90;
}

void Hardright() {
  angle  = 145;
  angle2 = 116;
  angle3 = 69;
  angle4 = 45;
}
void horizontal() {
  angle  = 0;
  angle2 = 0;
  angle3 = 0;
  angle4 = 0;
}

void DiaLR() {
  angle  = 145;
  angle2 = 135;
  angle3 = 140;
  angle4 = 135;
}

void DiaRL() {
  angle  = 55;
  angle2 = 45;
  angle3 = 50;
  angle4 = 45;
}
