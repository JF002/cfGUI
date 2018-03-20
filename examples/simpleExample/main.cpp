#include <M5Stack.h>

#include <Screen.h>
#include <ButtonInfoBar.h>
#include <StatusBar.h>
#include <Button.h>
#include <WidgetMosaic.h>

using namespace Codingfield::UI;
Screen screen(Size(320, 240), BLACK);
StatusBar* topBar;
ButtonInfoBar* bottomBar;
Codingfield::UI::Button* button0; // M5STack should really use namespaces to avoid name clashes
Codingfield::UI::Button* button1;
Codingfield::UI::Button* button2;
Codingfield::UI::Button* button3;
Codingfield::UI::Button* button4;
Codingfield::UI::Button* button5;
WidgetMosaic* mosaic;
Widget* focus;

void setup() {
  M5.begin();

  topBar = new StatusBar(&screen, Point(0,0), 25);
  bottomBar = new ButtonInfoBar(&screen, Point(0, screen.GetSize().height-25), 25);

  mosaic = new WidgetMosaic(&screen, Point(5,30), Size(320, 190));
  focus = mosaic;

  button0 = new Codingfield::UI::Button(mosaic);
  button0->SetBackgroundColor(BLUE);
  button0->SetTextColor(WHITE);
  button0->SetText("16C");
  button0->SetTitle("Fridge");
  button1 = new Codingfield::UI::Button(mosaic);
  button1->SetBackgroundColor(ORANGE);
  button1->SetTextColor(BLACK);
  button1->SetText("50%");
  button2 = new Codingfield::UI::Button(mosaic);
  button2->SetBackgroundColor(YELLOW);
  button2->SetTextColor(BLACK);
  button2->SetText("3h15");
  button3 = new Codingfield::UI::Button(mosaic);
  button3->SetBackgroundColor(PURPLE);
  button3->SetTextColor(WHITE);
  button3->SetText("COOL");
  button4 = new Codingfield::UI::Button(mosaic);
  button4->SetBackgroundColor(GREEN);
  button4->SetTextColor(WHITE);
  button4->SetText("ERROR");
  button5 = new Codingfield::UI::Button(mosaic);
  button5->SetBackgroundColor(MAROON);
  button5->SetTextColor(WHITE);
  button5->SetText("BUSY");

  topBar->SetUptime(0);
  topBar->SetWifiStatus(StatusBar::WifiStatuses::No_signal);

  bottomBar->SetButtonAText("<");
  bottomBar->SetButtonBText("Select");
  bottomBar->SetButtonCText(">");

  screen.Draw();
}

uint32_t loopCount = 0;
uint32_t temperature = 10;
uint32_t percent = 0;
std::string state = "BUSY";
int32_t wifiStatusIndex;
int rssi = -100;
int seconds = 0;
std::vector<StatusBar::WifiStatuses> wifiStatus {StatusBar::WifiStatuses::No_signal,
                                                 StatusBar::WifiStatuses::Weak,
                                                 StatusBar::WifiStatuses::Medium,
                                                 StatusBar::WifiStatuses::Full};
int32_t uptimeHours=0;
void loop() {
  M5.update();

  if((loopCount % 50) == 0) {
    if(temperature < 100)
      temperature++;
    else temperature = 0;

    String s;
    s = String(temperature) + String("C");
    button0->SetText(s.c_str());

    if(percent < 100)
      percent++;
    else percent = 0;

    s = String(percent) + String("%");
    button1->SetText(s.c_str());

    uptimeHours = millis() / (60*60000);
    topBar->SetUptime(uptimeHours);

    char strftime_buf[64];
    if(seconds < 60)
      seconds++;
    else
      seconds = 0;
    snprintf(strftime_buf, 64, "%02d:%02d:%02d", 1, 2, seconds);
    topBar->SetDateTime(strftime_buf);

    if(rssi < 0)
      rssi++;
    else
      rssi = -100;
    if(rssi >= -55)
      topBar->SetWifiStatus(StatusBar::WifiStatuses::Full);
    else if(rssi >= -75)
      topBar->SetWifiStatus(StatusBar::WifiStatuses::Medium);
    else if(rssi >= -85)
      topBar->SetWifiStatus(StatusBar::WifiStatuses::Weak);
    else
      topBar->SetWifiStatus(StatusBar::WifiStatuses::No_signal);
  }

  if((loopCount % 100) == 0) {
    if(state == "BUSY") state = "IDLE";
    else state = "BUSY";
    button5->SetText(state);
  }

  if(M5.BtnA.wasPressed())
    focus->OnButtonAPressed();

  if(M5.BtnB.wasPressed())
    focus->OnButtonBPressed();

  if(M5.BtnC.wasPressed())
    focus->OnButtonCPressed();

  screen.Draw();

  loopCount++;
  delay(10);
}
