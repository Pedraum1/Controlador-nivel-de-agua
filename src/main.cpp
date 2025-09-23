#include <Arduino.h>
#include "Logs.hpp"
#include "Console.hpp"

Console console;

void setup() {
    Logs::init();
    console.setup();
    console.bip();
}

void loop() {
    console.run();
}