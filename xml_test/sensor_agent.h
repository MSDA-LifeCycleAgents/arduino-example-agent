#pragma once

#include <list>
#include "sensor.h"
#include "tinyxml2.h"
#include <NTPClient.h>

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
    SensorAgent(const char* name, const char* identifier, const char* topic, bool toDA, std::list<Sensor*> sensors, NTPClient &ntp)
        : _name{name}, _identifier{identifier}, _topic{topic}, _toDecisionAgent{toDA}, _sensors{sensors}, ntp(ntp)
    // TODO: replace options with struct?
    {
    }

    const char* createInstructionSet()
    {
        XMLDocument doc;
        doc.InsertEndChild(doc.NewDeclaration());

        auto instr = doc.NewElement("instructions");
        doc.InsertEndChild(instr);
        auto ident = doc.NewElement("identifier");
        ident->SetText(_identifier);
        instr->InsertEndChild(ident);

        // Messaging
        auto msg = doc.NewElement("messaging");
        instr->InsertEndChild(msg);
        auto topic = doc.NewElement("topic");
        msg->InsertEndChild(topic);
        auto tName = doc.NewElement("name");
        tName->SetText(_topic);
        topic->InsertEndChild(tName);
        auto toDA = doc.NewElement("directToDecisionAgent");
        toDA->SetText(_toDecisionAgent);
        msg->InsertEndChild(toDA);
        auto xSensors = doc.NewElement("sensors");
        instr->InsertEndChild(xSensors);
        
        // Sensors
        for (auto& sensor : _sensors)
        {
            auto s = doc.NewElement("sensor");
            s->SetAttribute("id", sensor->getName());// TODO: replace spaces?
            xSensors->InsertEndChild(s);
            auto label = doc.NewElement("label");
            label->SetText(sensor->getName());
            s->InsertEndChild(label);
            auto sMin = doc.NewElement("min");
            sMin->SetText(sensor->getMinVal());
            s->InsertEndChild(sMin);
            auto sMax = doc.NewElement("max");
            sMax->SetText(sensor->getMaxVal());
            s->InsertEndChild(sMax);

            auto unit = doc.NewElement("unit");
            unit->SetText(sensor->getUnit());
            s->InsertEndChild(unit);
            auto interval = doc.NewElement("intervalinseconds");
            interval->SetText(sensor->getInterval());
            s->InsertEndChild(interval);
            
            auto backups = doc.NewElement("amountOfBackupMeasurements");
            backups->SetText(sensor->getNrBackupMeasurements());
            s->InsertEndChild(backups);
        }

        auto fallback = doc.NewElement("fallback");
        instr->InsertEndChild(fallback);
        auto via = doc.NewElement("via");
        via->SetText("ScreenAgent"); // TODO: replace with proper agent
        fallback->InsertEndChild(via);
        auto to = doc.NewElement("to");
        fallback->InsertEndChild(to);

        XMLPrinter printer;
        doc.Print(&printer);
        return printer.CStr();
    }

    /**
     * Converts the sensors values to an XML representation.
     * This includes the name of the sensor and its values.
     * 
     * \return an XML representation of the sensors
    */
    const char* toXML(std::list<Sensor*> sensors)
    {
        XMLDocument doc;
        doc.InsertEndChild(doc.NewDeclaration());
        auto root = doc.NewElement("sensorreading");
        doc.InsertEndChild(root);

        auto timestamp = doc.NewElement("timestamp");
        long unsigned int time = ntp.getEpochTime();
        String time_str = String(time);
        timestamp->SetText(time_str.c_str());
        root->InsertEndChild(timestamp);
        
        auto sroot = doc.NewElement("sensors");
        root->InsertEndChild(sroot);
        for (auto sensor : sensors)
        {            
            auto s = doc.NewElement("sensor");
            s->SetAttribute("id", sensor->getName());
            sroot->InsertEndChild(s);
            for (auto& pair : sensor->getData())
            {
                auto sm = doc.NewElement("measurement");
                sm->SetAttribute("id", pair.first);
                auto sv = doc.NewElement("value");
                sv->SetText(pair.second);
                sm->InsertEndChild(sv);
                s->InsertEndChild(sm);
            }
        }

        XMLPrinter printer;
        doc.Print(&printer);
        return printer.CStr();
    }

    void update()
    {
        std::list<Sensor*> queue;
        for (auto& sensor : _sensors)
        {
            if (sensor->needsUpdate(ntp.getEpochTime()))
            {
                queue.push_back(sensor);
            }
        }
        if (!queue.empty())
        {
            Serial.println(toXML(queue));
        }
    }
private:
    std::list<Sensor*> _sensors;
    const char* _name;
    const char* _identifier;
    const char* _topic;
    const bool _toDecisionAgent;
    NTPClient &ntp;
};