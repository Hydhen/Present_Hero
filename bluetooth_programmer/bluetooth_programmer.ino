// Basic Bluetooth sketch HC-06_01
// Connect the Hc-06 module and communicate using the serial monitor
//
// The HC-06 defaults to AT mode when first powered on.
// The default baud rate is 9600
// The Hc-06 requires all AT commands to be in uppercase. NL+CR should not be added to the command string
//
 
 
#include <SoftwareSerial.h>

const int rx = 12;
const int tx = 11;
SoftwareSerial bluetoothSerial(rx, tx);

// Connect the HC-06 TX to the Arduino RX on pin 12. 
// Connect the HC-06 RX to the Arduino TX on pin 11 through a voltage divider.
// 

// Command 	      Reply 	          Comment
// AT 	              OK 	          Communications test
// AT+VERSION 	      OKlinvorV1.8 	  Firmware version.
// AT+NAMEmyBTmodule  OKsetname 	  Sets the modules name to “myBTmodule”
// AT+PIN6789 	      OKsetPIN 	          Set the PIN to 6789
// AT+BAUD1 	      OK1200 	          Sets the baud rate to 1200
// AT+BAUD2 	      OK2400 	          Sets the baud rate to 2400
// AT+BAUD3 	      OK4800 	          Sets the baud rate to 4800
// AT+BAUD4 	      OK9600 	          Sets the baud rate to 9600
// AT+BAUD5 	      OK19200 	          Sets the baud rate to 19200
// AT+BAUD6 	      OK38400 	          Sets the baud rate to 38400
// AT+BAUD7 	      OK57600 	          Sets the baud rate to 57600
// AT+BAUD8 	      OK115200 	          Sets the baud rate to 115200
// AT+BAUD9 	      OK230400 	          Sets the baud rate to 230400
// AT+BAUDA 	      OK460800 	          Sets the baud rate to 460800
// AT+BAUDB 	      OK921600 	          Sets the baud rate to 921600
// AT+BAUDC 	      OK1382400 	  Sets the baud rate to 1382400

 
 
void setup() 
{
    Serial.begin(9600);
    Serial.println("Enter AT commands:");
 
    // HC-06 default serial speed is 9600
    bluetoothSerial.begin(9600);  
}
 
void loop()
{
 
    // Keep reading from HC-06 and send to Arduino Serial Monitor
    if (bluetoothSerial.available())
    {  
        Serial.write(bluetoothSerial.read());
    }
 
    // Keep reading from Arduino Serial Monitor and send to HC-06
    if (Serial.available())
    {
        bluetoothSerial.write(Serial.read());
    }
 
}
