#include "Buzzer.hpp"

Buzzer::Buzzer(int pin, int base_frequency, int led_pin)
{
    this->pin = pin;
    this->frequency = base_frequency;
    this->led_pin = led_pin;
}

void Buzzer::setup()
{
    pinMode(this->pin, OUTPUT);
    pinMode(this->led_pin, OUTPUT);
}

void Buzzer::bip(int note)
{
    if(note == 0)
    {
        note = this->frequency;
    }


    tone(this->pin, note);
    digitalWrite(this->led_pin, HIGH);
    delay(50);
    digitalWrite(this->led_pin, LOW);
    noTone(this->pin);
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