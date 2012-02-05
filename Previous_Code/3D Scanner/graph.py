class graph:
	def __init__( self, nodes, directed = False ):
		self.directed = directed
		self.edge_dict = {}
		self.nodes = []
		for node in nodes:
			self.add_node( node )
	def add_node( self, node ):
		if node in self.nodes:
			raise Exception('Node "'+str(node)+'" was already included in graph!')
		self.edge_dict[node] = {}
		self.edge_dict[node][node] = []
		if self.directed:
			for N in self.nodes:
				self.edge_dict[node][N] = []
				self.edge_dict[N][node] = []
		else: #If undirected then these are the same list (self.E[a][b] <-> self.E[b][a]).
			for N in self.nodes:
				self.edge_dict[node][N] = self.edge_dict[N][node] = []
		self.nodes.append( node )
	def link( self, node1, node2, edge ):
			self.edge_dict[node1][node2].append( edge ) #If the graph is undirected, this will also link node2 to node1
class node:
	def __init__( self, contents ):
		self.contents = contents
		self.neighbors = set()
	def link( self, other, directed = False ):
		#Linking to ourselves would be rather narcissistic, eh?
		if self == other:
			return
		self.neighbors.add( other )
		#If the link is undirected, we need to link up the other direction.
		if not directed:
			other.neighbors.add( self )
	def __str__( self ):
		return str( self.contents )
	def __repr__( self ):
		return self.__str__()

#Finds the largest connected subgraph
#which includes 'initial' for which
#each node satisfies
#'condition( node ) == True'
def flood_find( initial, condition ):
	found = set()
	visited = set()
	boundary = set( [ initial ] )#Start with our initial node...
	while len( boundary ) > 0:
		current = boundary.pop()
		if condition( current ):
			found.add( current )
			boundary = boundary | current.neighbors - visited #Expand the boundary.
		visited.add( current ) #Make sure we never visit this node again
	return found
'''
print "TESTING NODE BASED VIEW (depreciated)..."
G = [node( n ) for n in range(10)]
for i in range(9):
	G[i].link( G[i+1] )
G[9].link( G[0] )
print flood_find( G[7], lambda x: x.contents > 3 )
print "TESTING NEW GRAPH CLASS."
GRAPH = graph(range(10))
GRAPH.add_node(0)
GRAPH.link(0,1,True)
print GRAPH.edge_dict
'''
