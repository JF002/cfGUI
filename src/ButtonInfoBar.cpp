#include "ButtonInfoBar.h"

using namespace Codingfield::UI;

void ButtonInfoBar::SetButtonAText(const std::string& t) {
  if(btnAText != t) {
    oldBtnAText = btnAText;
    btnAText = t;
  }
}

void ButtonInfoBar::SetButtonBText(const std::string& t) {
  if(btnBText != t) {
    oldBtnBText = btnBText;
    btnBText = t;
  }
}

void ButtonInfoBar::SetButtonCText(const std::string& t) {
  if(btnCText != t) {
    oldBtnCText = btnCText;
    btnCText = t;
  }
}

void ButtonInfoBar::Draw() {
  if(IsHidden()) return;
  bool oldIsInvalidated = isInvalidated;
  Bar::Draw();

  if(oldIsInvalidated || (oldBtnAText != btnAText)) {
    M5.Lcd.setTextDatum(TC_DATUM);
    M5.Lcd.setTextColor(color);
    M5.Lcd.drawString(oldBtnAText.c_str(), (size.width/6), position.y + 5);
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.drawString(btnAText.c_str(), (size.width/6), position.y + 5);

    oldBtnAText = btnAText;
  }

  if(oldIsInvalidated || (oldBtnBText != btnBText)) {
    M5.Lcd.setTextDatum(TC_DATUM);
    M5.Lcd.setTextColor(color);
    M5.Lcd.drawString(oldBtnBText.c_str(), size.width/2, position.y + 5);
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.drawString(btnBText.c_str(), size.width/2, position.y + 5);

    oldBtnBText = btnBText;
  }

  if(oldIsInvalidated || (oldBtnCText != btnCText)) {
    M5.Lcd.setTextDatum(TC_DATUM);
    M5.Lcd.setTextColor(color);
    M5.Lcd.drawString(oldBtnCText.c_str(), ((size.width/3)*2) + (size.width/6), position.y + 5);
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.drawString(btnCText.c_str(), ((size.width/3)*2) + (size.width/6), position.y + 5);

    oldBtnCText = btnCText;
  }
  isInvalidated = false;
}
