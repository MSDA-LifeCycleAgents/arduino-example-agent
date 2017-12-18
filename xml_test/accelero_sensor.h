#pragma once

#include "sensor.h"

class AcceleroSensor : public Sensor
{
public:
    AcceleroSensor() : Sensor("AcceleroSensor", "G")
    {}

    virtual bool activate() override
    {
        return true;
    }

    virtual bool deactivate() override
    {
        return true;
    }

    virtual const std::map<const char*, double> getData() override
    {
        return std::map<const char*, double> {{"X", 0}, {"Y", 1}, {"Z", 2}};
    }
};