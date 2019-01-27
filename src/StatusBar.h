#pragma once

#include "Bar.h"

namespace Codingfield {
  namespace UI {
    class StatusBar : public Bar {
    public:
      enum class WifiStatuses {Unknown, No_signal, Weak, Medium, Full};
      StatusBar() : Bar() {}
      StatusBar(Widget* parent, Point position, int32_t height) : Bar(parent, position, height) {}
      void Draw() override;
      void SetWifiStatus(const WifiStatuses status);
      void SetUptime(const uint32_t t);
      void SetDateTime(const std::string& t);

    private:
      Color color = WHITE;
      WifiStatuses wifiStatus = WifiStatuses::No_signal;
      WifiStatuses oldWifiStatus = WifiStatuses::Unknown;
      uint32_t uptime = 0;
      uint32_t oldUptime = UINT32_MAX;
      std::string dateTime;
      std::string oldDateTime;
    };
  }
}
