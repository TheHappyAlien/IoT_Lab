#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

int led_color = LED_RED;
bool green_button_pressed = false;
bool red_button_pressed = false;
bool led_on = true;

void initRGB()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, LOW);
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

void setup()
{
  initRGB();
  initButtons();

}

void loop()
{
  if (!red_button_pressed && digitalRead(RED_BUTTON) == LOW)
  {
    led_on = !led_on;
    red_button_pressed = true;
  }

  if (!green_button_pressed && digitalRead(GREEN_BUTTON) == LOW){
    digitalWrite(led_color, LOW);     
    switch (led_color){
      case LED_RED:
        led_color = LED_GREEN;
        break;
      case LED_GREEN:
        led_color = LED_BLUE;
        break;
      case LED_BLUE:
        led_color = LED_RED;
        break;                 
    }  
    green_button_pressed = true;   
  } 
  

  if (green_button_pressed && digitalRead(GREEN_BUTTON) == HIGH)
    green_button_pressed = false;  

  if (red_button_pressed && digitalRead(RED_BUTTON) == HIGH)
    red_button_pressed = false;

  if (led_on)
    digitalWrite(led_color, HIGH);
  else
    digitalWrite(led_color, LOW);   
}


