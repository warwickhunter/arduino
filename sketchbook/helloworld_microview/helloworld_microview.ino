#include <MicroView.h>

void restart() {
    uView.clear(PAGE);
    uView.setCursor(0, 0);
    uView.print("This is\nWarwick's\nMicroView\nArduino");
    uView.display();
}

void setup() {
    uView.begin();
    restart();
}

static int y = 0;

void loop() {
  uView.line(0,y,LCDWIDTH - 1,y);
  uView.display();
  y += 4;
  if (y >= LCDHEIGHT) {
     y = 0;
     restart();
  }
  delay(500);
}
