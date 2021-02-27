#include <Hydroino.h>


SensorValues Values;

void setup() 
{
  InitDisplay();
  InitHydrogenSensor();
}

void loop() 
{
  
  GetSensorValues(&Values);
  
  if(IsLeverPulled())
    PrintStatus(Values.Hydrogen, Values.Light, Values.Battery, Values.Fertilization);

  if(IsWaterNeeded(Values.Hydrogen))
  {
    WaterThePlant();
  }

 
  SleepTwoMinutes(15);  
}
