#include "WidgetMosaic.h"

using namespace Codingfield::UI;

WidgetMosaic::WidgetMosaic(Widget* parent, Point position, Size size) : Widget(parent, position, size) {

}

void WidgetMosaic::Draw() {
  for(Widget* w : children) {
    w->Draw();
  }
}

void WidgetMosaic::AddChild(Widget* widget) {
  Widget::AddChild(widget);
  widget->SetSize(Size(100,88));
  switch(children.size()) {
    case 1: widget->SetPosition(Point(5,30)); break;
    case 2: widget->SetPosition(Point(110,30)); break;
    case 3: widget->SetPosition(Point(215,30)); break;
    case 4: widget->SetPosition(Point(5,122)); break;
    case 5: widget->SetPosition(Point(110,122)); break;
    case 6: widget->SetPosition(Point(215,122)); break;
    default: break;
  }
}

void WidgetMosaic::OnButtonAPressed() {
  if(indexSelected > 0) {
    children[indexSelected]->SetSelected(false);
    indexSelected--;
    children[indexSelected]->SetSelected(true);
  }
}

void WidgetMosaic::OnButtonBPressed() {

}

void WidgetMosaic::OnButtonCPressed() {
  if(indexSelected < children.size()-1) {
    children[indexSelected]->SetSelected(false);
    indexSelected++;
    children[indexSelected]->SetSelected(true);
  }
}
