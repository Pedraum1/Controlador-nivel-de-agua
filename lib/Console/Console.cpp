#include "Console.hpp"

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

//=================CONSOLE GENERALS==========================

Console::Console()
    : display(0x27, 16, 2),
      keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS)
{
    this->current_window = 0;
}

void Console::run()
{
    switch(this->current_window)
    {
        case 0:
            this->runLoginWindow();
        break;

        default:
            this->returnToStartMenu();
        break;
    }
}

//=================WINDOWS======================

void Console::runLoginWindow()
{
    
}

void Console::returnToStartMenu()
{
    this->current_window = 0;
}

//=================KEYPAD==========================

char Console::getKey()
{
    char key = this->keypad.getKey();
    if(key) this->bip();
    return key;
}

//=================BUZZER==========================

void Console::bip(int frequency)
{
    tone(this->buzzer_pin, frequency, 50);
    delay(50);
}

void Console::goodBip()
{
    bip(this->buzzer_tone);
    bip(2*this->buzzer_tone);
    bip(2.5*this->buzzer_tone);
}

void Console::badBip()
{
    bip(2*this->buzzer_tone);
    bip(this->buzzer_tone);
}

//=================LCD==========================

void Console::turnOnBacklight()
{
    if(!this->blacklight_state)
    {
        this->blacklight_state = true;
        display.backlight();
    }
}

void Console::turnOffBacklight()
{
    if(this->blacklight_state)
    {
        this->blacklight_state = false;
        display.noBacklight();
    }
}
