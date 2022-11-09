#ifndef PID_H
#define PID_H

class PID
{
public:
    PID(double dt, double max, double min, double Kp, double Ki, double Kd, double value);

    double calculate(double set);

    double getValue();
    double getSampleTime();
    double getFactorP();
    double getFactorI();
    double getFactorD();
    double getError();
    double getPreError();
    double getIntegral();

    void setValue(double value);
    void setSampleTime(double value);
    void setFactorP(double value);
    void setFactorI(double value);
    void setFactorD(double value);

private:
    double mdt, mmax, mmin, mKp, mKd, mKi;
    double pre_error =  0;
    double integral = 0;
    double error = 0;
    double mValue;
};

#endif // PID_H
