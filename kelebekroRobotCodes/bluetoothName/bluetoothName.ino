#include <SoftwareSerial.h>

SoftwareSerial mySerial(6, 7); // RX, TX
String command = ""; // Stores response of bluetooth device
// which simply allows \n between each
// response.
void setup()
{
// Open serial communications and wait for port to open:
Serial.begin(115200);
Serial.println("Type AT commands!");
// SoftwareSerial "com port" data rate. JY-MCU v1.03 defaults to 9600.
mySerial.begin(9600);
}
void loop()
{
// Read device output if available.
if (mySerial.available())
{
while(mySerial.available())
{ // While there is more to be read, keep reading.
command += (char)mySerial.read();
}
Serial.println(command);
command = ""; // No repeats
}
// Read user input if available.
if (Serial.available())
{
delay(10); // The DELAY!
mySerial.write(Serial.read());
}
}

//AT+NAMExyzt
//AT+NAME1234
//gibi komutlar vereceksin monitörden, komut olarak algılayıp uygulayacak