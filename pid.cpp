#include "pid.h"

PID::PID(double dt, double max, double min, double Kp, double Ki, double Kd, double value)
{
    mdt = dt;           //sample time
    mmax = max;         //max restrict
    mmin = min;         //min restrict
    mKp = Kp;           //P factor
    mKd = Kd;           //D factor
    mKi = Ki;           //I factor
    mValue = value;     //previous value
}

double PID::calculate(double set)
{
    error = set - mValue;

    // P element
    double Pout = mKp * error;

    // I element
    integral = integral + (error * mdt);
    double Iout = mKi * integral;

    // D element
    double derivative = (error - pre_error) / mdt;
    double Dout = mKd * derivative;

    double out = Pout + Iout + Dout;

    if(out > mmax)
        out = mmax;
    if(out < mmin)
        out = mmin;

    pre_error = error;

    return out;
}

double PID::getValue()
{
    return mValue;
}

double PID::getSampleTime()
{
    return mdt;
}

double PID::getFactorP()
{
    return mKp;
}

double PID::getFactorI()
{
    return mKi;
}

double PID::getFactorD()
{
    return mKd;
}

double PID::getError()
{
    return error;
}

double PID::getPreError()
{
    return pre_error;
}

double PID::getIntegral()
{
    return integral;
}

void PID::setValue(double value)
{
    mValue = value;
}

void PID::setSampleTime(double value)
{
    mdt = value;
}

void PID::setFactorP(double value)
{
    mKp = value;
}

void PID::setFactorI(double value)
{
    mKi = value;
}

void PID::setFactorD(double value)
{
    mKd = value;
}
