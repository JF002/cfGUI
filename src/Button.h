#pragma once

#include "Widget.h"

namespace Codingfield {
  namespace UI {
    class Button : public Widget {
    public:
      Button(Widget* parent);
      Button(Widget* parent, Point position, Size size);
      void SetBackgroundColor(Color c);
      void SetTextColor(Color c);
      virtual void SetSelected(bool s) override;
      void SetText(const std::string& t);
      void SetTitle(const std::string& t);
      void Draw() override;
    protected:
      Color backgroundColor = BLACK;
      bool backgroundColorUpdated = true;
      Color textColor = BLACK;
      std::string text;
      std::string oldText;
      std::string title;
      std::string oldTitle;
      bool wasSelected = false;
    };
  }
}
