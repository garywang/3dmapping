#include "testApp.h"
#include "ofAppGlutWindow.h"

pthread_t thread;

testApp* kinection;

#include <iostream>

void initializeApp()
{
  std::cout << "Initializing" << std::endl;
  kinection = new testApp();
  std::cout << "Running" << std::endl;
  //ofAppGlutWindow window;
  //ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);
  ofRunApp(kinection);
  std::cout << "Done" << std::endl;
}

//int main() {
//  initializeApp();
//}

//extern "C" {
  void init() {initializeApp();}
  int getLhX() {return kinection->lhx;}
  int getLhY() {return kinection->lhy;}
  int getRhX() {return kinection->rhx;}
  int getRhY() {return kinection->rhy;}
//}
