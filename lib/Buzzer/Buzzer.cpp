#include "Buzzer.hpp"

Buzzer::Buzzer(int pin, int base_frequency)
{
    this->pin = pin;
    this->frequency = base_frequency;
}

void Buzzer::bip(int note)
{
    if(note == 0)
    {
        note = this->frequency;
    }


    tone(this->pin, note, 50);
    delay(50);
}

void Buzzer::goodBip(int note)
{
    if(note == 0)
    {
        note = this->frequency;
    }

    bip(note);
    bip(2*note);
    bip(2.5*note);
}

void Buzzer::badBip(int note)
{
    if(note == 0)
    {
        note = this->frequency;
    }

    bip(2*note);
    bip(note);
}