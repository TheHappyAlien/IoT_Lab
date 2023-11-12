#include <LedController.h>

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

LedController controller;

void setup() {
  controller.init(LED_RED, LED_GREEN, LED_BLUE);
}

void loop() {
  controller.setColor(RED);
  delay(700);
  controller.setColor(GREEN);
  delay(700);
  controller.setColor(BLUE);
  delay(700);
  controller.setColor(YELLOW);
  delay(700);
  controller.setColor(CYAN);
  delay(700);
  controller.setColor(MAGENTA);
  delay(700);
  controller.setColor(BLACK);
  delay(700);
  controller.setColor(WHITE);
  delay(700);
  controller.setColor(0, 50, 200);
  delay(700);
}