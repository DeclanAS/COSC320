#include <iostream>
#include <chrono>
#include "matrix.h"

#define time_datatype std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1, 1000000000> > >

/*	Name: Declan Sheehan
 *	Course: COSC320-001
 *	Desc: The time (chrono) functions are in this file.
 *	In addition, you're not going read this sentence, but
 *	the main's testing harness is in the main, followed by
 *	addition and multiplication execution time testing.
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

int main (){
	srand(time(NULL));
	auto start = Timerstart();
	Elapsedtime(start);
	Matrix *A = new Matrix(2, 2, false);
	std::cout << *A << std::endl;
	Matrix C = (25 * *A);
	std::cout << C << std::endl;
	delete A;

	Matrix *K = new Matrix(3, 3, true);
	std::cout << "Base Matrix:\n" << *K << std::endl;
	K->DMatrix();
	std::cout << "Diagonal Matrix:\n" << *K << std::endl;
	K->IMatrix();
	std::cout << "Identity Matrix:\n" << *K << std::endl;
	Matrix L = (21 * *K);
	std::cout << L << std::endl;
	delete K;
	Matrix *P = new Matrix(3, 3, true);
	P->TMatrix(true);
	std::cout << "Triangular Upper Matrix:\n" << *P << std::endl;
	delete P;
	Matrix *M = new Matrix(3, 3, false);
	Matrix *N = new Matrix(3, 3, false);
	std::cout << "Matrix N:\n" << *N << "\n" << "Matrix M:\n" << *M << std::endl;
	std::cout << "M * N = \n";
	Matrix Z = (*N * *M);
	std::cout << Z << std::endl;
	delete M;
	delete N;

	Matrix *V = new Matrix(3, 1, false);
	std::cout << "Vector:\n" << *V << "\n" << (2 * *V) << std::endl;
	delete V;

	std::cout << "Matrix Multiplication (nxn):\n"; // to 10240
	for(int i = 5; i <= 2560; i*=2){
			Matrix *A;
			Matrix *B;
			std::cout << "Size [" << i << "] ";
			A = new Matrix(i, i, false);
			B = new Matrix(i, i, false);
			start = Timerstart();
			Matrix C = (*A * *B);
			Elapsedtime(start);
			delete A;
			delete B;
	}

	std::cout << "Matrix Addition (nxn):\n";
	for(int i = 5; i <= 40960; i*=2){
		Matrix *X;
		Matrix *Y;
		std::cout << "Size [" << i << "] ";
		X = new Matrix(i, i, false);
		Y = new Matrix(i, i, false);
		start = Timerstart();
		Matrix C = (*X + *Y);
		Elapsedtime(start);
		delete X;
		delete Y;
	}

	return 0;
}
