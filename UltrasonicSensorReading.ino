#include <Arduino.h>

HardwareSerial SensorSerial(1); // UART1
uint8_t frame[4];

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("A01NYUB Test on UART1");

  SensorSerial.begin(9600, SERIAL_8N1, 4, 5); // RX, TX (TX unused)
  Serial.println("Listening on UART1...");
}

void loop() {
  while (SensorSerial.available() >= 4) {
    if (SensorSerial.read() == 0xFF) {
      frame[0] = 0xFF;
      frame[1] = SensorSerial.read();
      frame[2] = SensorSerial.read();
      frame[3] = SensorSerial.read();

      uint8_t checksum = (frame[0] + frame[1] + frame[2]) & 0xFF;
      if (checksum == frame[3]) {
        int distance_mm = (frame[1] << 8) | frame[2];
        Serial.printf("Distance: %d mm\n", distance_mm);
      } else {
        Serial.println("Checksum error");
      }
    }
  }
}
