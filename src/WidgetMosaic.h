#pragma once

#include "Widget.h"
#include "Point.h"

namespace Codingfield {
  namespace UI {
    class WidgetMosaic : public Widget {
    public:
      WidgetMosaic(int32_t nbColumns = 3, int32_t nbRows = 2);
      WidgetMosaic(Widget* parent, Point position, Size size, int32_t nbColumns = 3, int32_t nbRows = 2);
      void Draw() override;
      virtual void AddChild(Widget* widget) override;
      virtual void OnButtonAPressed() override;
      virtual void OnButtonBPressed() override;
      virtual void OnButtonBLongPush() override;
      virtual void OnButtonCPressed() override;
      const Widget* GetSelected() const;
      bool IsZoomOnSelected() const;
      void SetZoomOnSelectedCallback(std::function<void (Widget* widget, bool)> func);
    private:
      int32_t indexSelected = 0;
      int32_t border = 5;
      int32_t nbColumns;
      int32_t nbRows;

      Size ComputeWidgetSize();
      Size ComputeWidgetSize(int32_t nbColumns, int32_t nbRows);
      Point ComputeWidgetPosition(const Size& widgetSize, int32_t position);
      Widget* selectedWidget = nullptr;
      bool zoomOnSelected = false;
      void ZoomOnSelected(bool enabled);
      std::function<void (Widget* widget, bool)> zoomOnSelectedCallback = nullptr;
    };
  }
}
