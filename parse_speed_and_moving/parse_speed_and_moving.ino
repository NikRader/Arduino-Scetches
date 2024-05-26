#include <Servo.h>
#include "stdlib.h"
unsigned long startTime = millis();
unsigned long currentTime;
const int numServos = 10;

Servo servos[numServos];  //create 10 servos
int pos, i;

// CONSTANTS
int counter = 0;        // Loop counter variable
float lag = .5712;      // Phase lag between segments
int frequency = 1;      // Oscillation frequency of segments.
int amplitude = 45;     // Amplitude of the serpentine motion of the snake
int rightOffset = 0;    // Right turn offset
int leftOffset = 0;     // Left turn offset
int offset = 6;         // Variable to correct servos that are not exactly centered
int delayTime = 4;      // Delay between limb movements
int startPause = 1500;  // Delay time to position robot
int test = -3;          // Test varialble takes values from -6 to +5

void setup() {
  Serial.begin(9600);
  servos[0].attach(32);
  servos[1].attach(33);
  servos[2].attach(25);
  servos[3].attach(26);
  servos[4].attach(23);
  servos[5].attach(22);
  servos[6].attach(21);
  servos[7].attach(19);
  servos[8].attach(18);
  servos[9].attach(5);
  //s1.attach(7);
}

void loop() {
  forwardMove();
  delay(20);
}

void forwardMove() {
  startTime = millis();
  for (counter = 0; counter < 360; counter += 1) {
    delay(delayTime);
    
    servos[0].write(90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    servos[1].write(90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    servos[2].write(90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    servos[3].write(90 + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    servos[4].write(90 + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    servos[5].write(90 + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    servos[6].write(90 + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    servos[7].write(90 + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    servos[8].write(90 + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    servos[9].write(90 + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));

    String res = "I ";
    String iter_num = int_to_string(counter);
    res+= iter_num;
    res+=" :";
    if (counter < 100) {
      for (int j = 0; j < 10; j++) {
        res += add_servo_inf(j);
      }
      res += ";";
      Serial.println(res);
    }
    else{break;}
  }
}
// Парсинг int в string
String int_to_string(int number) {
  char charArray[10];                // Создаем символьный массив для хранения значения типа int
  sprintf(charArray, "%d", number);  // Преобразуем int в строку
  String res = String(charArray);    // Создаем объект String из символьного массива
  return res;
}
// Запись номера, времени, положения в одну строку
String add_string(String num, String time, String state) {
  String res = "";
  res += num;
  res += " ";
  res += time;
  res += " ";
  res += state;
  res += ",";
  return res;
}

String add_servo_inf(int i) {
  String res = "";
  // Вычисление номера серво, времени и положения
  int intValue = i + 1;
  int cur_t = millis() - startTime;
  int cur_x = servos[i].read();
  // Запись в строку
  String str_num = int_to_string(intValue);
  String str_cur_t = int_to_string(cur_t);
  String str_cur_x = int_to_string(cur_x);
  // Сложение строк
  String data_group = add_string(str_num, str_cur_t, str_cur_x);
  res += data_group;
  return res;
}
