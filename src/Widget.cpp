#include "Widget.h"


using namespace Codingfield::UI;

Widget::Widget(Widget* parent) : Widget(parent, Point(0,0), Size(0,0)) {
}

Widget::Widget(Widget* parent, Point position, Size size) :  parent{parent}, position{position}, size {size} {
  if(parent != nullptr)
    parent->AddChild(this);
}

void Widget::Invalidate() {
  for(auto c : children) {
    c->Invalidate();
  }
  isInvalidated = true;
}

void Widget::SetSize(const Size& s) {
  size = s;
  OnSizeUpdated();
}

void Widget::SetPosition(const Point& p) {
  position = p;
  OnPositionUpdated();
}
