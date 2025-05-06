//SoftwareSerial kütüphanesi ile
#include <SoftwareSerial.h>

int RX = 10; //HC-06 için 10 numarılı pin öneriliyor
int TX = 11; //HC-06 için 11 numarılı pin öneriliyor
             //Ancak HC-06'lar genellikle 3,3V toleranslıdır ve 10 ve 11 numaralı pinlere bağlanıldığında

SoftwareSerial bluetooth(TX, RX);

String bluetoothName = "LANCE";
String bluetoothPass = "GETRONAGAN2025";

byte motor1A = 2;
byte motor1B = 3;
byte motor2A = 4;
byte motor2B = 5;


char data;
//Bluetooth ile alınacak veriyi data değişkeninde depolayacağız

void setup() {
  
  bluetooth.begin(38400);
  Serial.begin(19200);

  bluetooth.println("AT+NAME=LANCE");
  delay(1000);

  bluetooth.print("AT+PIN2025");
  delay(1000);

  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);

  stop();
  
  
}

void setMotor(int m1a, int m1b, int m2a, int m2b){
  
  digitalWrite(motor1A, m1a);
  digitalWrite(motor1B, m1b);
  digitalWrite(motor2A, m2a);
  digitalWrite(motor2B, m2b);
  //Motorları ayarlamak için
}
void forward() {
  
  setMotor(HIGH, LOW, HIGH, LOW);
  Serial.print("Forward: ");
  //İLERİ
}

void backward() {
  
  setMotor(LOW, HIGH, LOW, HIGH);
  Serial.print("Backward: ");
  //GERİ
}

void left() {
  
  setMotor(LOW, HIGH, HIGH, LOW);
  Serial.print("Left: ");
  //SOLA
}

void right() {
  
  setMotor(HIGH, LOW, LOW, HIGH);
  Serial.print("Right: ");
  //SAĞA
}

void stop() {
  
  setMotor(LOW, LOW, LOW, LOW);
  Serial.print("Stop: ");
  //DURDUR
}

void loop() {
  
  if (bluetooth.available()) {
    data = bluetooth.read();
    //Bluetooth ile alınan veri data değişkenine atandı
    switch (data) {
      
      case 'F':
        forward();
        break;
      
      case 'B':
        backward();
        break;
      
      case 'L':
        left();
        break;
      
      case 'R':
        right();
        break;
      
      case 'S':
        stop();
        break;
    }

    Serial.println(data);
    //Kontrol amaçlı

  } 

}
