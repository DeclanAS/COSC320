#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

/*	Name: Declan Sheehan
 *	Course: COSC320-001
 *	Desc: Class declaration for Matrix.
 */


class Matrix{
private:
	int **mat;
	unsigned long int rowsize;
	unsigned long int colsize;

public:
	Matrix();
	Matrix(unsigned long int rsize, unsigned long int csize, bool solution);
	~Matrix();
	void IMatrix();
	void DMatrix();
	void TMatrix(bool Up);
	friend std::ostream& operator<< (std::ostream& os, const Matrix& matrix);
	friend Matrix operator+ (const Matrix& matrixa, const Matrix& matrixb);
	friend Matrix operator- (const Matrix& matrixa, const Matrix& matrixb);
	friend Matrix operator* (const Matrix& matrixa, const Matrix& matrixb);
	friend Matrix operator* (const int& c, const Matrix& matrixa);
};
#endif
