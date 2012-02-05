/************************
*     Original Code     *
*   Will Oursler 2010   *
*ninjinuity.blogspot.com*
************************/

import processing.video.*;

Capture video;

Scanner scanner;
int scanning=0;

PImage Off;

void setup() {
  // Change size if too slow
  size(640, 480); 
  video = new Capture(this, width, height, 24);
  scanner=new Scanner("normal");
}

void draw() {
  if (video.available()) {
    video.read(); // Read a new video frame
    video.loadPixels(); // Make the pixels of video available
    if(scanning!=0)
    {
      PImage On=new PImage(width, height);
      arraycopy(video.pixels, On.pixels);
      On.updatePixels();
      //scanner.ProcessImage(On);
      GetMeanline(ThresholdGreen(Subtract(On,Off),10));
    }
    //image(video,0,0);
    
  }
}

// When a key is pressed, set the scanner's Off image, and begin the scan.
void keyPressed() {
  video.loadPixels();
  Off=new PImage(width, height);
  arraycopy(video.pixels, Off.pixels);
  Off.updatePixels();
  scanner.SetOffImage(Off);
  scanning=1;
}
