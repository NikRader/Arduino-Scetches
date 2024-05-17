
#include "BluetoothSerial.h"
#include <ESP32Servo.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

Servo s1;
Servo s2;
Servo s3;
Servo s4;
Servo s5;
Servo s6;
Servo s7;
Servo s8;
Servo s9;
Servo s10;

// Define variables
int forwardPin = 27;  // Remote control movement pins
int reversePin = 14;
int rightPin = 12;
int leftPin = 13;

int forwardVal = 0;  // Remote control variables
int reverseVal = 0;
int rightVal = 0;
int leftVal = 0;

int counter = 0; // Loop counter variable
float lag = .5712; // Phase lag between segments
int frequency = 1; // Oscillation frequency of segments.
int amplitude = 30; // Amplitude of the serpentine motion of the snake
int rightOffset = 5; // Right turn offset
int leftOffset = -10; // Left turn offset
int offset = 6; // Variable to correct servos that are not exactly centered
int delayTime = 7; // Delay between limb movements
int startPause = 5000;  // Delay time to position robot
int test = -3; // Test varialble takes values from -6 to +5


BluetoothSerial SerialBT;
 const int LED = 2;
void setup() {
   s1.attach(32);
   s2.attach(33);
   s3.attach(25);
   s4.attach(26);
   s5.attach(23);
   s6.attach(22);
   s7.attach(21);
   s8.attach(19);
   s9.attach(18);
   s10.attach(5);

  Serial.begin(115200);

  Serial.setTimeout(5); // Прием сообщения за 5 мс
  SerialBT.setTimeout(5); // Прием сообщения за 5 мс

  SerialBT.begin("ESP_32"); //Bluetooth device name
  pinMode(LED, OUTPUT);

}

void loop() {
  if (Serial.available()) {
     SerialBT.print(Serial.read());
  }
  // Сообщение на esp
  if (SerialBT.available()) {
    char command = SerialBT.read();
    if (command == '2'){
   s1.write(90+offset+amplitude*cos(5*lag));
   s2.write(90+offset+amplitude*cos(4*lag));
   s3.write(90+offset+amplitude*cos(3*lag));
   s4.write(90+amplitude*cos(2*lag));
   s5.write(90+amplitude*cos(1*lag));
   s6.write(90+amplitude*cos(0*lag));
   s7.write(90+amplitude*cos(-1*lag));
   s8.write(90+amplitude*cos(-2*lag));
   s9.write(90+amplitude*cos(-3*lag));
   s10.write(90+amplitude*cos(-4*lag));
    }
    if(command == '4'){
    for(counter = 0; counter < 360; counter += 1)  {
      delay(delayTime);
      s1.write(90+offset+amplitude*cos(frequency*counter*3.14159/180+5*lag));
      s2.write(90+offset+amplitude*cos(frequency*counter*3.14159/180+4*lag));
      s3.write(90+offset+amplitude*cos(frequency*counter*3.14159/180+3*lag));
      s4.write(90+amplitude*cos(frequency*counter*3.14159/180+2*lag));
      s5.write(90+amplitude*cos(frequency*counter*3.14159/180+1*lag));
      s6.write(90+amplitude*cos(frequency*counter*3.14159/180+0*lag));
      s7.write(90+amplitude*cos(frequency*counter*3.14159/180-1*lag));
      s8.write(90+amplitude*cos(frequency*counter*3.14159/180-2*lag));
      s9.write(90+amplitude*cos(frequency*counter*3.14159/180-3*lag));
      s10.write(90+amplitude*cos(frequency*counter*3.14159/180-4*lag));
    }
    
    }
    if(command == '6'){
   
    }
    if(command == '8'){
   
    }
    
  }
  delay(20);
}
