#include <M5Stack.h>

#include <NTPClient.h>
#include <Screen.h>
#include <ButtonInfoBar.h>
#include <StatusBar.h>
#include <Button.h>
#include <WidgetMosaic.h>
#include <string>
#include <time.h>
#include <sys/time.h>
#include <AppScreen.h>
#include <UpDownButton.h>
#include <WiFi.h>


using namespace Codingfield::UI;
AppScreen* screen;
StatusBar* topBar;
ButtonInfoBar* bottomBar;
Codingfield::UI::Button* button0;
Codingfield::UI::Button* button1;
Codingfield::UI::UpDownButton* button2;
Codingfield::UI::Button* button3;
Codingfield::UI::Button* button4;
Codingfield::UI::Button* button5;
WidgetMosaic* mosaic;
Widget* focus;

int32_t editButtonValue = 0;
int32_t editOldButtonValue = 0;

void setup() {
  M5.begin();

  // Instanciate and configure all widgets
  topBar = new StatusBar();
  bottomBar = new ButtonInfoBar();
  mosaic = new WidgetMosaic(3, 2);
  screen = new AppScreen(Size(320, 240), BLACK, topBar, bottomBar, mosaic);

  // Give the focus to the main screen
  focus = screen;

  button0 = new Codingfield::UI::Button(mosaic);
  button0->SetBackgroundColor(BLUE);
  button0->SetTextColor(WHITE);
  button0->SetText("16C");
  button0->SetTitle("Fridge");
  button1 = new Codingfield::UI::Button(mosaic);
  button1->SetBackgroundColor(ORANGE);
  button1->SetTextColor(BLACK);
  button1->SetText("50%");
  button2 = new Codingfield::UI::UpDownButton(mosaic); // Up/Down button
  button2->SetBackgroundColor(YELLOW);
  button2->SetTextColor(BLACK);
  button2->SetText("0");
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
  bottomBar->SetButtonBText("SELECT");
  bottomBar->SetButtonCText(">");

  // Callback called by the mosaic when it changes mode (mosaic/zoom on 1 widget)
  // We use it to update the bottom bar.
  mosaic->SetZoomOnSelectedCallback([bottomBar](Widget* widget, bool edit) {
    if(edit) {
      if(widget->IsEditable()){
        bottomBar->SetButtonAText("-");
        bottomBar->SetButtonBText("APPLY");
        bottomBar->SetButtonCText("+");
      } else {
        bottomBar->SetButtonAText("");
        bottomBar->SetButtonBText("BACK");
        bottomBar->SetButtonCText("");
      }
    } else {
      bottomBar->SetButtonAText("<");
      bottomBar->SetButtonBText("SELECT");
      bottomBar->SetButtonCText(">");
    }
  });

  // Configure callback to be called when the user wants to increment the value
  // of button2
  button2->SetUpCallback([&editButtonValue](UpDownButton* w) {
    editButtonValue++;
    w->SetText(String(editButtonValue).c_str());
    return true;
  });

  // Configure callback to be called when the user wants to decrement the value
  // of button2
  button2->SetDownCallback([&editButtonValue](UpDownButton* w) {
    editButtonValue--;
    w->SetText(String(editButtonValue).c_str());
    return true;
  });

  // Configure callback to be called when the user wants to apply the value
  // of button2
  button2->SetApplyCallback([&editButtonValue, &editOldButtonValue](UpDownButton* w) {
    editOldButtonValue = editButtonValue;
    return false;
  });

  // Configure callback to be called when the user wants to cancel modification
  // of the value of button2
  button2->SetCancelCallback([&editButtonValue](UpDownButton* w) {
    editButtonValue = editOldButtonValue;
    w->SetText(String(editButtonValue).c_str());
    return true;
  });

  // Draw the screen and all its children
  screen->Draw();
}

uint32_t loopCount = 0;
uint32_t temperature = 10;
uint32_t percent = 0;
std::string state = "BUSY";
int32_t wifiStatusIndex;
std::vector<StatusBar::WifiStatuses> wifiStatus {StatusBar::WifiStatuses::No_signal,
                                                 StatusBar::WifiStatuses::Weak,
                                                 StatusBar::WifiStatuses::Medium,
                                                 StatusBar::WifiStatuses::Full};
int32_t uptimeHours=0;
bool longPush = false;
void loop() {
  M5.update();

  // Update values displayd on the screen (status bar, buttons,...)
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
    snprintf(strftime_buf, 64, "%02d:%02d:%02d", 12, 14, 59);
    topBar->SetDateTime(strftime_buf);
  }

  if((loopCount % 100) == 0) {
    if(state == "BUSY") state = "IDLE";
    else state = "BUSY";
    button5->SetText(state);

    auto rssi =WiFi.RSSI();
    if(rssi >= -55) {
      topBar->SetWifiStatus(StatusBar::WifiStatuses::Full);
    } else if(rssi >= -75) {
      topBar->SetWifiStatus(StatusBar::WifiStatuses::Medium);
    } else if(rssi >= -85) {
      topBar->SetWifiStatus(StatusBar::WifiStatuses::Weak);
    } else {
      topBar->SetWifiStatus(StatusBar::WifiStatuses::No_signal);
    }
  }

  // Notify the widgets that physical buttons are pressed
  if(M5.BtnA.wasPressed()) {
    focus->OnButtonAPressed();
  }

  if(M5.BtnB.pressedFor(1000)) {
    if(!longPush) {
      focus->OnButtonBLongPush();
      longPush = true;
    }
  }
  else if(M5.BtnB.wasReleased()) {
    if(!longPush) {
      focus->OnButtonBPressed();
    }
    else {
      longPush = false;
    }
  }

  if(M5.BtnC.wasPressed()) {
    focus->OnButtonCPressed();
  }

  // Redraw the screen
  screen->Draw();

  loopCount++;
  delay(10);
}
