#include "Screen.h"

using namespace Codingfield::UI;

void Screen::Draw() {
  if(isUpdated)
    M5.Lcd.fillScreen(color);

  for(Widget* w : children)
    w->Draw();

  isUpdated = false;
}
