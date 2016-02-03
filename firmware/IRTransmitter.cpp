#include "application.h"
#include "IRTransmitter.h"

const int IRTransmitter::duty_cycle = 50;
const int IRTransmitter::carrier_frequency = 38000;
const int IRTransmitter::period = (1000000 + carrier_frequency / 2) / carrier_frequency;
const int IRTransmitter::high_time = period * duty_cycle / 100;
const int IRTransmitter::low_time = period - high_time;

IRTransmitter::IRTransmitter(unsigned int ir_output_pin, unsigned int led_pin) {
    ir_output_pin_ = ir_output_pin;
    led_pin_ = led_pin;

    pinMode(led_pin_, OUTPUT);
    pinMode(ir_output_pin_, OUTPUT);

    sig_time_ = 0;
}

void IRTransmitter::Mark(unsigned int mLen) {
    sig_time_ += mLen; // mark ends at new sigTime
    unsigned long now = micros();
    unsigned long dur = sig_time_ - now; // allows for rolling time adjustment due to code execution delays
    if (dur == 0) return;

    while ((micros() - now) < dur) { // just wait here until time is up
        digitalWrite(ir_output_pin_, HIGH);
        delayMicroseconds(high_time - 3);
        digitalWrite(ir_output_pin_, LOW);
        delayMicroseconds(low_time - 4);
    }
}

void IRTransmitter::Space(unsigned int sLen) {
    sig_time_ += sLen; //space ends at new sigTime
    unsigned long now = micros();
    unsigned long dur = sig_time_ - now; // allows for rolling time adjustment due to code execution delays
    if (dur == 0) return;
    while ((micros() - now) < dur); // just wait here until time is up
}

void IRTransmitter::Transmit(unsigned int *data, size_t length) {
    // First send the NEC RAW signal
    digitalWrite(led_pin_, HIGH);
    sig_time_ = micros(); // keeps rolling track of signal time to avoid impact of loop & code execution delays
    for (int i = 0; i < length; i++) {
        Mark(data[i++]); // also move pointer to next position
        if (i < length) Space(data[i]); // pointer will be moved by for loop
    }
    digitalWrite(led_pin_, LOW);
    delay(5000); //wait 5 seconds between each signal (change to suit)
}
