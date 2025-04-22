//Sadece motor sürücüyü test etmek için
const int motor1A = 2;
const int motor1B = 3;
const int motor2A = 4;
const int motor2B = 5;
String command;

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
String forward() {
  
  setMotor(HIGH, LOW, HIGH, LOW);
  command = "forward";
  return command;
  //İLERİ
}

String backward() {
  
  setMotor(LOW, HIGH, LOW, HIGH);
  command = "backward";
  return command;
  //GERİ
}

String left() {
  
  setMotor(LOW, HIGH, HIGH, LOW);
  command = "left";
  return command;
  //SOLA
}

String right() {
  
  setMotor(HIGH, LOW, LOW, HIGH);
  command = "right";
  return command;
  //SAĞA
}

String stop() {
  
  setMotor(LOW, LOW, LOW, LOW);
  command = "stop";
  return command;
  //DURDUR
}

void runAndControl(String command){
  Serial.println(command);
  delay(1000);
  //İşlevin kontrolünü sağlamak için
}

void loop() {
  runAndControl(forward());

  runAndControl(backward());

  runAndControl(stop());

  runAndControl(left());

  runAndControl(right());
}
