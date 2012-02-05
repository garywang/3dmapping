class slider
{
  float x_lock;//the x pos the box will center on.
  float y_min;
  float y_max;
  float y_pos;
  int Size;
  
  boolean mouse_over=false;
  boolean locked_on=false;
  
  slider(int x, int y_min, int y_max, int Size)
  {
    x_lock=x;
    this.y_min=y_min;
    this.y_max=y_max;
    y_pos=(y_max+y_min)/2;
    this.Size=Size;
    rectMode(RADIUS);
  };
  
  int getValue()//returns an int from 0 to 255 based on the position of the slider
  {
    //Make sure y_pos is in bounds.
    if(y_pos<y_min+Size)
      y_pos=y_min+Size;
    if(y_pos>y_max-Size)
      y_pos=y_max-Size;
    //higher values on the slider are actually lower y.
    return int(255*(y_pos-y_max-Size)/(y_min-y_max));
  };
  void Draw()//Call every draw step.
  {
    // Test if the cursor is over the box 
    if (mouseX > x_lock-Size && mouseX < x_lock+Size && 
    mouseY > y_pos-Size && mouseY < y_pos+Size) {
      mouse_over = true;  
      if(!locked_on) { 
        stroke(255); 
        fill(153);
      } 
      else{
        stroke(255); 
        fill(255);
      }
    } else {
      stroke(153);
      fill(153);
      mouse_over = false;
    }  
    //Make sure y_pos is in bounds.
    if(y_pos<y_min+Size)
      y_pos=y_min+Size;
    if(y_pos>y_max-Size)
      y_pos=y_max-Size;
    // Draw the box
    rect(x_lock, y_pos, Size, Size);
  };
  void MouseDown()//call when the mouse is pressed
  {
    if(mouse_over) { 
      locked_on = true; 
    } else {
      locked_on = false;
    }
  };
  void MouseOff()
  {
    locked_on = false;
  };
  void MouseMove()
  {
    if(locked_on)
     y_pos=mouseY;
  };
};

