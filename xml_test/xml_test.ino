#include "tinyxml2.h"
using namespace tinyxml2;

#include "sensor_agent.h"
#include "accelero_sensor.h"
#include "temp_sensor.h"
#include "arduino_adc_sensor.h"

void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("Serial started!");
}

void loop()
{
  Serial.println("Start");
  TempSensor ts;
  AcceleroSensor as;
  ADCSensor adc(A0);
  SensorAgent sa("HW", std::list<Sensor*>{&ts, &as, &adc});
  Serial.println(sa.toXML());
  Serial.println("Done!");
  delay(100000);
}

