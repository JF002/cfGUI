#include "ButtonInfoBar.h"

using namespace Codingfield::UI;

void ButtonInfoBar::SetButtonAText(const std::string& t) {
  if(btnAText != t) {
    btnAText = t;
    isUpdated = true;
  }
}

void ButtonInfoBar::SetButtonBText(const std::string& t) {
  if(btnBText != t) {
    btnBText = t;
    isUpdated = true;
  }
}

void ButtonInfoBar::SetButtonCText(const std::string& t) {
  if(btnCText != t) {
    btnCText = t;
    isUpdated = true;
  }
}

void ButtonInfoBar::Draw() {
  bool oldIsUpdated = isUpdated;
  Bar::Draw();

  if(oldIsUpdated) {
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setTextSize(2);

    M5.Lcd.setTextDatum(TC_DATUM);
    M5.Lcd.drawString(btnAText.c_str(), (size.width/6), position.y + 5);

    M5.Lcd.setTextDatum(TC_DATUM);
    M5.Lcd.drawString(btnBText.c_str(), size.width/2, position.y + 5);

    M5.Lcd.setTextDatum(TC_DATUM);
    M5.Lcd.drawString(btnCText.c_str(), ((size.width/3)*2) + (size.width/6), position.y + 5);
  }
  isUpdated = false;
}
