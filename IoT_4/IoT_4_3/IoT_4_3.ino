#include <LiquidCrystal_I2C.h>

#define POTENTIOMETER A0

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("VALUE READ: ");
  lcd.setCursor(0, 1);
  lcd.print("VOLTAGE: ");
}

int previousValue = -1;

void loop()
{
  int value = analogRead(A0);
  float voltage = value*0.00489;

  if (value == previousValue){
    return;
  }

  previousValue = value;

  lcd.setCursor(12, 0);
  lcd.print("    ");
  lcd.setCursor(12, 0);
  lcd.print(value);

  lcd.setCursor(9, 1);
  lcd.print("    ");
  lcd.setCursor(9, 1);
  lcd.print(voltage);
}
