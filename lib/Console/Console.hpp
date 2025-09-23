#ifndef CONSOLE_H

#define CONSOLE_H
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include "Logs.hpp"

#define EMPTY_CHAR '\0'

class Console
{
    public:
        Console();
        
        void run();

        char getKey();

        void bip(int frequency = 1000);

        void turnOnBacklight();
        void turnOffBacklight();
        
    private:
        LiquidCrystal_I2C display;
        Keypad keypad;

        bool blacklight_state;
        int current_window;
        int buzzer_tone = 1000;
        int buzzer_pin = 12;

        char password[5];

        void startMenu();
        void runLoginWindow();
        void setupLimit();
        void returnToStartMenu();

        void clearLCD();

        void goodBip();
        void badBip();

};

#endif