#ifndef CONSOLE_H

#define CONSOLE_H
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include "Buzzer.hpp"

#include "Logs.hpp"

#define EMPTY_CHAR '\0'

enum Menus {
    Login,
    Main,
    Setup,
    ManualControl
};

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

        char password[4];

        void runLoginWindow();
        void runStartMenu();
        void runSetupMenu();
        void runManualControlMenu();
        void returnToStartMenu();

        bool menuOptionDetected(char key_pressed);
        void routeToMenu(char option);

        void copyPasswordToObject(char password[4]);

        void clearLCD();

};

#endif