from vector import *

class sphere:
	def __init__( self, center, radius ):
		self.center = center
		self.radius = radius
	def __str__( self ):
		return 'r = '+ str(self.radius) + ', C = ' + str(self.center)
	#Returns True if point is strictly within the sphere, and False otherwise. Due to floating point arithmetic, behavior on the boundary of the sphere is ambiguous (For practical purposes, this may largely be ignored.)
	def contains( self, point ):
		if (point - self.center).length_squared() < radius**2:
			return True
		return False
