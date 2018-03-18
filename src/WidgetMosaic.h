#pragma once

#include "Widget.h"
#include "Point.h"

namespace Codingfield {
  namespace UI {
    class WidgetMosaic : public Widget {
    public:
      WidgetMosaic(Widget* parent, Point position, Size size, int32_t nbColumns = 3, int32_t nbRows = 2);
      void Draw() override;
      virtual void AddChild(Widget* widget) override;
      virtual void OnButtonAPressed() override;
      virtual void OnButtonBPressed() override;
      virtual void OnButtonCPressed() override;
    private:
      int32_t indexSelected = 0;
      int32_t border = 5;
      int32_t nbRows;
      int32_t nbColumns;

      Size ComputeWidgetSize();
      Point ComputeWidgetPosition(const Size& widgetSize, int32_t position);
    };
  }
}
