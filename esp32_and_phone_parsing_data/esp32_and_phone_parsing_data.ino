#include "BluetoothSerial.h"  
BluetoothSerial SerialBT;     

void setup() {
  Serial.begin(9600);        
  Serial.setTimeout(100);    
  SerialBT.setTimeout(100);  
  SerialBT.begin("ESP_32");  
}

void loop() {
  // Cообщение от esp32
  if (Serial.available()) {
    SerialBT.print(Serial.readString());
  }
  // Сообщение на esp от Android
  if (SerialBT.available() > 1) {
    char com = SerialBT.read();
    int val = SerialBT.parseInt();
    if (com == 'A') {
      amplitude = val;
    }
  }
}
