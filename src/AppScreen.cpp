#include "AppScreen.h"
#include <Bar.h>

using namespace Codingfield::UI;

AppScreen::AppScreen(Size size, Color color) : Screen(size, color) {

}

AppScreen::AppScreen(Size size, Color color, Bar* topBar, Bar* bottomBar, Widget* centreWidget) : Screen(size, color), topBar{topBar}, bottomBar{bottomBar}, centreWidget{centreWidget} {
  if(topBar != nullptr) {
    topBar->SetParent(this);
    topBar->SetPosition(Point(0,0));
    topBar->SetSize(Size(this->GetSize().width, barHeight));
    AddChild(topBar);
  }

  if(bottomBar != nullptr) {
    bottomBar->SetParent(this);
    bottomBar->SetPosition(Point(0, this->GetSize().height-barHeight));
    bottomBar->SetSize(Size(this->GetSize().width, barHeight));
    AddChild(bottomBar);
  }

  if(centreWidget != nullptr) {
    Point centerPosition;
    centerPosition.y = position.y + ((topBar != nullptr) ? topBar->GetSize().height : 0) + padding;
    centerPosition.x = position.x + padding;

    Size centerSize;
    centerSize.height = size.height - (((bottomBar != nullptr) ? bottomBar->GetSize().height : 0) + ((topBar != nullptr) ? topBar->GetSize().height : 0) + padding);
    centerSize.width = size.width;

    centreWidget->SetParent(this);
    centreWidget->SetPosition(centerPosition);
    centreWidget->SetSize(centerSize);
    AddChild(centreWidget);
  }
}

void AppScreen::OnButtonAPressed() {
  if(centreWidget != nullptr)
    centreWidget->OnButtonAPressed();
}

void AppScreen::OnButtonBPressed() {
  if(centreWidget != nullptr)
    centreWidget->OnButtonBPressed();
}

void AppScreen::OnButtonBLongPush() {
  if(centreWidget != nullptr)
    centreWidget->OnButtonBLongPush();
}

void AppScreen::OnButtonCPressed() {
  if(centreWidget != nullptr)
    centreWidget->OnButtonCPressed();
}
