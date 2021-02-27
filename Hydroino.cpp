#define lowWaterLevel 560
#define goodWaterLevel 340
#define LC_rs 12
#define LC_en 11
#define LC_d4 5
#define LC_d5 4
#define LC_d6 3
#define LC_d7 2
#define HydSensorPin A0
#define HydroPumpGRND 8
#define HydSensorGRND 9
#define ADC_MAX 1023

#define lcd.print Serial.println

#include <LiquidCrystal.h>
#include <LowPower.h>
#include <Hydroino.h>

const int MaxBatteryLevel = 5;
//LiquidCrystal lcd(LC_rs, LC_en, LC_d4, LC_d5, LC_d6, LC_d7);


//Function to sleep the Number of minutes give (SleepTwoMinutes() is more efficient)
void SleepMinutes(int MinuteCount)
{
  int Loops = 15 * MinuteCount;
  for(int i=0; i<Loops; i++)
  {
    LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);   
  }
  
}

//Function to sleep the Number of Minutes given times two (TwoMinuteCount = 4 -> 8 Minute sleep)
void SleepTwoMinutes(int TwoMinuteCount)
{
  int Loops = 15 * TwoMinuteCount;
  for(int i=0; i<Loops; i++)
  {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);   
  }
}



//Funktion which needs to be called for using a Display
void InitDisplay()
{
  //lcd.begin(16, 2);
  Serial.begin(9600)
}

//Funktion to Print everything on the LCD Display
void PrintStatus(int Hydrogen, int Light, int Battery, int Fertilization)
{
  //lcd.clear();
  

  //lcd.setCursor(0,0); //print Hydrogen Level
  lcd.print("H:");
  lcd.print(Hydrogen);
  lcd.print("%");

  //lcd.setCursor(8,0); //print Light Level
  lcd.print("L:");
  lcd.print(Light);
  lcd.print("kLx");

  //lcd.setCursor(0,1); //print Battery Level
  lcd.print("B:");
  BatteryPrinting(Battery);

  //lcd.setCursor(8,1); //print Fertilization Level
  lcd.print("F:");
  lcd.print(Fertilization);
  lcd.print("%");
}

//Helpfunktion for PrintStatus()
void BatteryPrinting(int Battery)
{
  if(Battery > MaxBatteryLevel) //If value is to big ... set it to 4
  Battery = MaxBatteryLevel;

  for(int i = MaxBatteryLevel; i > 0; i--){ //example Battery is 3: The Outcome will be 3 PLuses and one minus at the end
    if(Battery-- > 0)
    lcd.print("+");
    else
    lcd.print("-");
  }
  
}

void InitLever()
{

}

bool IsLeverPulled()
{
  return true;
}

//Gets all the Sensor Values and than puts them in the given Variable
void GetSensorValues(SensorValues* Values)
{
  //Get Hydrogen Values (480 is pure water and 780 is dry dirt. So to calculate, i flip the values)
  int Hyd = ADC_MAX - GetHydrogenValue();
  // Have the Hydrogen level start at around 0
  Hyd = Hyd - (ADC_MAX - lowWaterLevel);
  // Calculate the percentage
  Values->Hydrogen = (Hyd * 100) / (lowWaterLevel - goodWaterLevel);

  //Get Light
  Values->Light = 0;

  //Get Batterystatus
  Values->Battery = 5;

  //Get Fertilization
  Values->Fertilization = 0;
}

int GetHydrogenValue()
{
  int value;
  digitalWrite(HydSensorGRND, LOW);
  delay(300);
  value = analogRead(HydSensorPin);
  digitalWrite(HydSensorGRND, HIGH);
  return value;
}

void InitHydrogenSensor()
{
  pinMode(HydSensorPin, INPUT);
  pinMode(HydSensorGRND, OUTPUT);
}

bool DippedUnderHydrogenTreshold = false;
#define LowerHydrogenTreshhold 20
#define UpperHydrogenTreshhold 70

// Checks if water is needed
// Under 20 % it should start filling up until it reaches 70 % then wait again for dipping below 20 %
bool IsWaterNeeded(int HydrogenPercent)
{
  // Waterlevel 0 - 20
  if(HydrogenPercent <= LowerHydrogenTreshhold)
    DippedUnderHydrogenTreshold = true;

  // Waterlevel 20 - 69 AND it dipped below the Treshhold of 20 %
  else if(HydrogenPercent >= LowerHydrogenTreshhold && HydrogenPercent < UpperHydrogenTreshhold && DippedUnderHydrogenTreshold)
    DippedUnderHydrogenTreshold = true;

  // Waterlevel 70 - 100 OR 20 - 69 if the Treshold wasn't dipped
  else 
    DippedUnderHydrogenTreshold = false;

  return DippedUnderHydrogenTreshold;
}

//Process for Watering the Plants
void WaterThePlant()
{
    digitalWrite(HydroPumpGRND, Low);
    delay(2000);
    digitalWrite(HydroPumpGRND, HIGH);
}
