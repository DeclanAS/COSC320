#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include "matrix.h"
#define time_datatype std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1, 1000000000> > >

/*	Name: Declan Sheehan
 *	Course: COSC320-001
 *	Desc: Contains all of the definitions for
 *	the class Matrix.
 */

time_datatype Timerstart(){
	auto start = std::chrono::system_clock::now();
	return start;
}

void Elapsedtime(time_datatype start){
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << "Execution time: " << elapsed_seconds.count() << "s\n";
}


Matrix::Matrix() : rowsize(1), colsize(1){
	mat = new float*[rowsize];
	for(int i = 0; i < rowsize; i++)
		mat[i] = new float[colsize];
	mat[0][0] = 0;
}

// Aβ = [100x2]*[β]=[x] = b.
// βˆ = (A^T * A)^-1 * (A^T * b);
// x = (A^T * A)^-1 * (A^T  * y);

Matrix& Matrix::operator=(const Matrix& m){
	Matrix cp(m);
	rowsize = m.rowsize;
	colsize = m.colsize;
	float** arr = new float*[rowsize];
	for(int i = 0; i < rowsize; i++)
		arr[i] = new float[colsize]();
    mat = arr;

	float** temp = mat;
	mat = cp.mat;
	cp.mat = temp;

}

Matrix::Matrix(const Matrix& cp){
	rowsize = cp.rowsize;
	colsize = cp.colsize;
	float** arr = new float*[rowsize];
	for(int i = 0; i < rowsize; i++)
		arr[i] = new float[colsize]();
    mat = arr;
	for(int i = 0; i < cp.rowsize; i++)
		for (int j = 0; j < cp.colsize; j++)
			mat[i][j] = cp.mat[i][j];
}


Matrix::Matrix(unsigned long int rsize, unsigned long int csize, int selection){
srand(time(0));
if(rsize < 1 || csize < 1){
		std::cout << "Invalid matrix." << std::endl;
		exit (1);
}

	rowsize = rsize;
	colsize = csize;
	mat = new float *[rsize];

if(selection == 0){
	for(int i = 0; i < rsize; i++){
			mat[i] = new float[csize];
			for(int k = 0; k < csize; k++)
					mat[i][k] = 0.0;
	}
} else if (selection == 1){
	for(int i = 0; i < rsize; i++){
		mat[i] = new float[csize];
		for(int k = 0; k < csize; k++)
			mat[i][k] = (float) rand() / (float) rand();
		}
} else if (selection == 2){
	for(int i = 0; i < rsize; i++){
		mat[i] = new float[csize];
		for(int k = 0; k < csize; k++)
			mat[i][k] = 0.0;
	}

	for(int i = 0; i < rsize; i++)
		for(int k = i; k < csize; k++)
			mat[i][k] = mat[k][i] = (float) rand() / (float) rand();
	}
}

void Matrix::Insert(int i, int k, float num){
	mat[i][k] = num;
}

float Matrix::GetVal(int i, int k){
	return mat[i][k];
}

void Matrix::Determinant(){
	int Det = 0;
	if(rowsize != colsize)
		std::cout << "Non-Square, cannot be invertible.\n";
	if(rowsize == 2 && colsize == 2){
		Det = (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
		if(Det == 0)
			std::cout << "Matrix is not invertible.\n";
		else
			std::cout << "Matrix is invertible.\n";
	} else if (rowsize == 3 && colsize == 3){
		Det = mat[0][0] * mat[1][1] * mat[2][2]
			+ mat[0][1] * mat[1][2] * mat[2][0]
			+ mat[0][2] * mat[1][0] * mat[2][1]
			- (mat[0][2] * mat[1][1] * mat[2][0]
			+  mat[0][0] * mat[1][2] * mat[2][1]
			+  mat[0][1] * mat[1][0] * mat[2][2]);
		if(Det == 0)
			std::cout << "Matrix is not invertible.\n";
		else
			std::cout << "Matrix is invertible.\n";
	} else {
		int i, j, count;
		for(i = 0; i < rowsize; i++){
			for(j = 0; j < colsize; j++){
				Det += mat[i][j];
				
			}
			if(Det == 0)
				std::cout << "Matrix is not invertible.\n";
			else
				count++;
		}
		if(count == rowsize -1)
			std::cout << "Matrix is invertible.\n";
	}
}



void Matrix::TwoDRegression(){
	int datasize;
   	std::cout << "Enter the size of the data: ";
   	std::cin >> datasize;
   	std::string filename;
   	std::cout << "[2D] Enter the size of the data we'll input: ";
   	std::cin >> filename;
   	std::ifstream infile(filename); // Opens data file.
   	if(!infile.is_open()){
      	std::cout << "File Opening Error.\n";
      	exit (1);
   	}
   	float c1, c2; // Our "Buffers" to read the files.
   	Matrix *A = new Matrix(datasize, 2, 0); // A
   	Matrix *b = new Matrix(datasize, 1, 0); // b

   	for(int i = 0; i < datasize; i++){ // Fills A & b with data from file.
      	infile >> c1;
      	infile >> c2;
      	A->Insert(i, 0, c1);
      	b->Insert(i, 0, c2);
      	A->Insert(i, 1, 1.0);
   	}
   	infile.close();
   	auto start = Timerstart();
   	Matrix AT = (*A)^'T';
   	Matrix Beta = (((AT * *A).inverse() * AT) * *b);
   	Elapsedtime(start);
   	std::cout << "[2D] Aβ = [A]*[β]=[x] = b:" << std::endl;
   	std::cout << Beta << std::endl; // Prints regression line.

   	delete A;
   	delete b;
}


Matrix operator^ (const Matrix& m, const char& exp){
	Matrix matrixb(m.colsize, m.rowsize, 0);
	for(int i = 0; i < m.rowsize; i++)
		for(int k = 0; k < m.colsize; k++)
			matrixb.mat[k][i] = m.mat[i][k];

	return matrixb;
}


Matrix& Matrix::inverse(){
	// Please use a 2^n x 2^n matrix.
	int row = rowsize;
	int col = colsize;
	int row2 = row/2;
	int col2 = col/2;

	if(row == 1 && col == 1){
			if(mat[0][0] != 0) // Cannot divide by 0.
				mat[0][0] = (1.0 / mat[0][0]);
			return *this;
	}



	Matrix B(row2, col2, 0);
	Matrix C(row2, col2, 0);
	Matrix D(row2, col2, 0);
	Matrix CT(row2, col2, 0);
	for(int i = 0; i < row2; i++)
		for(int j = 0; j < col2; j++)
			B.mat[i][j] = mat[i][j];

	for(int i = 0; i < row2; i++)
		for(int j = (col2); j < col; j++)
			CT.mat[i][j - col2] = mat[i][j];

	for(int i = (row2); i < row; i++)
		for(int j = 0; j < col2; j++)
			C.mat[i - row2][j] = mat[i][j];

	for(int i = (row2); i < row; i++)
		for(int j = (col2); j < col; j++)
	 		D.mat[i - row2][j - col2] = mat[i][j];

	Matrix BI = (B.inverse());
	Matrix W = (C) * (BI);
	Matrix WT = W^'T';
	Matrix X = W * CT;
	Matrix S = D - X;
	Matrix V = (S.inverse());
	Matrix Y = V * (W);
	Matrix YT = Y^'T';
	Matrix T = (-1 * YT);
	Matrix U = (-1 * Y);
	Matrix Z = (WT) * (Y);
	Matrix R = BI + Z;

	for(int i = 0; i < row2; i ++)
		for(int j = 0; j < col2; j++)
			mat[i][j] = R.mat[i][j];


	for(int i = row2; i < row; i++)
		for(int j = 0; j < col2; j++)
			mat[i][j] = U.mat[i - row2][j];


	for(int i = 0; i < row2; i++)
		for(int j = col2; j < col; j++)
			mat[i][j] = T.mat[i][j - col2];


	for(int i = row2; i < row; i++)
		for(int j = col2; j < col; j++)
			mat[i][j] = V.mat[i - row2][j - col2];

	return *this;
}


void Matrix::IMatrix(){ // Identity Matrix
	for(int i = 0; i < this->rowsize; i++)
		this->mat[i][i] = 1;
}

void Matrix::DMatrix(){ // Diagonal Matrix
	srand(time(0));
	for(int i = 0; i < this->rowsize; i++)
		this->mat[i][i] = (float) rand() / (float) rand();
}

void Matrix::TMatrix(bool Up){ // Triangular Matrix
	srand(time(0));
	if(Up){
		for(int i = 0; i < this->rowsize; i++)
			for(int k = i; k < this->rowsize; k++)
				this->mat[i][k] = (float) rand() / (float) rand();
	} else {
		for(int i = this->rowsize-1; i>=0; i--)
			for(int k = i; k>=0; k--)
				this->mat[i][k] = (float) rand() / (float) rand();
	}
}

Matrix::~Matrix(){ // Destructor
	for(int i = 0; i < rowsize; i++)
		delete[] mat[i];
	delete[] mat;
}

std::ostream& operator<< (std::ostream& os, const Matrix& matrix){
for(int i = 0; i < matrix.rowsize; i++){
	for(int k = 0; k < matrix.colsize; k++)
		os << matrix.mat[i][k] << " ";
	std::cout << "\n";
	}
	return os;
}

Matrix operator+ (const Matrix& matrixa, const Matrix& matrixb){
	if(matrixa.rowsize != matrixb.rowsize || matrixa.colsize != matrixb.colsize){
		std::cout << "Invalid matrix size combination.";
		exit (1);
	}

	Matrix matrixc(matrixa.rowsize, matrixa.colsize, 0);
	for(int i = 0; i < matrixa.rowsize; i++)
		for(int k = 0; k < matrixa.colsize; k++)
			matrixc.mat[i][k] = matrixa.mat[i][k] + matrixb.mat[i][k];
	return matrixc;
}

Matrix operator- (const Matrix& matrixa, const Matrix& matrixb){
	if(matrixa.rowsize != matrixb.rowsize || matrixa.colsize != matrixb.colsize){
		std::cout << "Invalid matrix size combination.";
		exit (1);
	}

	Matrix matrixc(matrixa.rowsize, matrixa.colsize, 0);
	for(int i = 0; i < matrixa.rowsize;i++)
		for(int k = 0; k < matrixa.colsize; k++)
			matrixc.mat[i][k] = matrixa.mat[i][k] - matrixb.mat[i][k];
	return matrixc;
}

Matrix operator* (const Matrix& matrixa, const Matrix& matrixb){
	if(matrixa.colsize != matrixb.rowsize){
		std::cout << "Invalid matrix size combination.";
		exit (1);
	}
	Matrix matrixc(matrixa.rowsize, matrixb.colsize, 0);
	for(int i = 0; i < matrixa.rowsize; i++)
		for(int k = 0; k < matrixb.colsize; k++)
			for(int p = 0; p < matrixb.rowsize; p++)
				matrixc.mat[i][k] += (matrixa.mat[i][p] * matrixb.mat[p][k]);

	return matrixc;
}

Matrix operator* (const float& c, const Matrix& matrixa){// Scalar Mult.
	Matrix matrixb(matrixa.rowsize, matrixa.colsize, 0);
	for(int i = 0; i < matrixa.rowsize; i++)
		for(int k = 0; k < matrixa.colsize; k++)
			matrixb.mat[i][k] = (matrixa.mat[i][k] * c);

	return matrixb;
}
