/*
Remote control file for serpentine motion
of a snake robot with 12 servos
*/
//#include "esp_adc_cal.h"
#include <driver/adc.h>
#include <ESP32Servo.h>
#include "BluetoothSerial.h" //Header File for Serial Bluetooth, will be added by default into Arduino
BluetoothSerial ESP_BT; //Object for Bluetooth
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


void setup() {
// Set movement pins as inputs
  pinMode(forwardPin, INPUT);
  pinMode(reversePin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(leftPin, INPUT);

// Set movement pins to low
  digitalWrite(forwardPin, LOW);
  digitalWrite(reversePin, LOW);
  digitalWrite(rightPin, LOW);
  digitalWrite(leftPin, LOW);

  //pinMode(batPin,INPUT_PULLUP);
  Serial.begin(9600); //Start Serial monitor in 9600
  ESP_BT.begin("ESP32_snake_Control"); //Name of your Bluetooth Signal
  Serial.println("Bluetooth Device is Ready to Pair");
  pinMode(LED, OUTPUT);
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_11);
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
// Put snake in starting position
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


void loop()
{
  delay(20);
// Measures the value of the potentiometer
  batValue = adc1_get_raw(ADC1_CHANNEL_0);
  if(count == 20 || forwardVal){
    
    Serial.println((oldbatValue*3.75/4096)*(11943+2344)/2344);
    //Serial.println(oldbatValue*3.75/4096);
    //Serial.println(oldbatValue);
    Serial.println();
    ESP_BT.println((oldbatValue*3.75/4096)*(11943+2344)/2344);
    //ESP_BT.println(oldbatValue*3.75/4096);
    //ESP_BT.println(oldbatValue);
    ESP_BT.println();
    count = 1;
    digitalWrite(LED, HIGH);
    delay(20);
    digitalWrite(LED, LOW);
      }
  
  else{
    count++;
    oldbatValue = (10*oldbatValue + batValue)/11;
    
     }
//----------------------------------------------------------------------------
      if (Serial.available()) {
     SerialBT.print(Serial.read());
  }

  // Сообщение на esp
  if (SerialBT.available()) {
    char command = SerialBT.read();
    if (command == '2'){
     Serial.println("2");
    }
    
    if(command == '4'){
     Serial.println("4");
     
    }
    if(command == '6'){
     Serial.println("6");
    }
    
    if(command == '8'){
     Serial.print("8");
    }
  }
    

//  Read movement pins
  // forwardVal = digitalRead(forwardPin);
  // reverseVal = digitalRead(reversePin);
  // rightVal = digitalRead(rightPin);
  // leftVal = digitalRead(leftPin);
Forward motion
  if (forwardVal == HIGH){
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
//   }
// // Reverse motion
//   if (reverseVal == HIGH){
//     for(counter = 360; counter > 0; counter -= 1)  {
//       delay(delayTime);
//       s1.write(90+offset+amplitude*cos(frequency*counter*3.14159/180+5*lag));
//       s2.write(90+offset+amplitude*cos(frequency*counter*3.14159/180+4*lag));
//       s3.write(90+offset+amplitude*cos(frequency*counter*3.14159/180+3*lag));
//       s4.write(90+amplitude*cos(frequency*counter*3.14159/180+2*lag));
//       s5.write(90+amplitude*cos(frequency*counter*3.14159/180+1*lag));
//       s6.write(90+amplitude*cos(frequency*counter*3.14159/180+0*lag));
//       s7.write(90+amplitude*cos(frequency*counter*3.14159/180-1*lag));
//       s8.write(90+amplitude*cos(frequency*counter*3.14159/180-2*lag));
//       s9.write(90+amplitude*cos(frequency*counter*3.14159/180-3*lag));
//       s10.write(90+amplitude*cos(frequency*counter*3.14159/180-4*lag));
//     }
//   }

// // Right turn
//   if (rightVal == HIGH){
// // Ramp up turn offset
//     for(counter = 0; counter < 10; counter += 1)  {
//       delay(delayTime);
//       s1.write(90+offset+.1*counter*rightOffset+amplitude*cos(frequency*counter*3.14159/180+5*lag));
//       s2.write(90+offset+.1*counter*rightOffset+amplitude*cos(frequency*counter*3.14159/180+4*lag));
//       s3.write(90+offset+.1*counter*rightOffset+amplitude*cos(frequency*counter*3.14159/180+3*lag));
//       s4.write(90+.1*counter*rightOffset+amplitude*cos(frequency*counter*3.14159/180+2*lag));
//       s5.write(90+.1*counter*rightOffset+amplitude*cos(frequency*counter*3.14159/180+1*lag));
//       s6.write(90+.1*counter*rightOffset+amplitude*cos(frequency*counter*3.14159/180+0*lag));
//       s7.write(90+.1*counter*rightOffset+amplitude*cos(frequency*counter*3.14159/180-1*lag));
//       s8.write(90+.1*counter*rightOffset+amplitude*cos(frequency*counter*3.14159/180-2*lag));
//       s9.write(90+.1*counter*rightOffset+amplitude*cos(frequency*counter*3.14159/180-3*lag));
//       s10.write(90+.1*counter*rightOffset+amplitude*cos(frequency*counter*3.14159/180-4*lag));
//     }
// // Continue right turn
//     for(counter = 11; counter < 350; counter += 1)  {
//       delay(delayTime);
//       s1.write(90+offset+rightOffset+amplitude*cos(frequency*counter*3.14159/180+5*lag));
//       s2.write(90+offset+rightOffset+amplitude*cos(frequency*counter*3.14159/180+4*lag));
//       s3.write(90+offset+rightOffset+amplitude*cos(frequency*counter*3.14159/180+3*lag));
//       s4.write(90+rightOffset+amplitude*cos(frequency*counter*3.14159/180+2*lag));
//       s5.write(90+rightOffset+amplitude*cos(frequency*counter*3.14159/180+1*lag));
//       s6.write(90+rightOffset+amplitude*cos(frequency*counter*3.14159/180+0*lag));
//       s7.write(90+rightOffset+amplitude*cos(frequency*counter*3.14159/180-1*lag));
//       s8.write(90+rightOffset+amplitude*cos(frequency*counter*3.14159/180-2*lag));
//       s9.write(90+rightOffset+amplitude*cos(frequency*counter*3.14159/180-3*lag));
//       s10.write(90+rightOffset+amplitude*cos(frequency*counter*3.14159/180-4*lag));
//     }
// // Ramp down turn offset
//     for(counter = 350; counter < 360; counter += 1)  {
//       delay(delayTime);
//       s1.write(90+offset+.1*(360-counter)*rightOffset+amplitude*cos(frequency*counter*3.14159/180+5*lag));
//       s2.write(90+offset+.1*(360-counter)*rightOffset+amplitude*cos(frequency*counter*3.14159/180+4*lag));
//       s3.write(90+offset+.1*(360-counter)*rightOffset+amplitude*cos(frequency*counter*3.14159/180+3*lag));
//       s4.write(90+.1*(360-counter)*rightOffset+amplitude*cos(frequency*counter*3.14159/180+2*lag));
//       s5.write(90+.1*(360-counter)*rightOffset+amplitude*cos(frequency*counter*3.14159/180+1*lag));
//       s6.write(90+.1*(360-counter)*rightOffset+amplitude*cos(frequency*counter*3.14159/180+0*lag));
//       s7.write(90+.1*(360-counter)*rightOffset+amplitude*cos(frequency*counter*3.14159/180-1*lag));
//       s8.write(90+.1*(360-counter)*rightOffset+amplitude*cos(frequency*counter*3.14159/180-2*lag));
//       s9.write(90+.1*(360-counter)*rightOffset+amplitude*cos(frequency*counter*3.14159/180-3*lag));
//       s10.write(90+.1*(360-counter)*rightOffset+amplitude*cos(frequency*counter*3.14159/180-4*lag));
//     }
//   }

// // Left turn
//   if (leftVal == HIGH){
// // Ramp up turn offset
//     for(counter = 0; counter < 10; counter += 1)  {
//       delay(delayTime);
//       s1.write(90+offset+.1*counter*leftOffset+amplitude*cos(frequency*counter*3.14159/180+5*lag));
//       s2.write(90+offset+.1*counter*leftOffset+amplitude*cos(frequency*counter*3.14159/180+4*lag));
//       s3.write(90+offset+.1*counter*leftOffset+amplitude*cos(frequency*counter*3.14159/180+3*lag));
//       s4.write(90+.1*counter*leftOffset+amplitude*cos(frequency*counter*3.14159/180+2*lag));
//       s5.write(90+.1*counter*leftOffset+amplitude*cos(frequency*counter*3.14159/180+1*lag));
//       s6.write(90+.1*counter*leftOffset+amplitude*cos(frequency*counter*3.14159/180+0*lag));
//       s7.write(90+.1*counter*leftOffset+amplitude*cos(frequency*counter*3.14159/180-1*lag));
//       s8.write(90+.1*counter*leftOffset+amplitude*cos(frequency*counter*3.14159/180-2*lag));
//       s9.write(90+.1*counter*leftOffset+amplitude*cos(frequency*counter*3.14159/180-3*lag));
//       s10.write(90+.1*counter*leftOffset+amplitude*cos(frequency*counter*3.14159/180-4*lag));
//     }
// // Continue left turn
//     for(counter = 11; counter < 350; counter += 1)  {
//       delay(delayTime);
//       s1.write(90+offset+leftOffset+amplitude*cos(frequency*counter*3.14159/180+5*lag));
//       s2.write(90+offset+leftOffset+amplitude*cos(frequency*counter*3.14159/180+4*lag));
//       s3.write(90+offset+leftOffset+amplitude*cos(frequency*counter*3.14159/180+3*lag));
//       s4.write(90+leftOffset+amplitude*cos(frequency*counter*3.14159/180+2*lag));
//       s5.write(90+leftOffset+amplitude*cos(frequency*counter*3.14159/180+1*lag));
//       s6.write(90+leftOffset+amplitude*cos(frequency*counter*3.14159/180+0*lag));
//       s7.write(90+leftOffset+amplitude*cos(frequency*counter*3.14159/180-1*lag));
//       s8.write(90+leftOffset+amplitude*cos(frequency*counter*3.14159/180-2*lag));
//       s9.write(90+leftOffset+amplitude*cos(frequency*counter*3.14159/180-3*lag));
//       s10.write(90+leftOffset+amplitude*cos(frequency*counter*3.14159/180-4*lag));
//     }
// // Ramp down turn offset
//     for(counter = 350; counter < 360; counter += 1)  {
//       delay(delayTime);
//       s1.write(90+offset+.1*(360-counter)*leftOffset+amplitude*cos(frequency*counter*3.14159/180+5*lag));
//       s2.write(90+offset+.1*(360-counter)*leftOffset+amplitude*cos(frequency*counter*3.14159/180+4*lag));
//       s3.write(90+offset+.1*(360-counter)*leftOffset+amplitude*cos(frequency*counter*3.14159/180+3*lag));
//       s4.write(90+.1*(360-counter)*leftOffset+amplitude*cos(frequency*counter*3.14159/180+2*lag));
//       s5.write(90+.1*(360-counter)*leftOffset+amplitude*cos(frequency*counter*3.14159/180+1*lag));
//       s6.write(90+.1*(360-counter)*leftOffset+amplitude*cos(frequency*counter*3.14159/180+0*lag));
//       s7.write(90+.1*(360-counter)*leftOffset+amplitude*cos(frequency*counter*3.14159/180-1*lag));
//       s8.write(90+.1*(360-counter)*leftOffset+amplitude*cos(frequency*counter*3.14159/180-2*lag));
//       s9.write(90+.1*(360-counter)*leftOffset+amplitude*cos(frequency*counter*3.14159/180-3*lag));
//       s10.write(90+.1*(360-counter)*leftOffset+amplitude*cos(frequency*counter*3.14159/180-4*lag));
//     }
//   }
}