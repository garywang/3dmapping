from matrix import *
from vector import *
from sphere import *

#Eventual replacement module for Tetrahedron, Face, Edge, Etc.... Wrap all functionality into derived Simplexs
class simplex:
	def __init__( self, order, vertices ):
		self.order = order
		self.vertices = vertices#TODO It would be more accurate to use a set here. THat requires a rewrite of simplex.content().
		#Check to make sure we have the correct number of points.
		if len(self.vertices) != self.order + 1:
			Exception() #TODO Make more specific
		#Check for degeneracy...
		if self.content() == 0:
			Exception() #TODO Make more specific
	#Returns the n order n-1 simplices that make up this simplex
	def components(self):
		if self.order is 0:
			Exception() #TODO Make more specific
	#Find the content (i.e. hypervolume) with the Cayley-Menger Determinant. See http://mathworld.wolfram.com/Cayley-MengerDeterminant.html
	def content( self ):
		B = matrix( self.order + 2 )
		for i in range( self.order + 2 ):
			for j in range( self.order + 2 ):
				if i == j:
					B.set_value( i, j, 0 )
				elif i == 0 or j == 0:
					B.set_value( i, j, 1 )
				else:
					B.set_value( i, j, ( self.vertices[ i - 1 ] - self.vertices[ j - 1 ] ).length_squared() )
		from math import factorial, sqrt
		coefficient = ( (-1) ** ( self.order + 1 ) ) / float( ( 2 ** self.order ) * ( factorial( self.order ) ** 2 ) )
		return sqrt( coefficient * determinant( B ) )
	def components( self ):
		if self.order == 0:
			return []
		return [ simplex( self.order - 1, self.vertices[ : i ] + self.vertices[ i + 1 : ] ) for i in range( len( self.vertices ) ) ]

#This ends up being a bit rough around the edges. It would be great to have simplex autoconvert itself on construction...
class vertex( simplex ):
	def __init__( self, vertices ):
		simplex.__init__( self, 0, vertices )
class edge( simplex ):
	def __init__( self, vertices ):
		simplex.__init__( self, 1, vertices )
class face( simplex ):
	def __init__( self, vertices ):
		simplex.__init__( self, 2, vertices )
class tetrahedron( simplex ):
	def __init__( self, vertices ):
		simplex.__init__( self, 3, vertices )
	def volume( self ):
		return self.content()
	def circumsphere( self ):
		#See http://cgafaq.info/wiki/Tetrahedron_Circumsphere
		#Introduce a notation for the vertices.
		A = self.vertices[0]
		B = self.vertices[1]
		C = self.vertices[2]
		D = self.vertices[3]
		#Shift so that A is at the orgin for simplicity.
		X = B - A
		Y = C - A
		Z = D - A
		#Big formulas! Again, see http://cgafaq.info/wiki/Tetrahedron_Circumsphere for a source (if not an explanation).
		radius = (
				(
					scale( Z.length_squared(), cross( X, Y ) )
					+scale( Y.length_squared(), cross( Z, X ) )
					+scale( X.length_squared(), cross( Y, Z ) )
				).length()
			)/(
				2 * dot( X, cross( Y, Z ) )
			)
		center = A + scale(
				1 / ( 2 * dot( X, cross( Y, Z ) ) ),
				scale( Z.length_squared(), cross( X, Y ) )
				+ scale( Y.length_squared(), cross( Z, X ) )
				+ scale( X.length_squared(), cross( Y, Z ) )
			)
		return sphere( center, radius )


print "Starting Simplex Test..."
t = tetrahedron( [vector(1,1,1), vector(-1,-1,1), vector(1,-1,-1), vector(-1,1,-1)] )
print t.volume()
print t.circumsphere()
print t.components()
