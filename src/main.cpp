#include <Arduino.h>
#include "Console.hpp"

#include "Logs.hpp"

Console console;

void setup() {
    Logs::init();
    console.setup();
    console.bip();
}

void loop() {
    console.run();
}