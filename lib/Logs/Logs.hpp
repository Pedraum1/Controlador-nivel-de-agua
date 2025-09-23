#ifndef LOGS_H

#define LOGS_H

#include <Arduino.h>

class Logs
{
    public:
        static void init(unsigned long baud = 9600);
        static void log(String message);
        static void error(String message);
};

#endif