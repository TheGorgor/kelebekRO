#include "SPI.h" 
#include "RF24.h" 
#include "nRF24L01.h" 

RF24 radio(9, 8);
const byte address[6] = "GETRO";

struct motorValues{
   int left;
   int right;
} motors;

void setup() {
 
  pinMode(A3, INPUT);
  //VRy - 1
 
  pinMode(A5, INPUT);
  //VRy - 2

  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

}

void loop() {
  
  motors.left = map(analogRead(A3), 0, 1023, 0, 255);
  motors.right = map(analogRead(A5), 0, 1023, 0, 255);

  radio.write(&motors, sizeof(motors));

  Serial.print("L: ");
  Serial.println(motors.left);
  Serial.print("R: ");
  Serial.println(motors.right);

  delay(100);

}
