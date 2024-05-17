
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
  SerialBT.begin("ESP_32"); //Bluetooth device name
  pinMode(LED, OUTPUT);
 delay(1000);
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
}

void loop() {
  delay(500);
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  if (Serial.available()) {
     SerialBT.print(Serial.readString());
  }
  // Сообщение на esp от Android
  if (SerialBT.available()>1) {
  char  com = SerialBT.read();
  int val = SerialBT.parseInt();
   
   Serial.println("Параметр:");
   Serial.println(com); 
   Serial.println("Значение:");
   Serial.println(val);
   Serial.println("-----------------");
  }
  delay(20);
}
