#pragma once

#include "Widget.h"

namespace Codingfield {
  namespace UI {
    class Bar : public Widget {
    public:
      Bar(Widget* parent, Point position, int32_t height) : Widget(parent, position, Size(parent->GetSize().width, height)) {}
      void Draw() override;
    private:
      Color color = WHITE;
    };
  }
}
