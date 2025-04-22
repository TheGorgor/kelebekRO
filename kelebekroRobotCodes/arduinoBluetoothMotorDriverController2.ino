//Kütüphanesiz
int motor1A = 2;
int motor1B = 3;
int motor2A = 4;
int motor2B = 5;

char data;
//Bluetooth ile alınacak veriyi data değişkeninde depolayacağız

void setup() {
  
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);

  Serial.begin(9600);
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
  //İLERİ
}

void backward() {
  
  setMotor(LOW, HIGH, LOW, HIGH);
  //GERİ
}

void left() {
  
  setMotor(LOW, HIGH, HIGH, LOW);
  //SOLA
}

void right() {
  
  setMotor(HIGH, LOW, LOW, HIGH);
  //SAĞA
}

void stop() {
  
  setMotor(LOW, LOW, LOW, LOW);
  //DURDUR
}

void loop() {
  
  if (Serial.available()) {
    data = Serial.read();
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

  } else {
      stop();
  }

}
