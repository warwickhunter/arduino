#include <MicroView.h>

void restart() {
    uView.clear(PAGE);
    uView.setCursor(0, 0);
    uView.print("\n This is\n Wasa's\n Arduino");
    uView.display();
}

void setup() {
    uView.begin();
    restart();
}

static int side = 0;

void loop() {
  switch (side) {
      case 0: // Left
          uView.line(0,0,0,LCDHEIGHT-1);
          break;
      case 1: // Top
          uView.line(0,0,LCDWIDTH-1,0);
          break;
      case 2: // Right
          uView.line(LCDWIDTH-1,0,LCDWIDTH-1,LCDHEIGHT-1);
          break;
      case 3: // Bottom
          uView.line(0,LCDHEIGHT-1,LCDWIDTH-1,LCDHEIGHT-1);
          break;
      case 4:
          uView.clear(PAGE);
          uView.display();
          break;
  }
  uView.display();
  ++side;
  delay(500);
  if (side > 4) {
    side = 0;
    restart();
  }
}
