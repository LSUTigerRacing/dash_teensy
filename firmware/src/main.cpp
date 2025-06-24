#include <Arduino.h>
#include <FlexCAN_T4.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1; //RX PIN 23, TX PIN 22


void setup() {
    Serial.begin(115200);
    can1.begin(); // starts can1 controller
    can1.setBaudRate(500000);  // 500 kbps
    Serial.println("CAN1 Listening...");
}

void ReceiveHandler() {
    CAN_message_t msg;
    if (can1.reads(msg)) {
        Serial.print("Received: ID=0x");
        Serial.print(msg.id, HEX);
        Serial.print(" Data: ");
        for (uint8_t i = 0; i < msg.len; i++) {
            Serial.printf("%02X ", msg.buf[i]);
        }
        Serial.println();
    }
}

void loop() {
    ReceiveHandler();


}
