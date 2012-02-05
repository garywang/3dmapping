from vector import *
class circle:
	def __init__( self, radius, center):
		self.radius = radius
		self.center = center
	def distance_to( self, point ):
		return abs(self.radius - ( point - self.center ).length())

def hough_circle( point ):
	#Derived from the cartesian from of r = x_0 * cos( theta ) + y_0 * sin( theta )
	return circle( point.length() / 2, scale( 0.5, point ) )

def f(x):
		return  1/(x+.1)

#Returns the hough transform of the list of points. Note that this is of the form Hough( x, y ) NOT Hough( r, theta )
def hough( points ):
	return lambda point: sum( [ f( hough_circle( p ).distance_to( point ) ) for p in points ] )

def houghq( points ):
	return lambda point: hough( points )( point ) / ( ( len( points ) -1 ) * f( point.length() ) + 1 )

from numpy import *
import matplotlib.pyplot as plt
def PLOT( f ):
	#Display the result as a contor plot.
	x = linspace(-30,30,100)
	y = linspace(-30,30,100)
	(X,Y) = meshgrid(x,y)
	a = [ [ f( x[j],y[i] ) for j in range( len( x ) ) ] for i in range( len( y ) ) ]
	c = plt.contourf(x,y,a,linspace(0,15,21))
	b = plt.colorbar(c, orientation='vertical')
	lx = plt.xlabel("x")
	ly = plt.ylabel("y")
	ax = plt.axis([-30,30,-30,30])
	plt.show()

PLOT( lambda x,y: houghq( [ vector(i , 10 - i) for i in linspace( 0, 10, 30 ) ] + [ vector(i , 10 + i) for i in linspace( -10, 0, 30 ) ] + [ vector(i , -7) for i in linspace( -10, 10, 40 ) ] )( vector(x,y)) )
