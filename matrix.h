#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <string.h>


float det3d(float mat[3][3]);
float det4d(float **matrix);
float **transpose( int rows, int columns, float **matrix);
void free_board(float **matrix, int rows);
float **invert( int size, float **matrix);
float **oddIndexNegative( int size, float **matrix);
float **multiply(int iRows, int iColumns, int jColumns, float **matrix1, float **matrix2);


//find the transpose of a matrix
float **transpose( int rows, int columns, float **matrix)
{
	//rows
    float **Bt = (float **)calloc(columns, sizeof(float *)); 

	//columns
    for (int column = 0; column < columns; column++) {
        Bt[column] = (float *)calloc(rows, sizeof(float));
    }
    //loop through each row and column, set them to columns and rows
	for (int row = 0; row < columns; row++) {
		for (int column = 0; column < rows; column++) {
			Bt[row][column] = matrix[column][row];
		}
	}
	return Bt;
}


//multiply two matrices
float **multiply(int iRows, int iColumns, int jColumns, float **matrix1, float **matrix2)
{
	//rows
    float **BtB = (float **)calloc(iRows, sizeof(float *)); 

	//columns
    for (int row = 0; row < iRows; row++) {
        BtB[row] = (float *)calloc(jColumns, sizeof(float));
    }
	
	//formula to calculate the matrix multiplication
	for (int row=0; row < iRows; row++) {
		for (int column=0; column < jColumns; column++) {
			for (int obj=0; obj < iColumns; obj++) {
				BtB[row][column] += matrix1[row][obj]*matrix2[obj][column];
			}
		}
	}
	return BtB;
}


//find the inverse of a matrix
float **invert( int size, float **matrix)
{
	//will need the determinant
	float det = det4d(matrix);
	
	//allocate memory
	float element;
	//rows
    float **inverse = (float **)calloc(size, sizeof(float *)); 

	//columns
    for (int row = 0; row < size; row++) {
        inverse[row] = (float *)calloc(size, sizeof(float));
    }

	//now we find the inverse of BtB
	//we first need the matrix of minors:
	float RR[3][3]; //matrix after removing one row and one column
	
	//loop through each element in the matrix of minors:
	printf("Calculating the matrix of minors\n");
	for (int row = 0; row < size; row++) { //for each row in BtB
		for (int column = 0; column < size; column++) { //for each column in BtB

			//these variables will check if the next row/column has been removed
			//leaving a 3x3 matrix
			int nextBtBrow = 0;
			int nextBtBcolumn = 0;
			
			//loop through the rows of the new reduced matrix
			for (int rowRR = 0; rowRR < 3; rowRR++) {
				nextBtBcolumn = 0;
				if (nextBtBrow == row) {
					nextBtBrow++;
				}
				//loop through the columns of the reduced matrix
				for (int columnRR = 0; columnRR < 3; columnRR++) {
					if (nextBtBcolumn == column) {
						nextBtBcolumn++;
					} 
					//assign the values of the new reduced matrix
					RR[rowRR][columnRR] = matrix[nextBtBrow][nextBtBcolumn];
					nextBtBcolumn++;
				}
				nextBtBrow++;
			}
		
			//calculate the values for the matrix of minors as the determinant of
			//the reduced matrix
			element = det3d(RR) / det;
			//printf("Inside invert: inverted element is: %f\n", element);

			inverse[row][column] = element;
		}
	}

	//then transpose the inverse matrix
	return transpose(size, size, oddIndexNegative( size, inverse));
}


//make the elements with odd (row+column) the opposite sign
float **oddIndexNegative( int size, float **matrix)
{
	//float Bt[4][24];  //B transpose
	//rows
    float **resMat = (float **)calloc(size, sizeof(float *)); 

	//columns
    for (int row = 0; row < size; row++) {
        resMat[row] = (float *)calloc(size, sizeof(float));
    }

	//float BtB[4][4]; //B transpose * B
	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; column++) {
			resMat[row][column] = pow(-1, (row+column))*matrix[row][column];
		}
	}	

	return resMat;
}


//inputs a 3x3 matrix and returns the determinant
//just hardcoded
float det3d(float mat[3][3])
{
	float det;
		det = mat[0][0]*(mat[1][1]*mat[2][2]-mat[2][1]*mat[1][2]) - mat[0][1]*(mat[1][0]*mat[2][2]-mat[2][0]*mat[1][2]) + mat[0][2]*(mat[1][0]*mat[2][1]-mat[2][0]*mat[1][1]);
	return det;
}

//determinant of a 4d matrix
float det4d(float **matrix)
{
	//find the determinant of the original matrix BtB
	float det;
	float RR[3][3];
	//loop through columns of the B transpose * B matrix
	for (int column = 0; column < 4; column++) {

		//for determining which row/column will be removed
		int nextBtBrow = 0;
		int nextBtBcolumn = 0;
		
		//loop through the rows of the reduced matrix
		for (int rowRR = 0; rowRR < 3; rowRR++) {
			nextBtBcolumn = 0;
			if (nextBtBrow == 0) {
				nextBtBrow++;
			}
			for (int columnRR = 0; columnRR < 3; columnRR++) {
				if (nextBtBcolumn == column) {
					nextBtBcolumn++;
				} 
				RR[rowRR][columnRR] = matrix[nextBtBrow][nextBtBcolumn];
				nextBtBcolumn++;
			}
			nextBtBrow++;
		}
	
			
		//calculate the determinant of the BtB matrix
		det += pow(-1,column)*matrix[0][column]*det3d(RR);
	}
	
	return det;

}
