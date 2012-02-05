from vector import *
from math import *
class obj:
 	def __init__( self ):
  		self.vertices = []
		self.faces = []
 	def add_vertex( self, v ):
		try: self.vertices.index( v )
		except ValueError: self.vertices.append( v )
	def add_face( self, face ):
		for vertex in face.vertices:
			self.add( v )
		self.faces.append( f )
	def add_tetrahedron( self, f ):
		for face in tetrahedron.components()
			self.add_face( face )
	def write( self, filename ):
		f = open(filename, 'w')
		for vertex in self.vertices:
			f.write('v '+str(vertex.x)+' '+str(vertex.y)+' '+str(vertex.z)+'\n')
		f.close()
from random import *
F = obj()
for (x,y) in [(6.28*random(), 6.28*random()) for i in range(10000)]:
	F.add_vertex( vector( cos( x ) * (4 + cos( y )), sin( x ) * (4 + cos( y )), sin( y ) ) )
F.write('test.obj')
