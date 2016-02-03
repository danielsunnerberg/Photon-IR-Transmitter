#include <IRTransmitter/IRTransmitter.h>

#define IR_PIN D6
#define LED_PIN D7

void setup() {
}

// Raw data can be sniffed using an IR-receiver and e.g. https://github.com/z3t0/Arduino-IRremote/blob/master/examples/IRrecvDumpV2/IRrecvDumpV2.ino
unsigned int data[67] = {9000, 4450, 550, 550, 600, 500, 600, 550, 550, 1650, 600, 550, 550, 550, 600, 500, 600, 550,
                            600, 1600, 600, 1650, 600, 1650, 600, 500, 600, 1650, 600, 1600, 600, 1650, 600, 1650, 600,
                            500, 600, 1650, 600, 1650, 550, 550, 600, 1650, 550, 550, 600, 500, 600, 550, 550, 1650,
                            600, 550, 550, 550, 600, 1650, 550, 550, 600, 1650, 550, 1650, 650, 1600,
                            600};  // NEC 10EF6897

IRTransmitter transmitter(IR_PIN, LED_PIN);
void loop() {
    transmitter.Transmit(data, sizeof(data) / sizeof(data[0]));
}
