#include "Logs.hpp"

void Logs::init(unsigned long baud = 9600)
{
    Serial.begin(baud);
    Serial.println("Log service initiated");
}

void Logs::log(String message)
{
    Serial.print("#LOG: ");
    Serial.println(message);
}

void Logs::error(String message)
{
    Serial.print("!!ERROR: ");
    Serial.println(message);
}