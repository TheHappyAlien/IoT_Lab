#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4


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

short luminocity_1 = 255;
short luminocity_2 = 0;
short first_color = LED_RED;
short second_color = LED_GREEN;

void setup()
{
  initRGB();
  initButtons();
}

void loop()
{
  analogWrite(first_color, luminocity_1);
  analogWrite(second_color, luminocity_2);

  luminocity_1--;
  luminocity_2++;

  if (luminocity_1 == 0){
    luminocity_1 = 255;
    luminocity_2 = 0;

    switch (first_color){
      case LED_RED:
        first_color = LED_GREEN;
        second_color = LED_BLUE;
        break;

      case LED_GREEN:
        first_color = LED_BLUE;
        second_color = LED_RED;
        break;

      case LED_BLUE:
        first_color = LED_RED;
        second_color = LED_GREEN;
        break;      
    }
  }

  delay(5);
}