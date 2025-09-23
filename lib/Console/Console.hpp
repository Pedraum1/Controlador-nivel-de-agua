#ifndef CONSOLE_H

#define CONSOLE_H
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include "Buzzer.hpp"

#include "Logs.hpp"

#define EMPTY_CHAR '\0'

class Console
{
    public:
        Console();
        
        void run();
        void setup();

        char getKey();

        void bip();

        void turnOnBacklight();
        void turnOffBacklight();
        
    private:
        LiquidCrystal_I2C display;
        Keypad keypad;
        Buzzer buzzer;
        

        bool blacklight_state = true;
        int current_window = 0;

        char password[5];

        void startMenu();
        void runLoginWindow();
        void setupLimit();
        void returnToStartMenu();

        void clearLCD();

};

#endif