#include "Screen.h"
#include "Free_Fonts.h"

using namespace Codingfield::UI;

void Screen::Draw() {
  M5.Lcd.setFreeFont(FF21);
  M5.Lcd.setTextSize(1);

  if(IsHidden()) return;
  if(isInvalidated)
    M5.Lcd.fillScreen(color);

  for(Widget* w : children)
    w->Draw();

  isInvalidated = false;
}
