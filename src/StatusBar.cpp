#include "StatusBar.h"

using namespace Codingfield::UI;

extern const uint8_t image_data_wifi0[];
extern const uint8_t image_data_wifi1[];
extern const uint8_t image_data_wifi2[];
extern const uint8_t image_data_wifi3[];

void StatusBar::SetWifiStatus(const StatusBar::WifiStatuses status) {
  if(wifiStatus != status) {
    oldWifiStatus = wifiStatus;
    wifiStatus = status;
  }
}

void StatusBar::SetUptime(const uint32_t t) {
  if(uptime != t) {
    oldUptime = uptime;
    uptime = t;
  }
}

void StatusBar::SetDateTime(const std::string& t) {
  if(dateTime != t) {
    oldDateTime = dateTime;
    dateTime = t;
  }
}

void StatusBar::Draw() {
  if(IsHidden()) return;
  bool wasInvalidated = isInvalidated;
  Bar::Draw();

  if(wasInvalidated || (wifiStatus != oldWifiStatus)) {
    const uint8_t* wifibmp = image_data_wifi0;
    switch(wifiStatus) {
      case WifiStatuses::Weak: wifibmp = image_data_wifi1; break;
      case WifiStatuses::Medium: wifibmp = image_data_wifi2; break;
      case WifiStatuses::Full: wifibmp = image_data_wifi3; break;
      default:
      case WifiStatuses::No_signal:
        wifibmp = image_data_wifi0;
        break;
    }

    M5.Lcd.setBitmapColor(BLACK, color);
    M5.Lcd.pushImage(295, 0, 25, 25, const_cast<uint8_t*>(wifibmp), false);

    oldWifiStatus = wifiStatus;
  }

  if(wasInvalidated || (oldDateTime != dateTime)) {
    M5.Lcd.setTextDatum(TC_DATUM);

    M5.Lcd.setTextColor(color);
    M5.Lcd.drawString(oldDateTime.c_str(), 160, 5);

    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.drawString(dateTime.c_str(), 160, 5);

    oldDateTime = dateTime;
  }

  if(wasInvalidated || (oldUptime != uptime)) {
    M5.Lcd.setTextDatum(TL_DATUM);

    M5.Lcd.setTextColor(color);
    String s = String("UP:") + String(oldUptime) + String("h");
    M5.Lcd.drawString(s.c_str(), 1, 5);

    M5.Lcd.setTextColor(BLACK);
    s = String("UP:") + String(uptime) + String("h");
    M5.Lcd.drawString(s.c_str(), 1, 5);

    oldUptime = uptime;
  }
  isInvalidated = false;
}
