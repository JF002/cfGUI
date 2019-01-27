#include "UpDownButton.h"
#include "Free_Fonts.h"
using namespace Codingfield::UI;

UpDownButton::UpDownButton(Widget* parent) : Button(parent) {
  isEditable = true;
}

void UpDownButton::Draw() {
  if(IsHidden()) return;

  bool wasInvalidated = isInvalidated;
  Button::Draw();

  if(wasInvalidated) {
    if(controlsEnabled) {
      M5.Lcd.setTextDatum(MC_DATUM);
      M5.Lcd.setTextColor(textColor);
      M5.Lcd.drawString("-", position.x + (size.width/6), position.y + (size.height/2));
      M5.Lcd.drawString("+", position.x + (size.width - (size.width/6)), position.y + (size.height/2));
    }
  }
}

void UpDownButton::EnableControls()  {
  controlsEnabled = true;
}

void UpDownButton::DisableControls() {
  controlsEnabled = false;
}

void UpDownButton::OnButtonAPressed() {
  if(upCallback != nullptr) {
    downCallback(this);
  }
}

void UpDownButton::OnButtonBPressed() {
  if(applyCallback != nullptr) {
    applyCallback(this);
  }
}

void UpDownButton::OnButtonBLongPush() {
  if(cancelCallback != nullptr) {
    cancelCallback(this);
  }
}

void UpDownButton::OnButtonCPressed() {
  if(upCallback != nullptr) {
    upCallback(this);
  }
}

void UpDownButton::SetUpCallback(std::function<bool (UpDownButton* widget)> callback) {
  upCallback = callback;
}

void UpDownButton::SetDownCallback(std::function<bool (UpDownButton* widget)> callback) {
  downCallback = callback;
}

void UpDownButton::SetApplyCallback(std::function<bool (UpDownButton* widget)> callback) {
  applyCallback = callback;
}

void UpDownButton::SetCancelCallback(std::function<bool (UpDownButton* widget)> callback) {
  cancelCallback = callback;
}
