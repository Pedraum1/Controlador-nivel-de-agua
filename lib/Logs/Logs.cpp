#include "Logs.hpp"

void Logs::init(unsigned long baud)
{
    if(ENV == PRODUCTION) return;
    Serial.begin(baud);
    Serial.println("Log service initiated");
}

void Logs::log(String message)
{
    if(ENV == PRODUCTION) return;
    Serial.print("#LOG: ");
    Serial.println(message);
}

void Logs::error(String message)
{
    if(ENV == PRODUCTION) return;
    Serial.print("!ERR: ");
    Serial.println(message);
}