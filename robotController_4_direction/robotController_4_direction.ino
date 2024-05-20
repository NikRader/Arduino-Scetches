
/*
Remote control file for serpentine motion
of a snake robot with 10 servos
*/

#include <driver/adc.h>
#include <ESP32Servo.h>
#include "BluetoothSerial.h"  //Header File for Serial Bluetooth, will be added by default into Arduino
BluetoothSerial SerialBT;     //Object for Bluetooth


// The potentiometer is connected to GPIO36 (Pin VP)
const int batPin = 36;
const int LED = 2;
// Potentiometer value
int batValue = 0;
int oldbatValue = 0;
int count = 1;
// Define servo objects for the snake segments
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

// CONSTANTS
int counter = 0;        // Loop counter variable
float lag = .5712;      // Phase lag between segments
int frequency = 1;      // Oscillation frequency of segments.
int amplitude = 45;     // Amplitude of the serpentine motion of the snake
int rightOffset = 0;    // Right turn offset
int leftOffset = 0;   // Left turn offset
int offset = 6;         // Variable to correct servos that are not exactly centered
int delayTime = 4;      // Delay between limb movements
int startPause = 1500;  // Delay time to position robot
int test = -3;          // Test varialble takes values from -6 to +5


void setup() {

  //pinMode(batPin,INPUT_PULLUP);
  Serial.begin(9600);        //Start Serial monitor in 9600
  Serial.setTimeout(100);    // Прием сообщения за 100 мс
  SerialBT.setTimeout(100);  // Прием сообщения за 100 мс
  SerialBT.begin("ESP_32");  //Name of your Bluetooth Signal
  Serial.println("Bluetooth Device is Ready to Pair");
  pinMode(LED, OUTPUT);
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
  oldbatValue = adc1_get_raw(ADC1_CHANNEL_0);
  // Attach segments to pins
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

  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);

  delay(startPause);  // Pause to position robot
  digitalWrite(LED, HIGH);
  delay(200);
  digitalWrite(LED, LOW);
  delay(200);
  digitalWrite(LED, HIGH);
  delay(200);
  digitalWrite(LED, LOW);
  delay(200);
  digitalWrite(LED, HIGH);
  delay(200);
  digitalWrite(LED, LOW);
}

void loop() {
  delay(20);

  count = 1;
  digitalWrite(LED, HIGH);
  delay(20);
  digitalWrite(LED, LOW);

  if (Serial.available()) {
    SerialBT.print(Serial.readString());
  }
  // Сообщение на esp от Android
  if (SerialBT.available() > 1) {
    char com = SerialBT.read();
    int val = SerialBT.parseInt();

    if (com == 'i') {
      setStartPosition();
    }
    if (com == 'p') {
      // To Do PAUSE!!!
    }
    // Forward motion
    if (com == 'f') {
      forwardMove();
    }
    // Reverse motion
    if (com == 'b') {
      reverseMove();
    }

    // Right turn
    if (com == 'r') {
      rightMove();
    }

    if (com == 'l') {
      leftMove();
    }

    // Left turn
    if (com == 'l') {
      leftMove();
    }
    if (com == 'A') {
      amplitude = val;
    }
    if (com == 'D') {
      delayTime = val;
    }
    if (com == 'R') {
      rightOffset = val;
    }
    if (com == 'L') {
      leftOffset = val;
    }
  }
}
void setStartPosition() {
  s1.write(90 + offset + amplitude * cos(5 * lag));
  s2.write(90 + offset + amplitude * cos(4 * lag));
  s3.write(90 + offset + amplitude * cos(3 * lag));
  s4.write(90 + amplitude * cos(2 * lag));
  s5.write(90 + amplitude * cos(1 * lag));
  s6.write(90 + amplitude * cos(0 * lag));
  s7.write(90 + amplitude * cos(-1 * lag));
  s8.write(90 + amplitude * cos(-2 * lag));
  s9.write(90 + amplitude * cos(-3 * lag));
  s10.write(90 + amplitude * cos(-4 * lag));
}
void forwardMove() {
  for (counter = 0; counter < 360; counter += 1) {
    delay(delayTime);
    s1.write(90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    s2.write(90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    s3.write(90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    s4.write(90 + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    s5.write(90 + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    s6.write(90 + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    s7.write(90 + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    s8.write(90 + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    s9.write(90 + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    s10.write(90 + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
  }
}
void reverseMove() {
  for (counter = 360; counter > 0; counter -= 1) {
    delay(delayTime);
    s1.write(90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    s2.write(90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    s3.write(90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    s4.write(90 + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    s5.write(90 + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    s6.write(90 + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    s7.write(90 + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    s8.write(90 + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    s9.write(90 + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    s10.write(90 + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
  }
}
void rightMove() {
  // Ramp up turn offset
  for (counter = 0; counter < 10; counter += 1) {
    delay(delayTime);
    s1.write(90 + offset + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    s2.write(90 + offset + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    s3.write(90 + offset + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    s4.write(90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    s5.write(90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    s6.write(90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    s7.write(90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    s8.write(90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    s9.write(90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    s10.write(90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
  }
  // Continue right turn
  for (counter = 11; counter < 350; counter += 1) {
    delay(delayTime);
    s1.write(90 + offset + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    s2.write(90 + offset + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    s3.write(90 + offset + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    s4.write(90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    s5.write(90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    s6.write(90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    s7.write(90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    s8.write(90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    s9.write(90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    s10.write(90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
  }
  // Ramp down turn offset
  for (counter = 350; counter < 360; counter += 1) {
    delay(delayTime);
    s1.write(90 + offset + .1 * (360 - counter) * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    s2.write(90 + offset + .1 * (360 - counter) * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    s3.write(90 + offset + .1 * (360 - counter) * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    s4.write(90 + .1 * (360 - counter) * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    s5.write(90 + .1 * (360 - counter) * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    s6.write(90 + .1 * (360 - counter) * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    s7.write(90 + .1 * (360 - counter) * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    s8.write(90 + .1 * (360 - counter) * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    s9.write(90 + .1 * (360 - counter) * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    s10.write(90 + .1 * (360 - counter) * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
  }
}
void leftMove() {
  // Ramp up turn offset
  for (counter = 0; counter < 10; counter += 1) {
    delay(delayTime);
    s1.write(90 + offset + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    s2.write(90 + offset + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    s3.write(90 + offset + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    s4.write(90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    s5.write(90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    s6.write(90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    s7.write(90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    s8.write(90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    s9.write(90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    s10.write(90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
  }
  // Continue left turn
  for (counter = 11; counter < 350; counter += 1) {
    delay(delayTime);
    s1.write(90 + offset + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    s2.write(90 + offset + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    s3.write(90 + offset + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    s4.write(90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    s5.write(90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    s6.write(90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    s7.write(90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    s8.write(90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    s9.write(90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    s10.write(90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
  }
  // Ramp down turn offset
  for (counter = 350; counter < 360; counter += 1) {
    delay(delayTime);
    s1.write(90 + offset + .1 * (360 - counter) * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    s2.write(90 + offset + .1 * (360 - counter) * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    s3.write(90 + offset + .1 * (360 - counter) * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    s4.write(90 + .1 * (360 - counter) * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    s5.write(90 + .1 * (360 - counter) * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    s6.write(90 + .1 * (360 - counter) * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    s7.write(90 + .1 * (360 - counter) * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    s8.write(90 + .1 * (360 - counter) * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    s9.write(90 + .1 * (360 - counter) * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    s10.write(90 + .1 * (360 - counter) * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
  }
}
