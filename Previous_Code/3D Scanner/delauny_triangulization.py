from vector import *
from sphere import *
from simplex import *
from graph import *

#Implements Bowyer-Watson with my own touch (graph based simplex selection)
def delauny_tri( points_to_include ):
	#Initiate data structures
	points = points_to_include[:4]
	tetrahedrons = [ node( tetrahedron( points[:4] ) ) ]
	#TODO initiate graph
	
	while len( points ) < len( points_to_include ):
		point = points_to_include[n]
		#TODO make this use the graph. It can be done much faster this way. canidate_tetrahedrons should also be determined here.
		initial = None
		for Tetrahedron in tetrahedrons:
			if Tetrahedron.contents.circumsphere().contains(point):
				initial = Tetrahedron
				break
		if initial == None: #None conflict! Check exterior faces...
			pass
		else:
			invalid = flood_find( initial, lambda( Tetrahedron ): Tetrahedron.contents.circumsphere().contains(point) )
		canidate_faces = []
		for Tetrahedron in canidate_tetrahedrons:
			circumsphere = Tetrahedron.circumsphere()
			for p in V_n:
				if circumsphere.contains(p):
					pass #TODO remove Tetrahedron from canidate_tetrahedrons
		#Clean up
		points.append( point )

print "The circumsphere of a regular tetrahedron has",tetrahedron( [vector(1,1,1), vector(-1,-1,1), vector(1,-1,-1), vector(-1,1,-1)] ).circumsphere(),"."
#print delauny_tri([vector(1,1,1), vector(-1,-1,1), vector(1,-1,-1), vector(-1,1,-1), vector(5,6,7)])
