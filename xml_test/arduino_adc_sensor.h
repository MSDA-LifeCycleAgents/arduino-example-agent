#pragma once

#include "sensor.h"
#include <Arduino.h>

class ADCSensor : public Sensor
{
public:
    ADCSensor(uint8_t pin=A0) : Sensor("TemperatureSensor", "C", 30, -273.15f, 1000.0f),pin(pin)
    {}

    virtual bool activate() override
    {
        //not implemented
        return true;
    }

    virtual bool deactivate() override
    {
        //not implemented
        return true;
    }

    virtual const std::map<const char*, double> getData() override
    {
        int adc_val = analogRead(pin);
        double voltage = adc_val * ( 3.3 / 1024.0 );
        return std::map<const char*, double> {{"Voltage", voltage}};
    }

private:
    uint8_t pin;
};