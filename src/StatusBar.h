#pragma once

#include "Bar.h"

namespace Codingfield {
  namespace UI {
    class StatusBar : public Bar {
    public:
      enum class WifiStatuses {No_signal, Weak, Medium, Full};
      StatusBar() : Bar() {}
      StatusBar(Widget* parent, Point position, int32_t height) : Bar(parent, position, height) {}
      void Draw() override;
      void SetWifiStatus(const WifiStatuses status);
      void SetUptime(const uint32_t t);
      void SetDateTime(const std::string& t);

    private:
      Color color = WHITE;
      WifiStatuses wifiStatus;
      uint32_t uptime;
      std::string dateTime;
    };
  }
}
