/* Question 1:
 *
 * No, C++ can only return a pointer to a dynamic array (declared using new[]).
 * If an automatic array is attempted to be returned, it does not work
 * as there the automatic array does not exist out of its function's scope.
 * Therefore, a dynamic array must be used to get around this problem. Even with
 * the use of a dynamic array, dynamic memory must be used (new[]) to overcome
 * the scope problem. After calling the function that returns the pointer to
 * the dynamic array, delete [] must be used to reclaim the memory.
 */
#include <iostream>
#include <cstdlib>
using namespace std;
const int rows = 5;
const int cols = 5;

//Question 2
void fillMatrix(int matrix[rows][cols]) {
	//use seed of 1 to generate random but consistent matrices
	srand(1);
	for (int i=0; i < rows; i++) {
		for (int j=0; j <cols; j++) {
			// %5 + 1 generates a number that is between 1 and 5 inclusive
			matrix[i][j] = rand() % 5 + 1;
		}
	}
}

//Question 3
void PrintMatrix(int matrix[rows][cols]) {
	for (int i=0; i < rows; i++) {
		for (int j=0; j <cols; j++) {
			//print spaces between each number
			if(j != cols-1) {
				cout << matrix[i][j] << " ";
			}
			//line break at the end of the row
			else {
				cout << matrix[i][j] << endl;
			}
		}
	}
	//line break at the end so whatever is printed next looks nice
	cout << endl;
}

//Question 4
void transposeMatrix(int matrix[rows][cols]) {
	for (int i=0; i < rows; i++) {
		//int j=i so I do not transpose elements that have already BEEN transposed
		for (int j=i; j < cols; j++) {
			//temporary variable to store the value being transposed
			int temp = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = temp;
		}
	}
}

//Question 5
//returns a pointer to the third matrix (dynamic)
int** multiplyMatrix(int matrix1[rows][cols], int matrix2[rows][cols]) {
	//A 2D matrix is an array of pointers
	int** matrix3 = new int*[rows];
	//initialize each pointer in the array to be a pointer to another array
	for (int i=0; i < rows; i++) {
		matrix3[i] = new int[cols];
	}
	for (int i=0; i < rows; i++) {
		for (int j=0; j < cols; j++) {
			int sum = 0;
			for (int k=0; k < cols; k++) {
				//i and j are for final matrix grid coordinates
				//k traverses through the row of matrix1 and column of matrix2
				//then when j is incremented, advance to next column but same row
				//then when i is incremented, advance to next row and redo all columns
				sum+= matrix1[i][k]*matrix2[k][j];
			}
			matrix3[i][j] = sum;
		}
	}
	return matrix3;
}

//Question 6: Question 5 in recursion
//due to use of recursion, an empty third matrix just be one
//of the parameters as I cannot initiate one if the method
//is recursive.
void multiplyMatrix2(int matrix1[rows][cols], int matrix2[rows][cols], int matrixf[rows][cols]) {
	//must be static for this recursive method
	//same use of loops/nesting for variables i,j,k
	//i,j for coordinates of matrixf
	//k to parse through row in matrix1 and parse through column in matrix2
	static int i = 0;
	static int j = 0;
	static int k = 0;

	if (i >= rows) {
		//all rows have already been parsed
		return;
	}
	//if not, code continues
	if (j < cols) {
		//keeps j in range of column of array
		if (k < cols) {
			//keeps k in range of column of array
			//same as sum+= in iterative function
			matrixf[i][j] += matrix1[i][k]*matrix2[k][j];
			k++;
			//recursive call
			multiplyMatrix2(matrix1, matrix2, matrixf);

		}
		//reset k, just like beginning of for loop does
		k = 0;
		j++;
		multiplyMatrix2(matrix1, matrix2, matrixf);
	}
	//reset j, just like beginning of for loop does
	j = 0;
	i++;
	multiplyMatrix2(matrix1, matrix2, matrixf);

}


//Question 7a: Fill (Pointer)
void fillMatrix2(int matrix[rows][cols]) {
	srand(1);
	int* rowPointer = NULL;
	for (int i=0; i < rows; i++) {
		//points to next location in array of pointers
		rowPointer = *(matrix + i);
		for (int j=0; j < rows; j++) {
			//points to the next pointer in the pointer in the array of pointers
			*(rowPointer + j) = rand() % 5 + 1;
		}
	}
}

//Question 7b: Print (Pointer)
void PrintMatrix2(int matrix[rows][cols]) {
	int* rowPointer = NULL;
	for (int i=0; i < rows; i++) {
		rowPointer = *(matrix + i);
		for (int j=0; j < cols; j++) {
			if (j != cols-1) {
				cout << *(rowPointer + j) << " ";
			}
			else {
				cout << *(rowPointer + j) << endl;
			}
		}
	}
	cout << endl;
}

//Question 7c: Transpose (Pointer)
void transposeMatrix2(int matrix[rows][cols]) {
	for (int i=0; i < rows; i++) {
		for (int j=i; j < cols; j++) {
			//since i and j need to be swapped, combine
			//rowPointer and colPointer into one term
			int temp = *(*(matrix + i) + j);
			*(*(matrix + i) + j) = *(*(matrix + j) + i);
			*(*(matrix + j) + i) = temp;
		}
	}
}

/*Question 8:
 * It is possible to print a 1D array to look like a matrix. But it will not have
 * the full capabilities of an ACTUAL matrix. It will be harder to access
 * values at your desired locations. For example, line breaks must be manually
 * broken at multiples of 5 (arbitrary number that would not exist in the context
 * of a 1D array.) And it would be extremely difficult to execute
 * the transposition and multiplication of matrices as there is not as clear of a pattern
 * as there is with a matrix.
 *
 * In short, to use the full implementations and capabilities of a matrix, you CANNOT
 * use a 1D array to substitute. However, it is possible to fill a 1D array and
 * print it so it looks like a matrix, as I've done below.
 */
void fillMatrix3(int arr[25]) {
	srand(1);
	for (int i=0; i < 25; i++) {
		arr[i] = rand() % 5 + 1;
	}
}

void PrintMatrix3(int arr[25]) {
	for (int i=0; i < 25; i++) {
		if ((i+1)%5 != 0) {
			cout << arr[i] << " ";
		}
		else {
			cout << arr[i] << endl;
		}
	}
	cout << endl;
}


int main() {
	int matrix[rows][cols];

	//Q2 call
	cout << "Filled and Printed Matrix: " << endl;
	fillMatrix(matrix);

	//Q3 call
	PrintMatrix(matrix);

	//Q4 call
	cout << "Transposed Matrix: " << endl;
	transposeMatrix(matrix);
	PrintMatrix(matrix);

	//Q5 call
//	Since multiplyMatrix returns a pointer to the third matrix,
//	we must first dereference that pointer to an actual 2D array
//	so we can input it into PrintMatrix
//	this was done because Q3 explicitly said to RETURN (not void)
	int** matrix2 = multiplyMatrix(matrix,matrix);
	int matrix3[rows][cols];
	for (int i=0; i < rows; i++) {
		for (int j=0; j < cols; j++) {
			matrix3[i][j] = matrix2[i][j];
		}
	}
	cout << "Multiplied Matrix: " << endl;
	PrintMatrix(matrix3);
	delete[] matrix2; //reclaim space

	//Q6 call
	//Empty matrix needed for recursive method
	int matrix4[rows][cols];
	cout << "Multiplied Matrix (Recursive): " << endl;
	multiplyMatrix2(matrix, matrix, matrix4);
	PrintMatrix(matrix4);

	//Q7 call
	cout << "Filled and Printed Matrix (Pointers): " << endl;
	fillMatrix2(matrix);
	PrintMatrix2(matrix);

	cout << "Transposed Matrix (Pointers): " << endl;
	transposeMatrix2(matrix);
	PrintMatrix2(matrix);

	//Q8 call
	int arr[25];
	cout << "Filled and Printed Matrix (1D): " << endl;
	fillMatrix3(arr);
	PrintMatrix3(arr);

}




