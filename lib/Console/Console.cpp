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
      buzzer(12, 1000, 10)
{
    this->current_window = 0;
    this->blacklight_state = true;
}

void Console::setup()
{
    this->display.init();
    this->display.backlight();
    this->buzzer.setup();

    char password[4] = {'1', '2', '3', '4'};
    this->copyPasswordToObject(password);

    this->buzzer.goodBip();
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

        case 'D':
            this->exit();
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

    char inserted_password[4] = {EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR};

    int position = 0;


    this->display.setCursor(position, 1);

    while(true)
    {
        this->display.setCursor(0, 1);

        for(int i = 0; i < 4; i++)
        {
            if(inserted_password[i] != EMPTY_CHAR)
            {
                this->display.print('*');
            } else {
                this->display.print('_');
            }
        }

        char key = this->getKey();

        if(key){
            Logs::log("Posicao: " + String(position));

            if(key == '#' || position == 4)
            {
                Logs::log("ENTER");
                if(this->verifyPassword(inserted_password)){
                    Logs::log("SENHA CORRETA");
                    this->buzzer.goodBip();
                    this->routeToMenu('A');
                    return;
                } else {
                    Logs::log("SENHA INCORRETA");
                    this->buzzer.badBip();
                    position = 0;
                    Logs::log("SENHA INSERIDA: ");
                    for(int i = 0; i < 4; i++)
                    {
                        Logs::log(String(inserted_password[i]));
                        inserted_password[i] = EMPTY_CHAR;
                    }
                }

            } else {
                Logs::log("INSERINDO CARACTERE '" + String(key) + "' NA POSICAO " + String(position));
                inserted_password[position] = key;
                Logs::log("SENHA INSERIDA ATUAL: " + String(inserted_password[0]) + String(inserted_password[1]) + String(inserted_password[2]) + String(inserted_password[3]) );
                position++;
            }
        }

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

void Console::exit()
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

//=================PASSWORD==========================

void Console::copyPasswordToObject(char password[4])
{
    for(int i = 0; i < 4; i++)
    {
        this->password[i] = password[i];
    }
}

bool Console::verifyPassword(char password[4])
{
    for(int i = 0; i < 4; i++)
    {
        if(this->password[i] != password[i]) return false;
    }
    return true;
}
