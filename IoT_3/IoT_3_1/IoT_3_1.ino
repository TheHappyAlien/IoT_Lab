#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3
#define RED_BUTTON 2
#define GREEN_BUTTON 4
int led[] = {LED_RED, LED_GREEN, LED_BLUE};
void initRGB()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, HIGH);
  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_GREEN, LOW);
  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_BLUE, LOW);
}

void initButtons()
{
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
}
#define DEBOUNCE_PERIOD 10UL

bool isButtonReleased(int button, int& debounced_button_state, int& previous_reading, unsigned long& last_change_time)
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

void setup()
{
initRGB();
initButtons();
}

static int red_debounced_button_state = HIGH;
static int red_previous_reading = HIGH;
static unsigned long red_last_change_time = 0UL;

static int green_debounced_button_state = HIGH;
static int green_previous_reading = HIGH;
static unsigned long green_last_change_time = 0UL;

int led_index = 0;

void loop()
{
  if (isButtonReleased(GREEN_BUTTON, green_debounced_button_state, green_previous_reading, green_last_change_time) || isButtonReleased(RED_BUTTON, red_debounced_button_state, red_previous_reading, red_last_change_time))
  {
    digitalWrite(led[led_index], LOW);
    led_index = ++led_index % 3;
    digitalWrite(led[led_index], HIGH);
  }
}
