/***********************************
 * Adapted from code by Tom Gibara *
 * Processing port by Will Oursler *
 **********************************/
 import processing.video.*;

Capture video;
//user interface
slider threshold;
slider min_pixels;

int has_off=0;

PImage Off;

void setup() {
  // Change size if too slow
  size(640, 480); 
  video = new Capture(this, width/2, height/2, 24);
  threshold=new slider(width/2-5,height/2,height,5);
  min_pixels=new slider(width-5,0,height/2,5);
}

void draw() {
  if (video.available()) {
    video.read(); // Read a new video frame
    video.loadPixels(); // Make the pixels of video available
    if(has_off==0)
      image(video,0,0,width,height);//If we haven't set the off image yet, show the camera fullscreen as a diagnostic.
    if(has_off!=0)
    {
      background(0);//set a black bacldrop.
      PImage On=new PImage(width/2, height/2);
      arraycopy(video.pixels, On.pixels);
      On.updatePixels();
      
      PImage difference=Subtract(On,Off);
      PImage clean=GreenThresholdFilter(difference,threshold.getValue());//The best threshold seems to change with gantry position (light conditions?[yes it is]). Set it manually if it needs to be diffrent.
      
      CannyEdgeDetector detector = new CannyEdgeDetector(clean, 0.999f, 1f);
      PImage edges = detector.getEdgesImage();
      
      PImage mean=MeanLine(edges);            
      image(mean, 0, 0);
      
      HoughTransform hough=new HoughTransform(mean,400,200);
      stroke(color(255,255,0));//Draw bright yellow lines for the results.
      hough.GetBestLine().Draw();
            
      //Draw the other three panels...      
      image(clean, 0, height/2);
      threshold.Draw();//Draw the threshold slider. 
      image(video, width/2, height/2);
      
      //cluster edges.
      ArrayList clusters=Cluster(edges);
      for(int i=0; i<clusters.size(); i++)
      {
        EdgeCluster cluster=(EdgeCluster)clusters.get(i);
        if(cluster.Size()>min_pixels.getValue())
          cluster.Draw(width/2,0,color(random(256),random(256),random(256)));//Draw colored edge groups in the upper right
        else
          cluster.Draw(width/2,0,color(255,255,255));//Draw white, so it's clear what's being ignored.
      };
      min_pixels.Draw();
    }    
  }
}

void keyPressed() {
  video.loadPixels();
  Off=new PImage(width/2, height/2);
  arraycopy(video.pixels, Off.pixels);
  Off.updatePixels();
  has_off=1;
}

void mousePressed() {
  threshold.MouseDown();
  min_pixels.MouseDown();
}

void mouseDragged() {
  threshold.MouseMove();
  min_pixels.MouseMove();
}

void mouseReleased() {
  threshold.MouseOff();
  min_pixels.MouseOff();
}

