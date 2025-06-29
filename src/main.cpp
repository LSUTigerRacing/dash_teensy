#include <Arduino.h>
#include <FlexCAN_T4.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1; //RX PIN 23, TX PIN 22


void ReceiveHandler(const CAN_message_t &msg) {
  Serial.print("Received: ID=0x");
  Serial.print(msg.id, HEX);
  Serial.print(" Len:" );
  Serial.print(msg.len);
  Serial.print(" Data: ");
  for (uint8_t i = 0; i < msg.len; i++) {
    Serial.printf("%02X ", msg.buf[i]);
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  can1.begin();
  can1.setBaudRate(500000);  // 500 kbps
  can1.enableMBInterrupts();
  can1.setMBFilter(REJECT_ALL); // Set default filter to reject all
  can1.setMBFilter(MB0, 0x123);
  can1.onReceive(MB0, ReceiveHandler);

  Serial.println("CAN1 Listening...");
}



void loop() {
  can1.events();


}
