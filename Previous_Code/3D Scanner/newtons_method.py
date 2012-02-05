from derivative import derivative
def newton( f, guess, tolerance = .0000000000001 ):
	max_iterations = 10**6
	iterations = 0
	x = guess	
	while abs( f( x ) ) > tolerance :
		derivativef = derivative(f)(x)
		if derivativef == 0:
			return None
		x = x - ( f(x) / derivativef )
		iterations += 1
		if iterations > max_iterations:
			return None
	return x
#Works best for polynomials.
def polynomial( roots ):
	return lambda x: reduce( lambda poly, root: poly * ( x - root ), [1]+roots )
def roots( f, guess ):
	roots = []
	root = newton( f, guess )
	while root != None:
		roots.append( root )
		root = newton( lambda x: f( x ) / polynomial( roots )( x ), guess )
	return roots
def extrema( f, guess ):
	return roots( derivative(f), guess )
print roots( lambda x: 2.71828183**x + x, -1 )
