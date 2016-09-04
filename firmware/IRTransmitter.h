
#ifndef IRTransmitter_h
#define IRTransmitter_h

#include <stddef.h>

class IRTransmitter
{
    public:
        IRTransmitter(uint8_t ir_output_pin, uint8_t led_pin);
        void Transmit(unsigned int *data, size_t length, uint32_t wait = 5000);

    private:
        int ir_output_pin_;
        int led_pin_;
        unsigned long sig_time_;

        const static int duty_cycle;
        const static int carrier_frequency;
        const static int period;
        const static int high_time;
        const static int low_time;

        void Mark(unsigned int mLen);
        void Space(unsigned int sLen);
};

#endif /* IRTransmitter_h */
