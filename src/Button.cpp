#include "Button.h"

using namespace Codingfield::UI;

/* Please, please, M5STack, use namespaces around your classes! */

Codingfield::UI::Button::Button(Widget* parent) : Widget(parent) {

}

Codingfield::UI::Button::Button(Widget* parent, Point position, Size size) : Widget(parent, position, size) {

}

void Codingfield::UI::Button::SetBackgroundColor(Color c) {
  this->backgroundColor = c;
}

void Codingfield::UI::Button::SetTextColor(Color c) {
  this->textColor = c;
}

void Codingfield::UI::Button::SetSelected(bool s) {
  if(isSelected != s) {
    isSelected = s;
    isUpdated = true;
  }
}

void Codingfield::UI::Button::SetText(const std::string& t) {
  if(text != t) {
    this->text = t;
    isUpdated = true;
  }
}

void Codingfield::UI::Button::SetTitle(const std::string& t) {
  if(title != t) {
    title = t;
    isUpdated = true;
  }
}

void Codingfield::UI::Button::Draw() {
  if(isUpdated) {
    M5.Lcd.setTextColor(textColor);
    M5.Lcd.setTextSize(2);

    M5.Lcd.fillRect(position.x, position.y, size.width, size.height, backgroundColor);
    M5.Lcd.setTextDatum(MC_DATUM);
    M5.Lcd.setTextColor(textColor);
    if(title.empty())
      M5.Lcd.drawString(text.c_str(), position.x + (size.width/2), position.y + (size.height/2));
    else {
      M5.Lcd.drawString(text.c_str(), position.x + (size.width/2), position.y + (size.height/3));
      M5.Lcd.drawString(title.c_str(), position.x + (size.width/2), position.y + ((size.height/3)*2));
    }

    if(isSelected) {
      M5.Lcd.drawRect(position.x, position.y, size.width, size.height, RED);
      M5.Lcd.drawRect(position.x+1, position.y+1, size.width-2, size.height-2, RED);
      M5.Lcd.drawRect(position.x+2, position.y+2, size.width-4, size.height-4, RED);
    }
  }
  isUpdated = false;
}
