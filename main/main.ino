#include "Hydroino.h"
// dependency: lowpower by lowpowerlab

SensorValues Values;

void setup() 
{
  InitDisplay();
  InitHydrogenSensor();
  delay(2000);
}

void loop() 
{
  
  GetSensorValues(&Values);
  
  //if(IsLeverPulled())
  //  PrintStatus(Values.Hydrogen, Values.Light, Values.Battery, Values.Fertilization);

  if(IsWaterNeeded(Values.Hydrogen))
  {
    WaterThePlant();
  }

  // sleep for 30 min and check again
  SleepTwoMinutes(15);  
}
