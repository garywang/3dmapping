def derivative( f, h = .001 ):
	return lambda x: ( f( x + h/2 ) - f( x - h/2 ) ) / h
