#include "testApp.h"
#include "ofAppGlutWindow.h"

pthread_t thread;

testApp* kinection;

void initializeApp()
{
  kinection = new testApp();
  ofAppGlutWindow window;
  ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);
  ofRunApp(kinection);
}

int main() {
  initializeApp();
}

extern "C" {
  void init() {initializeApp();}
  int getLhX() {return kinection->lhx;}
  int getLhY() {return kinection->lhy;}
  int getRhX() {return kinection->rhx;}
  int getRhY() {return kinection->rhy;}
}
