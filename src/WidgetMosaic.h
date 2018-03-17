#pragma once

#include "Widget.h"

namespace Codingfield {
  namespace UI {
    class WidgetMosaic : public Widget {
    public:
      WidgetMosaic(Widget* parent, Point position, Size size);
      void Draw() override;
      virtual void AddChild(Widget* widget) override;
      virtual void OnButtonAPressed() override;
      virtual void OnButtonBPressed() override;
      virtual void OnButtonCPressed() override;
    private:
      int32_t indexSelected = 0;
    };
  }
}
