#include "WidgetMosaic.h"
#include <String>
using namespace Codingfield::UI;

WidgetMosaic::WidgetMosaic(Widget* parent, Point position, Size size, int32_t nbColumns, int32_t nbRows) : Widget(parent, position, size),
                                                                                                           nbColumns {nbColumns},
                                                                                                           nbRows {nbRows} {

}

void WidgetMosaic::Draw() {
  for(Widget* w : children)
    w->Draw();
}

void WidgetMosaic::AddChild(Widget* widget) {
  Widget::AddChild(widget);

  Size widgetSize = ComputeWidgetSize();
  widget->SetSize(widgetSize);

  int32_t position = ((children.size()-1) % (nbRows*nbColumns));
  widget->SetPosition(ComputeWidgetPosition(widgetSize, position));
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

Size WidgetMosaic::ComputeWidgetSize() {
  Size widgetSize;
  widgetSize.width = (size.width - ((2*border) + ((nbColumns-1)*border))) / nbColumns;
  widgetSize.height = (size.height - ((2*border) + ((nbRows-1)*border))) / nbRows;

  String str = String(widgetSize.width) + "x" + String(widgetSize.height);
  Serial.println("Mosaic size = " + str);
  return widgetSize;
}

Point WidgetMosaic::ComputeWidgetPosition(const Size& widgetSize, int32_t position) {
  Point widgetPosition;

  int32_t row = ((int32_t)position / (int32_t)nbColumns);
  int32_t column = position % nbColumns;
  widgetPosition.x = ((column)*border) + (column * widgetSize.width) + this->position.x;
  widgetPosition.y = ((row)*border) + (row * widgetSize.height) + this->position.y;

  return widgetPosition;
}
