#include "SPI.h" 
#include "RF24.h" 
#include "nRF24L01.h" 

RF24 radio(10, 9);
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
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();

}

void loop() {
  

  radio.read(&motors, sizeof(motors));

  Serial.print("Left: ");
  Serial.println(motors.left);
  Serial.print("Right: ");
  Serial.println(motors.right);

  delay(100);

}
