#include "Button.h"
#include "Free_Fonts.h"

using namespace Codingfield::UI;

/* Please, please, M5STack, use namespaces around your classes! */

Codingfield::UI::Button::Button(Widget* parent) : Widget(parent) {

}

Codingfield::UI::Button::Button(Widget* parent, Point position, Size size) : Widget(parent, position, size) {

}

void Codingfield::UI::Button::SetBackgroundColor(Color c) {
  backgroundColorUpdated = true;
  this->backgroundColor = c;
}

void Codingfield::UI::Button::SetTextColor(Color c) {
  this->textColor = c;
}

void Codingfield::UI::Button::SetSelected(bool s) {
  if(isSelected != s) {
    wasSelected = isSelected;
    isSelected = s;
    SetUpdateFlag();
  }
}

void Codingfield::UI::Button::SetText(const std::string& t) {
  if(text != t) {
    if(text.empty())
      oldText = t;
    else
      this->oldText = this->text;
    this->text = t;
    SetUpdateFlag();
  }
}

void Codingfield::UI::Button::SetTitle(const std::string& t) {
  if(title != t) {
    if(title.empty())
      oldTitle = t;
    else
      oldTitle = title;
    title = t;
    SetUpdateFlag();
  }
}

void Codingfield::UI::Button::Draw() {
  if(IsHidden()) return;
  if(true) {
    bool forceUpdate = false;
    int x = position.x + (size.width/2);
    int yText;
    int yTitle;
    if(title.empty()) {
      yText = position.y + (size.height/2);
    } else {
      yText = position.y + (size.height/3);
      yTitle = position.y + ((size.height/3)*2);
    }

    if(backgroundColorUpdated) {
      M5.Lcd.fillRect(position.x, position.y, size.width, size.height, backgroundColor);
      backgroundColorUpdated = false;
      forceUpdate = true;
    }

    if(forceUpdate || (oldText != text)) {
      M5.Lcd.setTextDatum(MC_DATUM);
      M5.Lcd.setTextColor(backgroundColor);

      M5.Lcd.setFreeFont(FF22);
      M5.Lcd.drawString(oldText.c_str(), x, yText);

      M5.Lcd.setTextColor(textColor);
      M5.Lcd.drawString(text.c_str(), x, yText);
      oldText = text;
    }

    if(forceUpdate || (oldTitle != title)) {
      M5.Lcd.setTextDatum(MC_DATUM);
      M5.Lcd.setTextColor(backgroundColor);

      M5.Lcd.setFreeFont(FF21);
      M5.Lcd.drawString(oldTitle.c_str(), x, yTitle);

      M5.Lcd.setTextColor(textColor);
      M5.Lcd.drawString(title.c_str(), x, yTitle);
      oldTitle = title;
    }

    if(wasSelected != isSelected) {
      if(isSelected) {
        M5.Lcd.drawRect(position.x, position.y, size.width, size.height, RED);
        M5.Lcd.drawRect(position.x+1, position.y+1, size.width-2, size.height-2, RED);
        M5.Lcd.drawRect(position.x+2, position.y+2, size.width-4, size.height-4, RED);
      } else {
        M5.Lcd.drawRect(position.x, position.y, size.width, size.height, backgroundColor);
        M5.Lcd.drawRect(position.x + 1, position.y + 1, size.width - 2, size.height - 2, backgroundColor);
        M5.Lcd.drawRect(position.x + 2, position.y + 2, size.width - 4, size.height - 4, backgroundColor);
      }
    }
  }
  isUpdated = false;
}
