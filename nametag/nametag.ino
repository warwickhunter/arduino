/**
 * An electronic name tag for use at super geeky meetings.
 * 
 * Warwick Hunter 2016-04-16
 */
#include <MicroView.h>


const int LAST_PAGE = 3;

static int page = 0;

void setup() {
    uView.begin();
}

void display(const char* message) {
    uView.clear(PAGE);
    uView.setCursor(0, 0);
    uView.print(message);
    uView.display();
}

void loop() {
  switch (page) {
      case 0: // Name & occupation
          display("Warwick\nHunter\n\nSoftware\nEngineer");
          break;
      case 1: // Skills
          display("Warwick\nHunter\n\nAndroid\nJava C++\nLinux");
          break;
      case 2: // Contact
          display("Warwick\nHunter\n\nw.hunter\n@computer\n.org");
          break;
      case 3: // Hobbies
          display("Warwick\nHunter\n\nBMW Rider\nK1300S\nR1200GSA");
          break;
  }
  uView.display();
  ++page;
  delay(2000);
  if (page > LAST_PAGE) {
    page = 0;
  }
}
