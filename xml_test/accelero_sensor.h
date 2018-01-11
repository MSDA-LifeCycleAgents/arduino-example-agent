#pragma once

#include "sensor.h"

class AcceleroSensor : public Sensor
{
public:
    AcceleroSensor(std::list<Plan> plans)
        : Sensor("AcceleroSensor", "G", 10, -1000.0f, 1000.0f, 10, plans)
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