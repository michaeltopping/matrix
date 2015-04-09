# matrix
matrix operations

function overview:

det3d(mat[3][3]):
calculates the determinant of a 3x3 matrix
input:3x3 matrix of floats, matrix[row][column]
output:float determinant

det4d(**matrix):
calculates the determinant of a 4x4 matrix
input:**matrix, a 4x4 pointer matrix, matrix[row][column]
output:float determinant

transpose(#rows, #columns, **matrix):
calculates the transpose of a matrix
input:#rows - number of rows of input matrix
      #columns - number of columns of input matrix
      **matrix - 2d array of pointers with dimension matrix[#rows][columns]
output:**matrix - 2d array of pointers with dimension matrix[#columns][#rows]

invert(size, **matrix):
calculates the inverse of a matrix
input:size - the number of elements in a row or column, only works for square matrices
      **matrix - 2d square matrix of floats of form matrix[row][column]
output:2d square size x size matrix of pointers with form matrix[row][column]

oddIndexNegative(size, **matrix):
for elements of a matrix with row+column = odd, the sign of the element is reversed
used in computing the inverse
input: size - number of elements in a row or column, only works for square matrices
       **matrix -  2d square matrix of floats of form matrix[row][column]
output: **matrix -  2d square matrix of floats of form matrix[row][column]

multiply(iRows, iColumns, jColumns, **matrix1, **matrix2):
multiplies two matrices together. (matrix1 x matrix2)
input: iRows - number of rows for first matrix
       iColumns - number of columns for the first matrix
       jColumns - number of columns for the second matrix
       **matrix1 - first matrix 
       **matrix2 - second matrix
output: **matrix of floats that is iRows x jColumns

free_board(**matrix, rows)
frees memory
input: **matrix - the pointer to the memory to be freed
	   rows - the number of rows allocated in the memory block.
