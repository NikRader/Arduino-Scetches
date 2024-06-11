#include <driver/adc.h>
#include <ESP32Servo.h>
#include "BluetoothSerial.h"  //Header File for Serial Bluetooth, will be added by default into Arduino
BluetoothSerial SerialBT;     //Object for Bluetooth
unsigned long startTime = millis();
unsigned long currentTime;
const int numServos = 10;
// The potentiometer is connected to GPIO36 (Pin VP)
const int batPin = 36;
const int LED = 2;
// Potentiometer value
int batValue = 0;
int oldbatValue = 0;
int count = 1;
// Define servo objects for the snake segments
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

  //pinMode(batPin,INPUT_PULLUP);
  Serial.begin(9600);        //Start Serial monitor in 9600
                             // SerialBT.begin(9600);
  Serial.setTimeout(100);    // Прием сообщения за 100 мс
  SerialBT.setTimeout(100);  // Прием сообщения за 100 мс
  SerialBT.begin("ESP_32");  //Name of your Bluetooth Signal
  Serial.println("Bluetooth Device is Ready to Pair");
  pinMode(LED, OUTPUT);
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
  oldbatValue = adc1_get_raw(ADC1_CHANNEL_0);
  // Attach segments to pins
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
  // Measures the value of the potentiometer

  batValue = adc1_get_raw(ADC1_CHANNEL_0);
  if (count == 200) {
    int bat_send = 100 * (oldbatValue * 3.75 / 4096) * (11943 + 2344) / 2344;

    char charArray[10];                  // Создаем символьный массив для хранения значения типа int
    sprintf(charArray, "%d", bat_send);  // Преобразуем int в строку
    String res = String(charArray);      // Создаем объект String из символьного массива
                                         // SerialBT.println(res);
    Serial.println(res);
    SerialBT.println(res);
    count = 1;
    digitalWrite(LED, HIGH);
    delay(20);
    digitalWrite(LED, LOW);
  } else {
    count++;
    oldbatValue = (10 * oldbatValue + batValue) / 11;
  }
  // yield();

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
  servos[0].write(90 + offset + amplitude * cos(5 * lag));
  servos[1].write(90 + offset + amplitude * cos(4 * lag));
  servos[2].write(90 + offset + amplitude * cos(3 * lag));
  servos[3].write(90 + amplitude * cos(2 * lag));
  servos[4].write(90 + amplitude * cos(1 * lag));
  servos[5].write(90 + amplitude * cos(0 * lag));
  servos[6].write(90 + amplitude * cos(-1 * lag));
  servos[7].write(90 + amplitude * cos(-2 * lag));
  servos[8].write(90 + amplitude * cos(-3 * lag));
  servos[9].write(90 + amplitude * cos(-4 * lag));
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
    // String send = "I";
    // String iter_num = int_to_string(counter);
    // send += iter_num;
    // send += ":";
    // if (counter < 360) {
    //   for (int j = 0; j < 10; j++) {
    //     send += add_servo_inf(j);
    //   }
    //   SerialBT.println(send);
    //   Serial.println(send);
      
    // } else {
    //   break;
    // }
  }
}
void reverseMove() {
  for (counter = 360; counter > 0; counter -= 1) {
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
  }
}
void rightMove() {
  // Ramp up turn offset
  for (counter = 0; counter < 10; counter += 1) {
    delay(delayTime);
    servos[0].write(90 + offset + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    servos[1].write(90 + offset + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    servos[2].write(90 + offset + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    servos[3].write(90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    servos[4].write(90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    servos[5].write(90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    servos[6].write(90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    servos[7].write(90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    servos[8].write(90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    servos[9].write(90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
  }
  // Continue right turn
  for (counter = 11; counter < 350; counter += 1) {
    delay(delayTime);
    servos[0].write(90 + offset + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    servos[1].write(90 + offset + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    servos[2].write(90 + offset + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    servos[3].write(90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    servos[4].write(90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    servos[5].write(90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    servos[6].write(90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    servos[7].write(90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    servos[8].write(90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    servos[9].write(90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
  }
  // Ramp down turn offset
  for (counter = 350; counter < 360; counter += 1) {
    delay(delayTime);
    servos[0].write(90 + offset + .1 * (360 - counter) * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    servos[1].write(90 + offset + .1 * (360 - counter) * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    servos[2].write(90 + offset + .1 * (360 - counter) * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    servos[3].write(90 + .1 * (360 - counter) * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    servos[4].write(90 + .1 * (360 - counter) * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    servos[5].write(90 + .1 * (360 - counter) * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    servos[6].write(90 + .1 * (360 - counter) * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    servos[7].write(90 + .1 * (360 - counter) * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    servos[8].write(90 + .1 * (360 - counter) * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    servos[9].write(90 + .1 * (360 - counter) * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
  }
}
void leftMove() {
  // Ramp up turn offset
  for (counter = 0; counter < 10; counter += 1) {
    delay(delayTime);
    servos[0].write(90 + offset + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    servos[1].write(90 + offset + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    servos[2].write(90 + offset + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    servos[3].write(90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    servos[4].write(90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    servos[5].write(90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    servos[6].write(90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    servos[7].write(90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    servos[8].write(90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    servos[9].write(90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
  }
  // Continue left turn
  for (counter = 11; counter < 350; counter += 1) {
    delay(delayTime);
    servos[0].write(90 + offset + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    servos[1].write(90 + offset + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    servos[2].write(90 + offset + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    servos[3].write(90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    servos[4].write(90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    servos[5].write(90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    servos[6].write(90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    servos[7].write(90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    servos[8].write(90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    servos[9].write(90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
  }
  // Ramp down turn offset
  for (counter = 350; counter < 360; counter += 1) {
    delay(delayTime);
    servos[0].write(90 + offset + .1 * (360 - counter) * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    servos[1].write(90 + offset + .1 * (360 - counter) * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    servos[2].write(90 + offset + .1 * (360 - counter) * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    servos[3].write(90 + .1 * (360 - counter) * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    servos[4].write(90 + .1 * (360 - counter) * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    servos[5].write(90 + .1 * (360 - counter) * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    servos[6].write(90 + .1 * (360 - counter) * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    servos[7].write(90 + .1 * (360 - counter) * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    servos[8].write(90 + .1 * (360 - counter) * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    servos[9].write(90 + .1 * (360 - counter) * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
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
  res += ")";
  res += time;
  res += ",";
  res += state;
  res += ";";
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
