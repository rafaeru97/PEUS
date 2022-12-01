#ifndef BUTTON_H
#define BUTTON_H
#include <wiringPi.h>


class Button
{
    public:
        Button(int pin);
        int getStatus();

    private:
        int _pin;
};

#endif // BUTTON_H
