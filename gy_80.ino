#include <Wire.h>
#include <LiquidCrystal.h>
#include "HMC5883L.h"
#include "L3G4200D.h"
// #include "ADXL345.h"
#include "DataSmoother.h"
#include <sstream>
#include <string>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_ADXL345.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
HMC5883L compass;
L3G4200D gyro;
Adafruit_BMP085_Unified baro = Adafruit_BMP085_Unified(10085);
DataSmoother data = DataSmoother();
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const float alpha = 0.5;
const String sXg = "Xg: ";


double fXa = 0;
double fYa = 0;
double fZa = 0;

void setup()
{
  Wire.begin();
  accel.begin();
  compass.SetScale(1.3);
  compass.SetMeasurementMode(Measurement_Continuous);
  gyro.setupL3G4200D(2000); // 2000 deg / sec
  baro.begin();
  lcd.begin(20, 4);
  delay(100);
}

void loops()
{
  lcd.clear();
  lcd.setCursor(0,0);
  double result = data.smoothe(10, 9.9);
  lcd.print(result);
  lcd.setCursor(0,2);
  lcd.print(data.alpha);
  lcd.setCursor(0,3);
  lcd.print(data.lastVal[10]);
  delay(1999);
}

void loop()
{
  if (digitalRead(6) == HIGH)
  {
    show9DOF();
  } else {
    showBaro();
  }
  delay(200);
}

void showBaro()
{
  sensors_event_t event;
  baro.getEvent(&event);
  float temperature;
 
  /* Display the results (barometric pressure is measure in hPa) */
  if (event.pressure)
  {
    baro.getTemperature(&temperature);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp:");
    lcd.print(temperature * 9 / 5 + 32);
    lcd.setCursor(0, 1);
    lcd.print("Press:");
    lcd.print(event.pressure);
    lcd.setCursor(0, 2);
    lcd.print("Altitude:");
    lcd.print(baro.pressureToAltitude(SENSORS_PRESSURE_SEALEVELHPA,
                                        event.pressure,
                                        temperature));
  }
  lcd.setCursor(0,3);
  lcd.print("bearing:");
  lcd.print(compass.getDegrees());
}

void show9DOF()
{
  sensors_event_t event;
  accel.getEvent(&event);
  
  MagnetometerRaw mag = compass.ReadRawAxis();
  
  int Xg, Yg, Zg;
  gyro.read(&Xg, &Yg, &Zg);
  
  writeResults(data.smoothe(1, event.acceleration.x),
               data.smoothe(2, event.acceleration.y),
               data.smoothe(3, event.acceleration.z),
               data.smoothe(4, mag.XAxis), 
               data.smoothe(5, mag.YAxis), 
               data.smoothe(6, mag.ZAxis), 
               data.smoothe(7, Xg), 
               data.smoothe(8, Yg), 
               data.smoothe(9, Zg));
}

void writeResults(double Xa, double Ya, double Za, double Xm, double Ym, double Zm, double Xg, double Yg, double Zg)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  X     Y     Z");
  writeAt(1, 0, Xa);
  writeAt(1, 6, Ya);
  writeAt(1, 12, Za);
  writeAt(2, 0, (int)Xm);
  writeAt(2, 6, (int)Ym);
  writeAt(2, 12, (int)Zm);
  writeAt(3, 0, (int)Xg);
  writeAt(3, 6, (int)Yg);
  writeAt(3, 12, (int)Zg);
}

void writeAt(int row, int col, double text)
{
  lcd.setCursor(col, row);
  lcd.print(text);
}
void writeAt(int row, int col, int text)
{
  lcd.setCursor(col, row);
  lcd.print(text);
}

