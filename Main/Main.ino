
#include <Servo.h>
Servo servo;

// Начальные параметры
void setup() {
// Привязали сервопривод к порту 10
  servo.attach(10);
  Serial.begin(9600);
 
}

// Цикл программы
void loop() {

 servo.write(0); 
 Serial.println("Turned on 0"); 
 delay(2000); // 

 servo.write(90); 
 Serial.println("Turned on 90"); 
 delay(2000); // 
 
 servo.write(180); 
 Serial.println("Turned on 180"); 

 delay(2000); // 
}

