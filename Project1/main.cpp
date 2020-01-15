#include <iostream>
#include <chrono>
#include "matrix.h"

/*	Name: Declan Sheehan
 *	Course: COSC320-001
 *  Desc: In main1.cpp, it tests the code given
 *	a handfull of matrices.
 */


int main (){
	srand(time(NULL));

	int count = 0;
	Matrix *A = new Matrix (2, 2, 0);
	Matrix *B = new Matrix (2, 2, 0);
	Matrix *Z = new Matrix (2, 2, 2);
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++){
			A->Insert(i, j, count++);
			B->Insert(i, j, count++);
		}

	std::cout << "Given Matrix A :\n" << *A << std::endl;
	std::cout << "Given Matrix B :\n" << *B << std::endl;
	std::cout << "Given Matrix Z :\n" << *Z << std::endl;

	Matrix C = Z->inverse();
	std::cout << "Z^-1:\n" << C << std::endl;


	Matrix T = (*A)^'T';
	std::cout << "A^T:\n" << T << std::endl;


	Matrix D = (*A * *B);
	std::cout << "A * B:\n" << D << std::endl;


	Matrix S = (*A - *B);
	std::cout << "A - B:\n" << S << std::endl;



	delete A;
	return 0;
}