Point2D LinearCombination(Point2D x_hat, Point2D y_hat, Point2D p)
/*
Takes: unit vectors x_hat=(u,v) and y_hat=(u,v) and a point p=(u,v)
Returns: (a,b) such that a*x_hat+b*y_hat=p if (a,b) exists (i.e. x_hat, y_hat independant).
*/
{
  float x=((y_hat.y)*(x_hat.x)-(x_hat.y)*(y_hat.x))/((y_hat.y)*(p.x)-(p.y)*(y_hat.x));
  float y=((x_hat.x)*(y_hat.y)-(y_hat.x)*(x_hat.y))/((x_hat.x)*(p.y)-(p.x)*(x_hat.y));
  return new Point2D(x,y);
};
