# cfGUI
A simple GUI library for M5Stack (ESP32)

This library is intended to run on M5Stack development board (http://www.m5stack.com/),  base on ESP32. 

However, it should be easy to port it to any other board with an LCD screen and 3 physical buttons.

It's composed of a simple hierarchy of graphical widget that can be drawn on screen.
The following widgets have been created so far:
  - Screen and AppScreen (screen with a top bar and a bottom bar)
  - Bar
  - StatusBar (Bar with uptime, clock and Wifi signal)
  - ButtonInfoBar (display the function of the physical button)
  - Button, UpDownButton
  - Mosaic of widgets
  
![Example picture of cfGUI running on a M5Stack board](https://mastodon.codingfield.com/system/media_attachments/files/000/207/740/original/dbacf24f45561e5c.jpg)

# How To (Platform.io)
To use this library with your platform.io project, simply clone or download the library into the directory 'lib' of your project.
Then, you just need to include the headers (e.g. #include <Screen.h>) and write some code.

Look at examples if you need some inspiration ;-)

**NOTE : ** This project was built with version 0.1.9 of M5STack. Since then, a little change has been made on method DrawBitmap which is not compatible with this version of cfGUI. Until I write a fix, you should use version 0.1.9 of M5Stack.

Here is an example of `platform.ini` file:

```
[env:m5stack-core-esp32]
platform = espressif32
board = m5stack-core-esp32
framework = arduino
lib_deps=M5Stack@0.1.9, NTPClient
build_flags=-std=gnu++11
```
  
# Todo
  - <s>Remove hard-coded values to make the lib more flexible</s>
  - Add new widgets
  - Better 'focus' management
  
# Changelog
## 0.2.0
  - Change default font (looks better)
  - New widgets (AppScreen, StatusBar, ButtonInfoBar, UpDownButton)
  - Improved mosaic (the size and position of the widget is not hard-coded anymore)
  - Global improvements

## 0.1.0
  - First version of the library, with basic functionalities
  
