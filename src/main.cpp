#include <Arduino.h>
#include "Logs.hpp"
#include "Console.hpp"

Console console;

void setup() {
    Logs::init();
}

void loop() {
    console.run();
    char key = console.getKey();
    
    if(key)
    {
        Logs::log(String(key));
    }
}