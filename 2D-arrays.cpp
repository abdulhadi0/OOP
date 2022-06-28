#include <iostream>
#include <fstream>

using namespace std;

int** InputMatrix(ifstream& fin, int& rows, int& cols)
{
	fin >> rows;
	fin >> cols;

	int** Matrix = new int* [rows];
	int** endrows = Matrix + rows;

	for (; Matrix < endrows;Matrix++)
	{
		*(Matrix) = new int[cols];
	}
	Matrix = endrows - rows;

	for (; Matrix < endrows; Matrix++)
		for (int* col = *Matrix; col< *Matrix + cols; col++)
			fin >> *(col);

	Matrix = endrows - rows;
	return Matrix;
}

void OutputMatrix(int** Matrix, const int& rows, const int& cols)
{
	int** endrows = Matrix + rows;

	for (; Matrix < endrows; Matrix++)
	{
		for (int* col = *Matrix; col < *Matrix + cols; col++)
			cout << *(col) << "\t";
		cout << endl;
	}
	Matrix -= rows;
	cout << endl;
}

int** AddMatrix(int** MatrixA, int** MatrixB, const int& rows, const int& cols)
{
	int** AddMatrix = new int* [rows];
	int** endrows = AddMatrix + rows;
	for (; AddMatrix < endrows; AddMatrix++)
	{
		*(AddMatrix) = new int[cols];
	}
	AddMatrix = endrows - rows;
	
	for (; AddMatrix < endrows; AddMatrix++, MatrixA++, MatrixB++)
	{
		for (int* col = *AddMatrix; col < *AddMatrix + cols; col++)
		{
			*(col) = **MatrixA + **MatrixB;

			*MatrixA += 1;
			*MatrixB += 1;
		}
		*(MatrixA) -= cols;
		*(MatrixB) -= cols;
	}
	AddMatrix -= rows;
	MatrixA -= rows;
	MatrixB -= rows;

	return AddMatrix;
}

int** TransposeMatrix(int** Matrix, const int& rows, const int& cols)
{
	int tranRows = cols, tranCols = rows, c =0;
	int* count = &c;
	int** TranMatrix = new int* [tranRows];
	int** endrows = TranMatrix + tranRows;
	for (; TranMatrix < endrows; TranMatrix++)
	{
		*(TranMatrix) = new int[tranCols];
	}
	TranMatrix = endrows - cols;

	for (; TranMatrix < endrows; TranMatrix++,*count+=1)
	{
		for (int* col = *TranMatrix; col < *TranMatrix + tranCols; col++, Matrix++)
		{
			*Matrix += *count;
			*col = **Matrix;
			*Matrix -= *count;
		}
		Matrix -= rows;
	}

	TranMatrix -= tranRows;
	return TranMatrix;
}

bool IsSymmetric(int** Matrix, const int& rows, const int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (*(*(Matrix + i) + j) != *(*(Matrix + j) + i))
				return false;
		}
	}
	return true;
}

void InterchangeRows(int*& row1, int*& row2)
{
	int* tempptr = 0;
	tempptr = row1;
	row1 = row2;
	row2 = tempptr;
}
void InterchangeRows(int** Matrix, const int& rows, const int& cols)
{
	int row1 = 1;
	int row2 = 3;
	cout << "Interchanging Rows of Matrix A:\n";
	cout << "Row 1: " << row1 << endl;
	cout << "Row 2: " << row2 << endl;
	InterchangeRows(*(Matrix + row1-1), *(Matrix + row2-1));

}


int main()
{
	int rowsA = 0, colsA = 0, rowsB = 0, rowsC = 0, colsB = 0, colsC = 0;

	ifstream fin;
	fin.open("InputFile.txt");

	int** MatrixA = InputMatrix(fin, rowsA, colsA);
	cout << "Matrix A: \n";
	OutputMatrix(MatrixA, rowsA, colsA);

	int** MatrixB = InputMatrix(fin, rowsB, colsB);
	cout << "Matrix B: \n";
	OutputMatrix(MatrixB, rowsB, colsB);

	int** MatrixC = InputMatrix(fin, rowsC, colsC);
	cout << "Matrix C: \n";
	OutputMatrix(MatrixC, rowsC, colsC);

	cout << "A + B: \n";
	if (rowsA == rowsB && colsA == colsB)
		OutputMatrix(AddMatrix(MatrixA, MatrixB, rowsA, colsA), rowsA, colsA);
	else
		cout << "Addition not Possible.\n\n";

	cout << "A + C: \n";
	if (rowsA == rowsC && colsA == colsC)
		OutputMatrix(AddMatrix(MatrixA, MatrixC, rowsA, colsA), rowsA, colsA);
	else
		cout << "Addition not Possible.\n\n";

	cout << "Transpose of A: \n";
	OutputMatrix(TransposeMatrix(MatrixA, rowsA, colsA), colsA, rowsA);

	cout << "Transpose of C: \n";
	OutputMatrix(TransposeMatrix(MatrixC, rowsC, colsC), colsC, rowsC);

	if (IsSymmetric(MatrixA, rowsA, colsA))
		cout << "Matrix A is Symmetric.\n\n";
	else
		cout << "Matrix A is NOT Symmetric.\n\n";

	if (IsSymmetric(MatrixB, rowsB, colsB))
		cout << "Matrix B is Symmetric.\n\n";
	else
		cout << "Matrix B is NOT Symmetric.\n\n";

	InterchangeRows(MatrixA, rowsA, colsA);
	OutputMatrix(MatrixA, rowsA, colsA);

	for (int i = 0; i < rowsA; i++)
		delete[] * (MatrixA + i);
	
	delete[] MatrixA;

	for (int i = 0; i < rowsB; i++)
		delete[] * (MatrixB + i);

	delete[] MatrixB;

	for (int i = 0; i < rowsC; i++)
		delete[] * (MatrixC + i);

	delete[] MatrixC;
}