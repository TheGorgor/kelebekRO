#include "SPI.h" 
#include "RF24.h" 
#include "nRF24L01.h" 

RF24 radio(9, 8);
const byte address[6] = "GETRO";

byte motorValues[2];

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
  
  motorValues[0] = map(analogRead(A3), 0, 1023, 0, 255);
  motorValues[1] = map(analogRead(A5), 0, 1023, 0, 255);

  radio.write(&motorValues, sizeof(motorValues));

  Serial.print("L: ");
  Serial.println(motorValues[0]);
  Serial.print("R: ");
  Serial.println(motorValues[1]);

  delay(100);

}
