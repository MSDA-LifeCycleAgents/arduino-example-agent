#pragma once

#include <list>
#include "sensor.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class SensorAgent
{
public:
    /**
     * Constructs an agent
     * 
     * \param name the name of the sensor agent
     * \param sensors a list of the sensors associated with the agent
    */
    SensorAgent(const char* name, std::list<Sensor*> sensors) : sensors{sensors}
    {}
    
    /**
     * Converts the sensors values to an XML representation.
     * This includes the name of the sensor and its values.
     * 
     * \return an XML representation of the sensors
    */
    const char* toXML()
    {
        XMLDocument doc;
        auto root = doc.NewElement("sensorreading");
        doc.InsertEndChild(root);
        auto sroot = doc.NewElement("sensors");
        root->InsertEndChild(sroot);

        for (auto& sensor : sensors)
        {
            auto s = doc.NewElement("sensor");
            s->SetAttribute("id", sensor->getName());
            sroot->InsertEndChild(s);
            for (auto& pair : sensor->getData())
            {
                auto sp = doc.NewElement("value");
                sp->SetAttribute(pair.first, pair.second);
                s->InsertEndChild(sp);
            }
        }

        XMLPrinter printer;
        doc.Print(&printer);
        return printer.CStr();
    }
private:
    std::list<Sensor*> sensors;
};