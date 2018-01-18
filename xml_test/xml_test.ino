#include "tinyxml2.h"
using namespace tinyxml2;

#include "sensor_agent.h"
#include "accelero_sensor.h"
#include "temp_sensor.h"
#include "arduino_adc_sensor.h"
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "config.h"

WiFiUDP ntpUDP;
NTPClient ntp(ntpUDP);

TempSensor ts;
AcceleroSensor as;
ADCSensor adc(A0);
SensorAgent sa("Hardware agent", "4, chosen by fair dice roll, guaranteed to be random.", "SomeNotSoRandomTopic", false, std::list<Sensor*>{&ts, &as, &adc}, ntp);

void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("Serial started!");

  WiFi.begin(ssid,password);
  Serial.print("Connecting to wifi...");
  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print(".");
  }
  Serial.println("wifi connected!");
  ntp.begin();
  ntp.update();
  Serial.println();
  Serial.println(sa.createInstructionSet());
  Serial.println();
}

void loop()
{
  ntp.update();
  sa.update();
}