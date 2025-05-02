#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// nRF modülünü tanımlıyoruz: CE pini 9, CSN pini 10
RF24 radio(9, 10);

// Kablosuz iletişim adresi (kumanda & robot aynı adresi kullanmalı)
const byte adres[] = "robot";

// Robotun yönünü (açısını) takip etmek için değişken
float heading = 0;

// joystick verisini -255 ile 255 arası değere dönüştüren fonksiyon
int mapJoystick(int val) {
  return map(val, 0, 1023, -255, 255);
}

// nRF üzerinden gönderilecek veri yapısı
struct MotorData {
  int left;   // sol motor hızı
  int right;  // sağ motor hızı
};

void setup() {
  // Joystick pinlerini tanımla
  pinMode(A2, INPUT); // VRx1: sağ/sol hareket
  pinMode(A3, INPUT); // VRy1: ileri/geri
  pinMode(A4, INPUT); // VRx2: yön dönüşü

  Serial.begin(9600);     // Seri monitör için
  radio.begin();          // nRF başlat
  radio.setPALevel(RF24_PA_LOW);  // Güç seviyesi (düşük: daha az parazit)
  radio.setChannel(115);          // Kanal belirle (aynı olmak zorunda)
  radio.openWritingPipe(adres);   // Gönderme adresi ayarla
  radio.stopListening();          // Gönderici moduna geç
}

void loop() {
  // Joystick verilerini oku ve -255 ila 255 arasında yeniden ölçekle
  int x = mapJoystick(analogRead(A2)); // VRx1
  int y = mapJoystick(analogRead(A3)); // VRy1
  int rot = mapJoystick(analogRead(A4)); // VRx2

  // Joystick deadzone (küçük titreşimleri yok say)
  if (abs(x) < 20) x = 0;
  if (abs(y) < 20) y = 0;
  if (abs(rot) < 20) rot = 0;

  // Dönüş açısını güncelle (FPS oyunlarındaki mouse gibi)
  heading += rot * 0.05; // 0.05 dönüş hassasiyeti
  float rad = heading * PI / 180.0; // Dereceyi radyana çevir

  // Joystick vektörünü robotun açısına göre döndür (rotation matrix)
  float forward = y * cos(rad) + x * sin(rad);
  float strafe  = -y * sin(rad) + x * cos(rad);

  // Motor değerlerini hesapla (tank sürüş mantığı)
  int leftMotor = constrain(forward + strafe, -255, 255);
  int rightMotor = constrain(forward - strafe, -255, 255);

  // Gönderilecek veriyi hazırla
  MotorData data = {leftMotor, rightMotor};

  // Veriyi robot tarafına gönder
  radio.write(&data, sizeof(data));

  // Seri monitöre yaz (test ve debug için)
  Serial.print("L: "); Serial.print(leftMotor);
  Serial.print(" | R: "); Serial.println(rightMotor);

  delay(20); // Sistem nefes alsın (20ms = ~50Hz)
}
