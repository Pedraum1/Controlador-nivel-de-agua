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

    char password[4] = {'1', '2', '3', '4'};
    this->copyPasswordToObject(password);
}

void Console::run()
{
    switch(this->current_window)
    {
        case Login:
            Logs::log("Indo para tela de Login");
            this->runLoginWindow();
        break;

        case Main:
            Logs::log("Indo para menu inicial");
            this->runStartMenu();
        break;

        case Setup:
            Logs::log("Indo para setup");
            this->runSetupMenu();
        break;

        case ManualControl:
            Logs::log("Indo para controle manual");
            this->runManualControlMenu();
        break;

        default:
            this->returnToStartMenu();
        break;
    }
}

bool Console::menuOptionDetected(char key_pressed)
{
    if(
        key_pressed == 'A' ||
        key_pressed == 'B' ||
        key_pressed == 'C' ||
        key_pressed == 'D'
    ) return true;

    return false;
}

void Console::routeToMenu(char option)
{
    switch(option)
    {
        case 'A':
            this->current_window = Main;
        break;

        case 'B':
            this->current_window = Setup;
        break;

        case 'C':
            this->current_window = ManualControl;
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
    this->display.setCursor(0, 0);
    this->display.print("LOGIN:");
    this->display.setCursor(0, 1);
    this->display.print("____");

    unsigned long last_time = millis();
    unsigned long current_time = millis();

    bool show_digit  = true;

    this->display.setCursor(0, 1);

    while(true)
    {
        char key = this->getKey();
        if(this->menuOptionDetected(key))
        {
            this->routeToMenu(key);
            return;
        }

        current_time = millis();
        if(current_time - last_time >= 1000)
        {
            last_time = current_time;
            show_digit = !show_digit;
            if(show_digit){
                this->display.setCursor(0, 1);
                this->display.print("_");
            } else {
                this->display.setCursor(0, 1);
                this->display.print(" ");
            };
        }

        //TODO: INSERIR CÓDIGO DO MENU DE LOGIN

    }
}

void Console::runStartMenu()
{
    this->clearLCD();
    this->display.setCursor(0, 0);
    this->display.print("Menu inicial");
    while(true)
    {
        char key = this->getKey();
        if(this->menuOptionDetected(key))
        {
            this->routeToMenu(key);
            return;
        }

        //TODO: INSERIR CÓDIGO DO MENU INICIAL

    }
}

void Console::runSetupMenu()
{
    this->clearLCD();
    this->display.setCursor(0, 0);
    this->display.print("Menu de");
    this->display.setCursor(0, 1);
    this->display.print("configuracao");

    while(true)
    {
        char key = this->getKey();
        if(this->menuOptionDetected(key))
        {
            this->routeToMenu(key);
            return;
        }
        //TODO: INSERIR CÓDIGO DO MENU DE OPÇÕES
    }
}

void Console::runManualControlMenu()
{
    this->clearLCD();
    this->display.setCursor(0, 0);
    this->display.print("Menu de");
    this->display.setCursor(0, 1);
    this->display.print("controle manual");

    while(true)
    {
        char key = this->getKey();
        if(this->menuOptionDetected(key))
        {
            this->routeToMenu(key);
            return;
        }
        //TODO: INSERIR CÓDIGO DO MENU DE OPÇÕES
    }
}

void Console::returnToStartMenu()
{
    this->current_window = 1;
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

//=================PASSWORD==========================

void Console::copyPasswordToObject(char password[4])
{
    for(int i = 0; i < 4; i++)
    {
        this->password[i] = password[i];
    }
}
