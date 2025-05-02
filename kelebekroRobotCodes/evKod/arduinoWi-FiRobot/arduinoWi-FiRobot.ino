#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// CE ve CSN pinlerini ayarla
RF24 radio(9, 10);

// Aynı adresle eşleşmek zorunda
const byte adres[] = "robot";

// Gelen veriyi tutacak yapı (kumanda ile aynı struct olmalı!)
struct MotorData {
  int left;
  int right;
};

// Motorlara PWM sinyali gönderme fonksiyonu
void setMotors(int leftMotor, int rightMotor) {
  // Değerleri sınırla
  leftMotor = constrain(leftMotor, -255, 255);
  rightMotor = constrain(rightMotor, -255, 255);

  // Sol motor kontrolü (2 ve 3 pinleri)
  if (leftMotor > 0) {
    analogWrite(2, leftMotor);
    analogWrite(3, 0);
  } else {
    analogWrite(2, 0);
    analogWrite(3, -leftMotor);
  }

  // Sağ motor kontrolü (4 ve 5 pinleri)
  if (rightMotor > 0) {
    analogWrite(4, rightMotor);
    analogWrite(5, 0);
  } else {
    analogWrite(4, 0);
    analogWrite(5, -rightMotor);
  }
}

void setup() {
  // Motor pinlerini çıkış olarak ayarla
  pinMode(2, OUTPUT); pinMode(3, OUTPUT);
  pinMode(4, OUTPUT); pinMode(5, OUTPUT);

  Serial.begin(9600);     // Seri monitör (opsiyonel)

  radio.begin();          // nRF başlat
  radio.setPALevel(RF24_PA_LOW);  // Güç seviyesi
  radio.setChannel(115);          // Kanal aynı olmalı
  radio.openReadingPipe(1, adres); // Alıcı adresi
  radio.startListening();         // Alıcı moduna geç
}

void loop() {
  // Gelen veri varsa
  if (radio.available()) {
    MotorData data;
    radio.read(&data, sizeof(data)); // Veriyi oku
    setMotors(data.left, data.right); // Motorlara uygula

    // Seri monitöre yaz (debug için)
    Serial.print("L: "); Serial.print(data.left);
    Serial.print(" | R: "); Serial.println(data.right);
  }
}
