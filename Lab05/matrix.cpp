#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include "matrix.h"

/*	Name: Declan Sheehan
 *	Course: COSC320-001
 *	Desc: Each the Matrix class functions are
 *	defined here.	
 *	
 */


Matrix::Matrix() : rowsize(1), colsize(1){
	mat = new int*[rowsize];
	for(int i = 0; i < rowsize; i++)
		mat[i] = new int[colsize];
	mat[0][0] = 0;
}

Matrix::Matrix(unsigned long int rsize, unsigned long int csize, bool solution){
	srand(time(0));
	if(rsize < 1 || csize < 1){
		std::cout << "Invalid matrix." << std::endl;
		exit (1);
	} else if (rsize == 1 && csize == 1){
		std::cout << "Invalid matrix." << std::endl;
		exit (1);
	}
	rowsize = rsize;
	colsize = csize;
	mat = new int *[rsize];

	if(solution){
		for(int i = 0; i < rsize; i++){
			mat[i] = new int[csize];
			for(int k = 0; k < csize; k++)
				mat[i][k] = 0;
		}
	} else {
		for(int i = 0; i < rsize; i++){
			mat[i] = new int[csize];
			for(int k = 0; k < csize; k++)
				mat[i][k] = rand() % 100;
		}
	}
}

void Matrix::IMatrix(){ // Identity Matrix
	for(int i = 0; i < this->rowsize; i++)
		this->mat[i][i] = 1;
}

void Matrix::DMatrix(){ // Diagonal Matrix
	srand(time(0));
	for(int i = 0; i < this->rowsize; i++)
		this->mat[i][i] = rand() % 100;
}

void Matrix::TMatrix(bool Up){ // Triangular Matrix
	srand(time(0));
	if(Up){
		for(int i = 0; i < this->rowsize; i++)
			for(int k = i; k < this->rowsize; k++)
				this->mat[i][k] = rand() % 100;
	} else {
		for(int i = this->rowsize-1; i>=0; i--)
			for(int k = i; k>=0; k--)
				this->mat[i][k] = rand() % 100;
	}
}

Matrix::~Matrix(){ // Destructor
	for(int i = 0; i < rowsize; i++)
		delete[] mat[i];
	delete[] mat;
}

std::ostream& operator<< (std::ostream& os, const Matrix& matrix){
	// ┎┒
	// ┖┚
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

	Matrix matrixc(matrixa.rowsize, matrixa.colsize, true);
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

	Matrix matrixc(matrixa.rowsize, matrixa.colsize, true);
	for(int i = 0; i < matrixa.rowsize; i++)
		for(int k = 0; k < matrixa.colsize; k++)
			matrixc.mat[i][k] = matrixa.mat[i][k] - matrixb.mat[i][k];
	return matrixc;
}

Matrix operator* (const Matrix& matrixa, const Matrix& matrixb){
	if(matrixa.colsize != matrixb.rowsize){
		std::cout << "Invalid matrix size combination.";
		exit (1);
	}
	Matrix matrixc(matrixa.rowsize, matrixb.colsize, true);
	for(int i = 0; i < matrixa.colsize; i++)
		for(int k = 0; k < matrixb.colsize; k++)
			for(int p = 0; p < matrixa.colsize; p++)
				matrixc.mat[i][k] += (matrixa.mat[i][p] * matrixb.mat[p][k]);
	return matrixc;
}

Matrix operator* (const int& c, const Matrix& matrixa){// Scalar Mult.
	std::cout << "Scalar: " << c << std::endl;
	Matrix matrixb(matrixa.rowsize, matrixa.colsize, true);
	for(int i = 0; i < matrixa.rowsize; i++)
		for(int k = 0; k < matrixa.colsize; k++)
			matrixb.mat[i][k] = (matrixa.mat[i][k] * c);

	return matrixb;
}
