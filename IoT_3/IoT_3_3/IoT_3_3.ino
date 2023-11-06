#include <LiquidCrystal_I2C.h>

#define RED_BUTTON 2
#define GREEN_BUTTON 4
#define DEBOUNCE_PERIOD 10UL

LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long seconds = 0;
unsigned long millisOnStart = 0;
unsigned long millisOver = 0;
bool timerGoing = false;

void initButtons()
{
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

bool secondPassed()
{
  bool secondPassed = false;

  if (millis() - (seconds*1000 + millisOnStart) >= 1000){
    seconds++;
    secondPassed = true;
  }

  return secondPassed;
}

void printTime()
{
    lcd.setCursor(0, 0);    
    lcd.print(seconds);
}

bool isButtonPressed(int button, int& debounced_button_state, int& previous_reading, unsigned long& last_change_time)
{
  
  bool isPressed = false;
  int current_reading = digitalRead(button);
  
  if (previous_reading != current_reading)
  {
    last_change_time = millis();
  }
  
  if (millis() - last_change_time > DEBOUNCE_PERIOD)
  {
    if (current_reading != debounced_button_state)
    {
      if (debounced_button_state == LOW && current_reading == HIGH)
      {
        isPressed = true;
      }
      debounced_button_state = current_reading;
    }
  }
  
  previous_reading = current_reading;
  
  return isPressed;
}

static int red_debounced_button_state = HIGH;
static int red_previous_reading = HIGH;
static unsigned long red_last_change_time = 0UL;

static int green_debounced_button_state = HIGH;
static int green_previous_reading = HIGH;
static unsigned long green_last_change_time = 0UL;


void setup()
{
  initButtons();  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(0);
}

void loop()
{
  if (timerGoing)
  {
    if (secondPassed())
    {
      printTime();
    }

    if (isButtonPressed(GREEN_BUTTON, green_debounced_button_state, green_previous_reading, green_last_change_time))
    {
      timerGoing = false;
      millisOver = millis() - (millisOnStart + seconds*1000);
    }
    
  }
  else
  { 
    if(isButtonPressed(GREEN_BUTTON, green_debounced_button_state, green_previous_reading, green_last_change_time))
    {
      timerGoing = true;
      millisOnStart = millis() - (seconds*1000 + millisOver);
    }
  }

  if (isButtonPressed(RED_BUTTON, red_debounced_button_state, red_previous_reading, red_last_change_time))
  {
    timerGoing = false;
    seconds = 0;
    millisOver = 0;
    lcd.clear();
    lcd.print(0);
  }  
}