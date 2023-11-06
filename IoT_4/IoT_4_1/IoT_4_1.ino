  #define BUTTON_RED 4
#define BUTTON_GREEN 2

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  { /* just wait */
  }

  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
}

void loop()
{
  String str = String(digitalRead(BUTTON_RED)) + " " + String(digitalRead(BUTTON_GREEN));
  Serial.println(str);
}