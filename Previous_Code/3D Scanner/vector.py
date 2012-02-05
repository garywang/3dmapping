from math import sqrt

class vector:
	x = 0
	y = 0
	z = 0
	def __init__( self, x, y, z = 0 ):
		self.x = float( x )
		self.y = float( y )
		self.z = float( z )
	def __str__( self ):
		return '(' + str(self.x) + ', ' + str(self.y) + ', ' + str( self.z ) + ')'
	def __add__( self, other ):
		return vector( self.x + other.x, self.y + other.y, self.z + other.z )
	def __sub__( self, other ):
		return vector( self.x - other.x, self.y - other.y, self.z - other.z )
	def __eq__( self, other ):
		return ( self.x == other.x ) and ( self.y == other.y ) and ( self.z == other.z )
	def __ne__( self, other ):
		return not self == other
	def __hash__( self ):
		return hash( (self.x, self.y, self.z) )
	# computationally faster than (vector.length()**2)
	def length_squared( self ):
		return dot( self, self )
	def length( self ):
		return sqrt( self.length_squared() )
	def normalized( self ):
		return self.scaled( 1.0 / self.length() )

def dot( A, B ):
	return A.x * B.x + A.y * B.y + A.z * B.z

def cross( A, B ):
	return vector( A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x )

def scale( n, A ):
	return vector( n * A.x, n * A.y, n * A.z )
