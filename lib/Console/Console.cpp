#include "Console.hpp"

char keys[4][4] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[4] = {9, 8, 7, 6};
byte colPins[4] = {5, 4, 3, 2};

//=================CONSOLE GENERALS==========================

Console::Console()
    : display(0x27, 16, 2),
      keypad(makeKeymap(keys), rowPins, colPins, 4, 4),
      buzzer(12, 1000)
{
    this->current_window = 0;
    this->blacklight_state = true;
}

void Console::setup()
{
    this->display.init();
    this->display.backlight();
}

void Console::run()
{
    switch(this->current_window)
    {
        case 0:
            this->runLoginWindow();
        break;

        case 1:
            this->clearLCD();
            this->display.setCursor(0, 0);
            this->display.print("Menu principal");
            while(true){delay(10);}
        break;

        default:
            this->returnToStartMenu();
        break;
    }
}

//=================WINDOWS======================

void Console::runLoginWindow()
{
    this->clearLCD();
    this->display.setCursor(2, 0);
    this->display.print("Hello World!");
    this->display.setCursor(0, 1);
    this->display.print("Tela de Login");

    while(true)
    {
        char key = this->getKey();
        if(key && key == '#')
        {
            this->current_window = 1;
            return;
        }
    }
    delay(10);
}

void Console::returnToStartMenu()
{
    this->current_window = 0;
}

//=================BUZZER==========================

void Console::bip()
{
    this->buzzer.bip();
}

//=================KEYPAD==========================

char Console::getKey()
{
    char key = this->keypad.getKey();
    if(key) this->buzzer.bip();
    return key;
}

//=================LCD==========================

void Console::clearLCD()
{
    this->display.setCursor(0, 0);
    this->display.print("                ");
    this->display.setCursor(0, 1);
    this->display.print("                ");
}

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
