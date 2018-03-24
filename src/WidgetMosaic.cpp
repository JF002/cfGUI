#include "WidgetMosaic.h"
#include <String>
using namespace Codingfield::UI;

WidgetMosaic::WidgetMosaic(Widget* parent, Point position, Size size, int32_t nbColumns, int32_t nbRows) : Widget(parent, position, size),
                                                                                                           nbColumns {nbColumns},
                                                                                                           nbRows {nbRows} {

}

WidgetMosaic::WidgetMosaic(int32_t nbColumns, int32_t nbRows) : WidgetMosaic(nullptr, Point(), Size(), nbColumns, nbRows) {

}

void WidgetMosaic::Draw() {
  if(IsHidden()) return;
  if(isUpdated) {
    M5.Lcd.fillRect(position.x, position.y, size.width, size.height, BLACK);
  }

  if(!zoomOnSelected) {
    for(Widget* w : children)
      w->Draw();
  }
  else {
    selectedWidget->Draw();
  }

  isUpdated = false;
}

void WidgetMosaic::AddChild(Widget* widget) {
  Widget::AddChild(widget);

  Size widgetSize = ComputeWidgetSize();
  widget->SetSize(widgetSize);

  int32_t position = ((children.size()-1) % (nbRows*nbColumns));
  widget->SetPosition(ComputeWidgetPosition(widgetSize, position));
  SetUpdateFlag();
}

const Widget* WidgetMosaic::GetSelected() const {
  return selectedWidget;
}

void WidgetMosaic::ZoomOnSelected(bool enabled) {
  bool oldValue = zoomOnSelected;
  if(selectedWidget != nullptr && enabled) {
    zoomOnSelected = true;
    Size widgetSize = ComputeWidgetSize(1,1);
    selectedWidget->SetSize(widgetSize);
    selectedWidget->SetPosition(ComputeWidgetPosition(widgetSize, 0));
  }  else {
    zoomOnSelected = false;

    for(auto index = 0; index < children.size(); index++) {
      Widget* widget = children.at(index);
      Size widgetSize = ComputeWidgetSize();
      widget->SetSize(widgetSize);
      widget->SetPosition(ComputeWidgetPosition(widgetSize, index));
    }
  }

  if(oldValue != zoomOnSelected)
    SetUpdateFlag();
}

void WidgetMosaic::OnButtonAPressed() {
  if(zoomOnSelected)
    return selectedWidget->OnButtonAPressed();

  if(indexSelected > 0) {
    children[indexSelected]->SetSelected(false);
    indexSelected--;
    children[indexSelected]->SetSelected(true);
    selectedWidget = children[indexSelected];
  }
}

void WidgetMosaic::OnButtonBPressed() {
  if(zoomOnSelected)
    return selectedWidget->OnButtonBPressed();

  ZoomOnSelected(true);
}

void WidgetMosaic::OnButtonBLongPush() {
  ZoomOnSelected(false);
}

void WidgetMosaic::OnButtonCPressed() {
  if(zoomOnSelected)
    return selectedWidget->OnButtonCPressed();

  if(indexSelected < children.size()-1) {
    children[indexSelected]->SetSelected(false);
    indexSelected++;
    children[indexSelected]->SetSelected(true);
    selectedWidget = children[indexSelected];
  }
}

Size WidgetMosaic::ComputeWidgetSize() {
  return ComputeWidgetSize(nbColumns, nbRows);
}

Size WidgetMosaic::ComputeWidgetSize(int32_t nbColumns, int32_t nbRows) {
  Size widgetSize;
  widgetSize.width = (size.width - ((2*border) + ((nbColumns-1)*border))) / nbColumns;
  widgetSize.height = (size.height - ((2*border) + ((nbRows-1)*border))) / nbRows;
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
