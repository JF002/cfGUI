#include "Bar.h"

using namespace Codingfield::UI;

void Bar::Draw() {
  if(IsHidden()) return;
  if(isUpdated)
    M5.Lcd.fillRect(position.x, position.y, size.width, size.height, WHITE);

  isUpdated = false;
}
