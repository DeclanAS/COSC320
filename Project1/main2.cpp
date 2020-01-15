#include <iostream>
#include <fstream>
#include <string.h>
#include <chrono>
#include "matrix.h"

/*	Name: Declan Sheehan
 *	Course: COSC320-001
 * Desc: This does the 2D linear regression for 
 * A file of your choice, then computes the 
 * 3D regression.
 */



int main (){
   //##################################
   //##                              ##
   //##      2D Regression Part      ##
   //##                              ##
   //##################################

   Matrix X;
   X.TwoDRegression();

   //##################################
   //##                              ##
   //##      3D Regression Part      ##
   //##                              ##
   //##################################
   std::ifstream infile("points100-3d.dat", std::ios_base::in);
   float c1, c2, c3; // Clear values.
   Matrix *A = new Matrix(100, 3, 0); // A
   Matrix *b = new Matrix(100, 1, 0); // b
   for(int a = 0; a < 100; a++){ // Fetches data from file.
      A->Insert(a, 2, 1.0); // Sets column 3 to all 1's.
      infile >> c1;
      infile >> c2;
      infile >> c3;
      A->Insert(a, 0, c1);
      A->Insert(a, 1, c2);
      b->Insert(a, 0, c3);
   }
   infile.close(); // Close file.


   //start = Timerstart(); // Time the regression.
   Matrix AT = (*A)^'T';
   Matrix Beta2(4, 4, 0);
   Beta2.Insert(3, 3, 1.0);
   /* "Pads" the 3x3 into a 4x4 */
   Matrix Beta = (AT * *A);
   for(int i = 0; i < 3; i++)
      for(int j = 0; j < 3; j++)
         Beta2.Insert(i, j, Beta.GetVal(i, j));

   /* "Unpads" the (now) 4x4 back to a 3x3 */
   
   Beta2 = Beta2.inverse();
   for(int i = 0; i < 3; i++)
      for(int j = 0; j < 3; j++)
         Beta.Insert(i, j, Beta2.GetVal(i, j));

   Beta = ((Beta * AT) * *b);
   //Elapsedtime(start);
   std::cout << "[3D] Aβ = [A]*[β]=[x] = b:" << std::endl;
   std::cout << Beta << std::endl; // Prints regression plane.

   delete A; // Deallocate memory.
   delete b;
   return 0;
}