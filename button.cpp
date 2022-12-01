#include "button.h"

Button::Button(int pin)
{
    _pin = pin;
    wiringPiSetup();
    pinMode(_pin, INPUT);
}

int Button::getStatus() {
    return digitalRead(_pin);
}
