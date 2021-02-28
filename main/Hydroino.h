#ifndef Hydroino_h
#define Hydroino_h

#include "Arduino.h"
#include <LiquidCrystal.h>
#include <LowPower.h>
//A Struct for saving the Sensor Values in a ordered way
struct SensorValues 
{
    int Hydrogen; 
    int Light; 
    int Battery; 
    int Fertilization;
};


//Function to sleep the Number of minutes give (SleepTwoMinutes() is more efficient)
void SleepMinutes(int MinuteCount);

//Function to sleep the Number of Minutes given times two (TwoMinuteCount = 4 -> 8 Minute sleep)
void SleepTwoMinutes(int TwoMinuteCount);

//Funktion which needs to be called for using a Display
void InitDisplay();

//Funktion to Print everything on the LCD Display
void PrintStatus(int Hydrogen, int Light, int Battery, int Fertilization);

//Helpfunktion for PrintStatus()
void BatteryPrinting(int Battery);

//Checks if the Lever is Pulled
bool IsLeverPulled();

//Gets all the Sensor Values and than puts them in the given Variable
void GetSensorValues(SensorValues* Values);

//Checks if water is needed
bool IsWaterNeeded(int HydrogenPercent);

//Process for Watering the Plants
void WaterThePlant();

//Needed to Use the Funktion GetHydrogenValue()
void InitHydrogenSensor();

//Returns the HydrogenRawValue from A0
int GetHydrogenValue();
#endif
