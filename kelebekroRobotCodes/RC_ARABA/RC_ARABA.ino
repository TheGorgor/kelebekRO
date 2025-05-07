#include <SoftwareSerial.h>
const int LPWM = 10; 
const int RPWM = 9;
const int L1PWM = 3; 
const int R1PWM = 11;
SoftwareSerial bt(6,7);
char data;
void setup() {
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(11,OUTPUT);
  Serial.begin(9600); 
  bt.begin(9600);
}

void loop() {
 if(bt.available())
{
 char data= bt.read(); 
 Serial.println(data);
 if(data=='F')
 {
  analogWrite(9,255);
  analogWrite(10,0);
  analogWrite(3,255);
  analogWrite(11,0);
  } 
  else if (data=='S')
  {
    analogWrite(9,0);
    analogWrite(10,0);
    analogWrite(3,0);
    analogWrite(11,0);
    
    }
  else if (data=='B')
  {
    
  analogWrite(9,0);
  analogWrite(10,100);
  analogWrite(3,0);
  analogWrite(11,100);
    
    
    }
    
  else if (data=='R')
  {
    
  analogWrite(9,0);
  analogWrite(10,100);
  analogWrite(3,-100);
  analogWrite(11,0);
    
    
    }
  else if (data=='L')
  {
    
  analogWrite(9,-100);
  analogWrite(10,0);
  analogWrite(3,0);
  analogWrite(11,100);
    
    
    }  

  }
}
