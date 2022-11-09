#ifndef OBJECT_H
#define OBJECT_H

class Object
{
    public:
        Object(double dt, double K, double T, double value);

        double calculate(double value);

        double getValue();
        double getSampleTime();
        double getConstantTime();
        double getFactor();

        void setValue(double value);
        void setSampleTime(double value);
        void setConstantTime(double value);
        void setFactor(double value);

    private:
        double mValue, mK, mT, mdt;
};

#endif // OBJECT_H
