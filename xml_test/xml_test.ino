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
  Plan pCold{PlanType::Below, 0, "It's freezing!", "", "", 10};
  Plan pHot{PlanType::Above, 100, "HOT!", "", "", 10};
  Plan pFast{PlanType::Above, 100, "Too fast!", "", "", 10};

  TempSensor ts{std::list<Plan>{pCold, pHot}};
  AcceleroSensor as{std::list<Plan>{pFast}};
  ADCSensor adc(std::list<Plan>{}, A0);
  SensorAgent sa("Hardware agent", "4, chosen by fair dice roll, guaranteed to be random.", "SomeNotSoRandomTopic", 1, false, std::list<Sensor*>{&ts, &as, &adc});
  Serial.println(sa.createInstructionSet());
  Serial.println();
  Serial.println(sa.toXML());
  Serial.println("Done!");
  delay(100000);
}