
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

short luminocity = 255;

void setup()
{
  initRGB();
  initButtons();
}

void loop()
{
  analogWrite(LED_GREEN, luminocity);

  if (digitalRead(GREEN_BUTTON) == LOW && luminocity < 255)
    luminocity++;
  
  if (digitalRead(RED_BUTTON) == LOW && luminocity > 0)
    luminocity--;

  delay(5);
}