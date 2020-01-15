#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

/*	Name: Declan Sheehan
 *	Course: COSC320-001
 *	The class definition for Matrix.
 */

class Matrix{
private:
	float **mat;
	unsigned long int rowsize;
	unsigned long int colsize;

public:
	Matrix();
	Matrix(unsigned long int rsize, unsigned long int csize, int selection);
	Matrix(const Matrix&);
	~Matrix();
	void IMatrix(); // Makes Identity Matrix W/ Matrix(n, n, true);
	void DMatrix(); // Creates Diagonal Matrix W/ Matrix(n, n, true);
	void TMatrix(bool Up); // Creates U/L Matrix W/ Matrix(n, n, true);
  	void Insert(int i, int k, float num);
  	void TwoDRegression();
  	void Determinant(); // Extra Credit (Invertible/NonInvertible.)
  	float GetVal(int i, int k);
	Matrix& inverse();
	Matrix& operator = (const Matrix&);
	friend std::ostream& operator<< (std::ostream& os, const Matrix& matrix);
	friend Matrix operator+ (const Matrix& matrixa, const Matrix& matrixb);
	friend Matrix operator- (const Matrix& matrixa, const Matrix& matrixb);
	friend Matrix operator* (const Matrix& matrixa, const Matrix& matrixb);
	friend Matrix operator* (const float& c, const Matrix& matrixa);
	friend Matrix operator^ (const Matrix& m, const char& exp);
};
#endif
