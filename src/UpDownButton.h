#pragma once

#include "Button.h"

namespace Codingfield {
  namespace UI {
    class UpDownButton : public Button {
    public:
      UpDownButton(Widget* parent);
      virtual void Draw();

      virtual void EnableControls() override;
      virtual void DisableControls() override;

      virtual void OnButtonAPressed() override;
      virtual void OnButtonBPressed() override;
      virtual void OnButtonBLongPush() override;
      virtual void OnButtonCPressed() override;

      void SetUpCallback(std::function<bool (UpDownButton* widget)> callback);
      void SetDownCallback(std::function<bool (UpDownButton* widget)> callback);
      void SetApplyCallback(std::function<bool (UpDownButton* widget)> callback);
      void SetCancelCallback(std::function<bool (UpDownButton* widget)> callback);

    private:
      bool controlsEnabled = false;
      int32_t currentValue = 0;
      int32_t oldValue = 0;

      std::function<bool (UpDownButton* widget)> upCallback = nullptr;
      std::function<bool (UpDownButton* widget)> downCallback = nullptr;
      std::function<bool (UpDownButton* widget)> applyCallback = nullptr;
      std::function<bool (UpDownButton* widget)> cancelCallback = nullptr;
    };
  }
}
