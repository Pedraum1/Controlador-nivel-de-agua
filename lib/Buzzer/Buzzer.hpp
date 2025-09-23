#ifndef BUZZER_H

#define BUZZER_H

#include "Arduino.h"

class Buzzer
{
    public:
        Buzzer(int pin, int base_frequency);
        void bip(int note = 0);
        void goodBip(int note = 0);
        void badBip(int note = 0);
    
    private:
        int pin;
        int frequency;

};

#endif