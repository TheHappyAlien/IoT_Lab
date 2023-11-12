#include <util/atomic.h>
#include <LiquidCrystal_I2C.h>

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define ENCODER1 A2
#define ENCODER2 A3

#define RED_BUTTON 2

#define DEBOUNCING_PERIOD 100
#define DEBOUNCE_PERIOD 10UL

LiquidCrystal_I2C lcd(0x27, 16, 2);

void drawMenu(int topLine)
{
  if (topLine == 0)
  {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print(" Menu:");
    lcd.setCursor(4, 1);
    lcd.print(" <RED>");      
  }
  else if (topLine == 1)
  {
    lcd.clear();    
    lcd.setCursor(4, 0);
    lcd.print(" RED");
    lcd.setCursor(4, 1);
    lcd.print(" <GREEN>");    
  }
  else if (topLine == 2)
  {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print(" GREEN");
    lcd.setCursor(4, 1);
    lcd.print(" <BLUE>");   
  }
}

int chooseLED(int choice)
{
  if (choice == 0)
  {
    return LED_RED;
  }
  else if (choice == 1)
  {
    return LED_GREEN;
  }
  else
  {
    return LED_BLUE;
  }
}



bool isRedButtonPressed() 
{
  static int debounced_button_state = HIGH;
  static int previous_reading = HIGH;
  static unsigned long last_change_time = 0UL;
  bool isPressed = false;

  int current_reading = digitalRead(RED_BUTTON);

  if (previous_reading != current_reading) 
  {
    last_change_time = millis();
  }

  if (millis() - last_change_time > DEBOUNCE_PERIOD) {
    if (current_reading != debounced_button_state) {
      if (debounced_button_state == HIGH && current_reading == LOW) {
        isPressed = true;
      }
      debounced_button_state = current_reading;
    }
  }

  previous_reading = current_reading;

  return isPressed;
}

void printLuminocity(int luminocity)
{
  char buffer[40];
  sprintf(buffer, "Luminocity: %3d", luminocity);
  lcd.setCursor(0, 0);
  lcd.print(buffer);
}

void setup()
{
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, 0);

  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_GREEN, 0);

  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_BLUE, 0);

  pinMode(ENCODER1, INPUT_PULLUP);
  pinMode(ENCODER2, INPUT_PULLUP);

  pinMode(RED_BUTTON, INPUT_PULLUP);


  lcd.init();
  lcd.backlight();
  drawMenu(0);
  PCICR |= (1 << PCIE1);
  PCMSK1 |= (1 << PCINT10);
}

volatile int encoder1 = HIGH;
volatile int encoder2 = HIGH;
volatile unsigned long encoderTimestamp = 0UL;

ISR(PCINT1_vect)
{
  encoder1 = digitalRead(ENCODER1);
  encoder2 = digitalRead(ENCODER2);
  encoderTimestamp = millis();
}

int encoderValue = 0;
int lastEn1 = LOW;
unsigned long lastChangeTimestamp = 0UL;
int chosenLED = 0;
bool inMenu = true;

short redLuminocity = 0;
short greenLuminocity = 0;
short blueLuminocity = 0;

void saveLuminocity(short luminocity)
{
  if (chosenLED == LED_RED)
  {
    redLuminocity = luminocity;
  }
  else if (chosenLED == LED_GREEN)
  {
    greenLuminocity = luminocity;
  }
  else
  {
    blueLuminocity = luminocity;
  }
  analogWrite(chosenLED, luminocity);
}

short readLuminocity()
{
  if (chosenLED == LED_RED)
  {
    return redLuminocity;
  }
  else if (chosenLED == LED_GREEN)
  {
    return greenLuminocity;
  }
  else
  {
    return blueLuminocity;
  }
}

short readChosenOption()
{
  if (chosenLED == LED_RED)
  {
    return 0;
  }
  if (chosenLED == LED_GREEN)
  {
    return 1;
  }
  else
  {
    return 2;
  }
}

void loop()
{
  int en1;
  int en2;
  unsigned long timestamp;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    en1 = encoder1;
    en2 = encoder2;
    timestamp = encoderTimestamp;
  }

  if (isRedButtonPressed())
  {
    if (inMenu)
    {
      inMenu = false;
      chosenLED = chooseLED(encoderValue);
      encoderValue = readLuminocity();
      lcd.clear();
      printLuminocity(encoderValue);
    }
    else if (!inMenu)
    {
      inMenu = true;
      saveLuminocity(encoderValue);
      lcd.clear();      
      drawMenu(readChosenOption());
      encoderValue = readChosenOption();      
    }
  }

  if (inMenu)
  {
    if (en1 == LOW && timestamp > lastChangeTimestamp + DEBOUNCING_PERIOD)
    {
      if (en2 == HIGH)
      {
        if (encoderValue < 2)    
          encoderValue += 1;
      }
      else
      {
        if (encoderValue > 0)
          encoderValue -= 1;
      }
      lastChangeTimestamp = timestamp;
      drawMenu(encoderValue);
    }
  }
  else
  {
    if (en1 == LOW && timestamp > lastChangeTimestamp + DEBOUNCING_PERIOD)
    {
      if (en2 == HIGH)
      {
        if (encoderValue < 255)    
          encoderValue += 15;
      }
      else
      {
        if (encoderValue > 0)
          encoderValue -= 15;
      }
      lastChangeTimestamp = timestamp;
      lcd.clear();
      printLuminocity(encoderValue);
      analogWrite(chosenLED, encoderValue);
    }
  }

  lastEn1 = en1;
}
