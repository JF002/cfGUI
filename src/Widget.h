#pragma once

#include "Point.h"
#include "Size.h"
#include <M5Stack.h>

namespace Codingfield {
  namespace UI {
    using Color = uint32_t;

    /* Base class for all widgets
     * A widget is an object that has a parent widget, children, a position and a size,
     * and is able to draw itself on the screen.*/
    class Widget {
    public:
      Widget(Widget* parent);
      Widget(Widget* parent, Point position, Size size);

      void SetParent(Widget* parent) { this->parent = parent; }

      const Size& GetSize() const { return size; }
      void SetSize(const Size& s);

      const Point& GetPosition() const {return position; }
      void SetPosition(const Point& p);

      /* The widget will be visible (drawn) the next time Draw() will be called */
      void Show() { SetUpdateFlag(); isVisible = true; }

      /* The widget will not be visible (not drawn) the next time Draw() will be called */
      void Hide() { SetUpdateFlag(); isVisible = false; }

      bool IsVisible() const { return isVisible;}
      bool IsHidden() const { return !isVisible;}

      /* Returns true if the value of the widget can be edited via buttons */
      bool IsEditable() const { return isEditable; }

      /* Add a widget as a child of this one */
      virtual void AddChild(Widget* widget) { children.push_back(widget); }

      /* Draw the widget. Implemented by concrete implementations of Widget */
      virtual void Draw() = 0;

      /* These methods must be called by the application when buttons are pressed
       * They allow the implementation of Widget to react to user actions on
       * physical buttons. */
      virtual void OnButtonAPressed() { }
      virtual void OnButtonBPressed() { }
      virtual void OnButtonBLongPush() { }
      virtual void OnButtonCPressed() { }

      /* This method must be called by the application to specify is this instance
       * of Widget is selected or not. */
      virtual void SetSelected(bool s) { }

      /* Enables/disables controls on the button */
      virtual void EnableControls() {}
      virtual void DisableControls() {}

    protected:
      virtual void OnSizeUpdated() { }
      virtual void OnPositionUpdated() { }
      void SetUpdateFlag();

      Point position;
      Size size;
      Widget* parent = nullptr;
      std::vector<Widget*> children;
      bool isSelected = false;
      bool isUpdated = true;
      bool isVisible = true;
      bool isEditable = false;
    };
  }
}
