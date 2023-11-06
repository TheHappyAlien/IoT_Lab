#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3


void initRGB()
{
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}


void setup()
{
  Serial.begin(9600);
  while (!Serial)
  { /* just wait */
  }
  initRGB();
  Serial.print("");
}



void loop()
{
  String command = Serial.readStringUntil('\n');
  if(command.equals("")){
      return;
  }

  Serial.println(command);

  command.trim();
  command.toLowerCase();


  if(command.substring(0, 4).equals("rgb("))
  {
    short red = -1;
    short green = -1;
    short blue = -1;
    int endIndex = 4;
    String substring = "";

    command = command.substring(endIndex);
    endIndex = command.indexOf(',');
    substring = command.substring(0, endIndex);
    substring.trim();
    red = substring.toInt();

    command = command.substring(endIndex + 1);
    endIndex = command.indexOf(',');
    substring = command.substring(0, endIndex);
    substring.trim();
    green = substring.toInt();

    command = command.substring(endIndex + 1);
    endIndex = command.indexOf(')');
    substring = command.substring(0, endIndex);
    substring.trim();
    blue = substring.toInt();

    if(red >= 0 && red <= 255 && green >= 0 && green <= 255 && blue >= 0 && blue <= 255)
    {
      digitalWrite(LED_RED, red);
      digitalWrite(LED_GREEN, green);
      digitalWrite(LED_BLUE, blue);
    }
    else{
      Serial.println("Wrong command format, should be like: rgb(r,g,b) - r,g,b being integers between 0 and 255.");
    }
  }
  else{
    Serial.println("Wrong command format, should be like: rgb(r,g,b) - r,g,b being integers between 0 and 255.");
  }
}
