#pragma once

#include "Bar.h"

namespace Codingfield {
  namespace UI {
    class ButtonInfoBar : public Bar {
    public:
      ButtonInfoBar() : Bar() {}
      ButtonInfoBar(Widget* parent, Point position, int32_t height) : Bar(parent, position, height) {}
      void Draw() override;
      void SetButtonAText(const std::string& t);
      void SetButtonBText(const std::string& t);
      void SetButtonCText(const std::string& t);
    private:
      Color color = WHITE;
      std::string btnAText;
      std::string btnBText;
      std::string btnCText;
    };
  }
}
