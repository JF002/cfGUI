#include "UpDownButton.h"
#include "Free_Fonts.h"
using namespace Codingfield::UI;

UpDownButton::UpDownButton(Widget* parent) : Button(parent) {
  isEditable = true;
}

void UpDownButton::Draw() {
  if(IsHidden()) return;

  if(isUpdated) {
    Button::Draw();
    if(controlsEnabled) {
      M5.Lcd.setTextDatum(MC_DATUM);
      M5.Lcd.setTextColor(textColor);
      M5.Lcd.drawString("-", position.x + (size.width/6), position.y + (size.height/2));
      M5.Lcd.drawString("+", position.x + (size.width - (size.width/6)), position.y + (size.height/2));
    }
  }

  isUpdated = false;
}

void UpDownButton::EnableControls()  {
  controlsEnabled = true;
}

void UpDownButton::DisableControls() {
  controlsEnabled = false;
}

void UpDownButton::OnButtonAPressed() {
  if(upCallback != nullptr) {
    if(downCallback(this))
      SetUpdateFlag();
  }
}

void UpDownButton::OnButtonBPressed() {
  if(applyCallback != nullptr) {
    if(applyCallback(this))
      SetUpdateFlag();
  }
}

void UpDownButton::OnButtonBLongPush() {
  if(cancelCallback != nullptr) {
    if(cancelCallback(this))
      SetUpdateFlag();
  }
}

void UpDownButton::OnButtonCPressed() {
  if(upCallback != nullptr) {
    if(upCallback(this))
      SetUpdateFlag();
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
