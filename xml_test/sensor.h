#pragma once

#include <map>

/**
 * Base class for sensors
*/
class Sensor{
public:
    /**
     * Activates the sensor
     * 
     * <b>NOTE: Must be implemented in a subclass</b>
     * 
     * \return <b>true</b> if succesful, <b>false</b> otherwise
    */
    virtual bool activate() = 0;
    
    /**
     * Activates the sensor
     * 
     * <b>NOTE: Must be implemented in a subclass</b>
     * 
     * \return <b>true</b> if succesful, <b>false</b> otherwise
    */
    virtual bool deactivate() = 0;

    /**
     * Gets data from the sensor
     * 
     * <b>NOTE: Must be implemented in a subclass</b>
     * 
     * \return a map (key value pair/dictionary) of sensor data
    */
    //template<typename T>
    virtual const std::map<const char*, double> getData() = 0;


    /**
     * Gets the unit associated with the sensor data
     *
     * \return the name of the used unit
     */
    const char* getUnit()
    {
        return _unit;
    }

    /**
     * Gets the name associated with the sensor
     *
     * \return the name of the sensor
     */
    const char* getName()
    {
        return _name;
    }

    /**
     * Gets the interval of the sensor
     *
     * \return the interval of the sensor
     */
    size_t getInterval()
    {
        return _interval;
    }

protected:
    /**
     * 
     * \param name the name of the sensor
     * \param unit the unit used by the sensor
     * \param interval the interval of the sensor
     * \param minval the minimum value expected from the sensor
     * \param maxval the maximum value expected from the sensor
    */
    Sensor(const char* name, const char* unit, size_t interval, size_t minval, size_t maxval)
        : _name{name}, _unit{unit}, _interval{interval}, _minVal{minval}, _maxVal{maxval}
    {}
    
    bool active = false;

private:
    const char* _unit;
    const char* _name;
    const size_t _interval;
    const double _minVal;
    const double _maxVal;
};