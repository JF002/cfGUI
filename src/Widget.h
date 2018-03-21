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

      void SetParent(Widget* parent) { this->parent = parent; }
      const Size& GetSize() const { return size; }
      void SetSize(const Size& s) { size = s; }

      const Point& GetPosition() const {return position; }
      void SetPosition(const Point& p) {position = p; }

      void Show() { SetUpdateFlag(); isVisible = true; }
      void Hide() { SetUpdateFlag(); isVisible = false; }
      bool IsVisible() const { return isVisible;}
      bool IsHidden() const { return !isVisible;}

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
      bool isVisible = true;

      void SetUpdateFlag();
    };

  }
}
