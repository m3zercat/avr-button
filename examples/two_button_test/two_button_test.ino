#define BUTTON_MAX_PRESSES 3
#define BUTTON_MAX_HOLDS 1
#include <button.h>

Button *b = new Button(5, true);
Button *b2 = new Button(6, true);

void oneClick()
{
  Serial.println("One Click");
}

void doubleClick()
{
  Serial.println("Double Click");
}

void trebbleClick()
{
  Serial.println("Trebble Click");
}

void holdPush()
{
  Serial.println("Holding");
}

void setup() {
  Serial.begin(9600);
  b->SetClickAction(1, oneClick);
  b->SetClickAction(2, doubleClick);
  b->SetClickAction(3, trebbleClick);
  b->SetHoldAction(1, holdPush);
  b->Setup();
  b2->SetClickAction(1, oneClick);
  b2->SetClickAction(2, doubleClick);
  b2->SetClickAction(3, trebbleClick);
  b2->SetHoldAction(1, holdPush);
  b2->Setup();
  Serial.println("ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  b->Pulse();
  b2->Pulse();
}