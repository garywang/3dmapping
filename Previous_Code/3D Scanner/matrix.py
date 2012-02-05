class MatrixSizeError( ValueError ):
	pass
class MatrixIndexError( ValueError ):
	pass
class MatrixValueError( ValueError ):
	pass

class matrix:
	def __init__( self, num_rows, num_columns = None ):
		#make a square matrix if num_columns is left blank.
		if num_columns is None:
			num_columns = num_rows
		self.contents = [[0 for i in range(num_columns)] for j in range(num_rows)]

	def num_rows( self ):
		return len( self.contents )

	def num_columns( self ):
		return len( self.contents[0] )

	def get_value( self, row_index, column_index ):
		return self.contents[row_index][column_index]

	def set_value( self, row_index, column_index, value ):
		self.contents[row_index][column_index] = value

	#Do I hear lambda functions calling(see matrix.__mul__ or identiy matrix for examples)? Set every value in the array with the rule A_ijMinimal Surface with symmetry axes marked = value( i, j )
	def set_all_values( self, value ):
		for row_index in range( self.num_rows() ):
			for column_index in range( self.num_columns() ):
				self.contents[row_index][column_index] = value( row_index, column_index )
	
	def transpose( self ):
		result = matrix( self.num_columns(), self.num_rows() )
		result.set_all_values( lambda i, j: self.get_value( j, i ) )
		return result

	def __mul__( self, other ):
		if self.num_columns() != other.num_rows():
			raise MatrixSizeError("Matrix Sizes don't match.")
		result = matrix( self.num_rows(), other.num_columns() )
		result.set_all_values( lambda row_index, column_index: sum( [ self.get_value( row_index, index ) * other.get_value( index, column_index ) for index in range( self.num_columns() ) ] ) )
		return result

	def __add__( self, other ):
		if self.num_rows() != other.num_rows() or self.num_columns() != other.num_columns():
			raise MatrixSizeError("Matrix Sizes don't match.")
		result = matrix( self.num_rows(), other.num_columns() )
		result.set_all_values( lambda row_index, column_index: self.get_value( row_index, column_index ) + other.get_value( row_index, column_index ) )
		return result
	def __sub__( self, other ):
		if self.num_rows() != other.num_rows() or self.num_columns() != other.num_columns():
			raise MatrixSizeError("Matrix Sizes don't match.")
		result = matrix( self.num_rows(), other.num_columns() )
		result.set_all_values( lambda row_index, column_index: self.get_value( row_index, column_index ) - other.get_value( row_index, column_index ) )
		return result
	def PRINT( self ):
		for row in self.contents:
			print row

def identity_matrix( n ):
	I = matrix( n )
	#The notation below in the lambda function confused me when I first saw it. See http://eikke.com/python-ifelse-in-lambda/ for a nice explanation of what it does.
	I.set_all_values( lambda row_index, column_index: row_index == column_index and 1 or 0 )
	return I

def minor( A, row_index, column_index ):
	#See http://en.wikipedia.org/wiki/Minor_(linear_algebra).
	if row_index >= A.num_rows() or column_index >= A.num_columns():
		raise MatrixIndexError("Indices out of range.")
	M = matrix( A.num_rows() - 1, A.num_columns() - 1 )
	for i in range( M.num_rows() ):
		for j in range( M.num_columns() ):
			if i < row_index:
				if j < column_index:
					M.set_value( i, j, A.get_value( i, j ) )
				else:
					M.set_value( i, j, A.get_value( i, j + 1 ) )
			else:
				if j < column_index:
					M.set_value( i, j, A.get_value( i + 1, j ) )
				else:
					M.set_value( i, j, A.get_value( i + 1, j + 1 ) )
	return M
			
def cofactor( A, row_index, column_index ):			
	if A.num_rows() != A.num_columns():
			raise MatrixSizeError("Matrix is not square.")
	return determinant( minor( A, row_index, column_index ) ) * ( -1 ) ** ( row_index + column_index )

def determinant( A ):
	if A.num_rows() != A.num_columns():
			raise MatrixSizeError("Matrix is not square.")
	#For clarity of code
	size = A.num_rows()

	#If the Matrix is 1 by 1, the determinant is easy...
	if size is 1:
		return A.get_value( 0, 0 )
        j = 0
	SUM = 0
	for i in range( size ):
		#Compute the required cofactor.
		SUM +=  A.get_value( i, j ) * cofactor( A, i, j )
	return SUM

#returns B s.t. AB = I
def inverse( A ):
	if A.num_rows() != A.num_columns():
		raise MatrixSizeError("Matrix is not square.")
	#For clarity of code
	size = A.num_rows()
	detA = determinant( A )
	if detA == 0:
		raise MatrixValueError("Matrix is not invertable.")
	B = matrix( size )
	if size == 1:
		B.set_value( 0, 0, 1 / detA )
		return B
	B.set_all_values( lambda i, j: cofactor( A, j, i ) / float( detA ) )
	return B
