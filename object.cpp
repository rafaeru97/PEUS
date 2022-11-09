#include "object.h"

Object::Object(double dt, double K, double T, double value)
{
    mdt = dt;       //sample time
    mK = K;         //factor
    mT = T;         //constant time
    mValue = value; //previous value
}

double Object::calculate(double value)
{
    //Y = K*U/(T/dt+1) + (T/dT)/(T/dt+1) * Y-1
    double output = mK * value / (mT / mdt + 1) + (mT / mdt) / (mT / mdt + 1) * mValue;
    mValue = output;
    return output;
}

double Object::getValue()
{
    return mValue;
}

double Object::getSampleTime()
{
    return mdt;
}

double Object::getConstantTime()
{
    return mT;
}

double Object::getFactor()
{
    return mK;
}

void Object::setValue(double value)
{
    mValue = value;
}

void Object::setSampleTime(double value)
{
    mdt = value;
}

void Object::setConstantTime(double value)
{
    mT = value;
}

void Object::setFactor(double value)
{
    mK = value;
}
