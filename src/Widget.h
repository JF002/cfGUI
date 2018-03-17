#pragma once

#include "Point.h"
#include "Size.h"
#include <M5Stack.h>

namespace Codingfield {
  namespace UI {
    using Color = uint32_t;
    class Widget {
    public:
      Widget(Widget* parent);
      Widget(Widget* parent, Point position, Size size);

      Widget(Point position, Size size) : Widget(nullptr, position, size) {}

      const Size& GetSize() const { return size; }
      void SetSize(const Size& s) { size = s; }

      const Point& GetPosition() const {return position; }
      void SetPosition(const Point& p) {position = p; }

      virtual void AddChild(Widget* widget) { children.push_back(widget); }

      virtual void Draw() = 0;

      virtual void OnButtonAPressed() { }

      virtual void OnButtonBPressed() { }

      virtual void OnButtonCPressed() { }

      virtual void SetSelected(bool s) { }

    protected:
      Point position;
      Size size;
      Widget* parent = nullptr;
      std::vector<Widget*> children;
      bool isSelected = false;
      bool isUpdated = true;
    };

  }
}
