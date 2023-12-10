#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

LiquidCrystal_I2C lcd(0x27, 16, 2);
OneWire oneWire(A1);
DallasTemperature tempSensors(&oneWire);

byte celcius[8] = {
  B01000,
  B10100,
  B01000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

void setupLED()
{
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, LOW);

  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_GREEN, LOW);

  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_BLUE, LOW);
}

void setupLCD()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void setup()
{
  setupLED();
  setupLCD();

  tempSensors.begin();
  lcd.createChar(0, celcius);
}


float tempIn; 
float tempOut;
float maxTemp = 0;
float minTemp = 0;

void setIndicatorLED(float temperature)
{
  if (temperature < 18.0f) {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, HIGH);
  } else if (temperature < 27.0f) {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, LOW);
  } else {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);
  }
  
}

void loop()
{
  tempSensors.requestTemperatures();
  float tempIn = tempSensors.getTempCByIndex(1);
  float tempOut = tempSensors.getTempCByIndex(0);

  minTemp = min(minTemp, tempOut);
  maxTemp = max(maxTemp, tempOut);

  setIndicatorLED(tempOut);

  char buffer[40];
  sprintf(buffer, "IN:%4s", String(tempIn, 1).c_str());
  lcd.setCursor(0, 0);
  lcd.print(buffer);

  sprintf(buffer, "OUT:%4s", String(tempOut, 1).c_str());
  lcd.setCursor(8, 0);
  lcd.print(buffer);

  sprintf(buffer, "MIN:%3s", String(minTemp, 0).c_str());
  lcd.setCursor(0, 1);
  lcd.print(buffer);

  // degree symbol
  lcd.setCursor(7, 1);
  lcd.write(byte(0));

  sprintf(buffer, "MAX:%2s", String(maxTemp, 0).c_str());
  lcd.setCursor(9, 1);
  lcd.print(buffer);

  // degree symbol
  lcd.setCursor(15, 1);
  lcd.write(byte(0));
}