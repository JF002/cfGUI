#pragma once

#include <Screen.h>

namespace Codingfield {
  namespace UI {
    class Bar;
    class AppScreen : public Screen {
    public:
      AppScreen(Size size, Color color);
      AppScreen(Size size, Color color, Bar* topBar, Bar* bottomBar, Widget* centreWidget);

      virtual void OnButtonAPressed() override;
      virtual void OnButtonBPressed() override;
      virtual void OnButtonBLongPush() override;
      virtual void OnButtonCPressed() override;

    private:
      Bar* topBar = nullptr;
      Bar* bottomBar = nullptr;
      Widget* centreWidget = nullptr;
      int32_t padding = 5;
      int32_t barHeight = 25;
    };
  }
}
