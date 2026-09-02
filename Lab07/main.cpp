#include <iostream>
#include <limits.h>
#include <fstream>
#include <string.h>
#include <chrono>
#include <cmath>
#include "hash.h"

	/*	Name: Declan Sheehan
	 *	Course: COSC320-001
	 *	Desc: This spaghetti you see infront of you is:
	 *	ItoHex: Converts size_t to hexadecimal.
	 *	str_hash_function1: First custom hashing function.
	 *	str_hash_function2: Second custom hasing function.
	 * hash_file: Hashes a file w/ both functions.
	 *	Test_Hashes: Test harness.
	 */

	/* I don't like my custom hash functions. They
	 *	look like spaghetti. All I know is they work.
	 */

	 // int = 4;
	 // float = 4;
	 // char = 1;

struct A{ // 9 PADS TO 12.
	int jenny;
	float rootbeer;
	char idiosyncratic;
};


std::string ItoHex(size_t value){
	std::stringstream ss;
	ss << std::hex << value;
	std::string result( ss.str() );
	// std::cout << "Value " << value <<
	// " in hex: " << result << std::endl;
	return result;
}

unsigned long long multi_hash(size_t value){
	size_t w = 31; // Cannot go over 31. (1 << 32) -> 0.
	float A = 0.69337613708;
	unsigned long long a = 67108864;
	unsigned long long hash_value = value * a * A;
	hash_value = hash_value & (1 << w) - 1;
	hash_value = hash_value >> (w-17);
	return hash_value;
}

size_t hash_division(size_t k, size_t s){
	return k % s;
}

size_t str_hash_function1(char* str){ // Spagetti Hash Function 1
	size_t hash_value, ASCII, i, count, A_val;
	hash_value = ASCII = i = count = A_val = 0;
	char bfr;
	while(str[i] != '\0'){
		bfr = static_cast<char>(str[i]);
		ASCII = ASCII + static_cast<char>(str[i]);
		if((str[i] >= '0' && str[i] <= '0') && (count%2 == 0))
			if(bfr % 2 == 0)
				A_val += (count + bfr + 13);
			else if(bfr % 3 == 0)
				A_val += (count + bfr + 31);
			else
				A_val += (count + bfr + 97);
		else if((str[i] >= '0' && str[i] <= '0') && !(count%2 == 0))
			if(bfr % 3 == 0)
				A_val += (count + bfr + 97);
			else if(bfr % 2 == 0)
				A_val += (count + bfr + 13);
			else
				A_val += (count + bfr + 31);
		else if (!(str[i] >= '0' && str[i] <= '0') && (count%2 == 0))
			if(bfr % 2 == 0)
				A_val += (count + bfr + 107);
			else if (bfr % 3 == 0)
				A_val += (count + bfr + 211);
			else
				A_val += (count + bfr + 397);
		else
			A_val += (count % bfr);
		count++;
		i++;
	}

	if(count == 0){
		hash_value = 2999 * count + ASCII + A_val;
	} else if (count%2 == 0) {
		hash_value = 1777 * count + ASCII + A_val;
	} else {
		hash_value = 7717 * count + ASCII + A_val;
	}
	if(count == 0)
		hash_value = 1777; // Could be zero.
	if(count != 0)
		hash_value = hash_value + (static_cast<char>(str[0]) - (bfr) * 42);
	if(count > 4){
		int fourth = count/4;
		hash_value = hash_value + (static_cast<char>(str[fourth]) +
			static_cast<char>(str[fourth*2]) + static_cast<char>(str[fourth*3]));
	}

	return hash_value;
}

size_t str_hash_function2(char* str){ // Spagetti Hash Function 2.
	size_t hash_value, ASCII, total, count, i;
	hash_value = ASCII = total = count = i = 0;
	char bfr, bfr_m1;
	while(str[i] != '\0')
		i++;
	total = i;
	i = 0;

	while(str[i] != '\0'){
		if(i > 0)
			bfr_m1 = static_cast<char>(str[i-1]);
		bfr = static_cast<char>(str[i]);
		ASCII += bfr;
		if(total % 2 == 0){
			hash_value += (bfr + bfr_m1 + 7);
		} else if (total % 2 == 1){
			if(str[i] >= '0' && str[i] <= '9'){
				hash_value += (bfr * 3);
				if(i > 0)
					hash_value += ((bfr + bfr_m1) * (bfr/bfr_m1 + 31));
			} else {
				hash_value += (bfr * 7);
				if(i > 0)
					hash_value += ((bfr + bfr_m1) * (bfr/bfr_m1 + 17));
			}
		}
		i++;
	}
	if(total%2 == 0)
		hash_value += ASCII + total * 1337;
	if(total%2 == 1)
		hash_value += ASCII + total * 997;
	if(total > 4){
		int fourth = count/4;
		hash_value += (static_cast<char>(str[fourth]) +
		static_cast<char>(str[fourth*2]) + static_cast<char>(str[fourth*3]) * bfr);
	} else {
		hash_value += (static_cast<char>(str[0]) + static_cast<char>(str[1])
			+ (static_cast<char>(str[total-1])));
	}
	return hash_value;
}

size_t hash_file(char* file_name, bool type){ // Hashes entire file.
	std::ifstream infile(file_name); // Open File.
	if(!infile.is_open()){ // Error with file.
		printf("%s Could not be accessed.", file_name);
		exit(1);
	}
	// Allocating a 4096x30 char array.ff0000 color
	char** str;
	str = new char*[4096];
	for(int i = 0; i < 4096; i++)
		str[i] = new char[30];

	// Set values.
	int a, b, hash_value;
	a = b = hash_value = 0;

	// Reading in the file & ...
	while(!infile.eof()){ // hashing line by line.
		infile.get(str[a][b]);
		if(str[a][b] == '\n'){
			if(type == true)
				hash_value += str_hash_function1(str[a]);
			else
				hash_value += str_hash_function2(str[a]);
			a++;
			b = 0;
		} else {
			b++;
		}
	}

	infile.close(); // Close file.
	// Prints out total hash of the file.
	printf("The hash of the file %s is %d.\n", file_name, hash_value);

	for (int i = 0; i < 4096; i++)// Deallocate
		delete[] str[i];
	delete [] str;

	return hash_value;
}


void Test_Hashes(char* file_name){ // Tests hashes on test-file.
	std::ifstream infile(file_name); // Open File.
	if(!infile.is_open()){ // Error with file.
		printf("%s Could not be accessed.", file_name);
		exit(1);
	}
	char** str = new char*[4096];
	for(int i = 0; i < 4096 ; i++)
		str[i] = new char[30];

	int a, b;
	a = b = 0;
	while(!infile.eof()){ // Read in file contents.
		infile.get(str[a][b]);
		if(str[a][b] == '\n'){
			a++;
			b = 0;
		} else {
			b++;
		}
	}

	a = b = 0;
	int val = 0;
	std::cout << "\nUsing Hash Function 1:\n";
	while(str[a][0] != '\0'){
		val = str_hash_function1(str[a]);
		int pos = strcspn(str[a], "\n");
		std::cout << "The (hex) hash value of \"";

		for(int i = 0; i < pos; i++)
			std::cout << str[a][i];

		std::cout << "\" is " << ItoHex(val) << ".\n";
		a++;
	}
	std::cout << "\nUsing Hash Function 2:\n";
	a = b = 0;
	while(str[a][0] != '\0'){
		val = str_hash_function2(str[a]);
		int pos = strcspn(str[a], "\n");
		std::cout << "The (hex) hash value of \"";

		for(int i = 0; i < pos; i++)
			std::cout << str[a][i];

		std::cout << "\" is " << ItoHex(val) << ".\n";
		a++;
	}

	infile.close();

	for(int i = 0; i < 4096; i++)
		delete[] str[i];
	delete[] str;
}

;
int main (int argc, char* argv[]){
	// Extra Credit:
	struct A tommy_tutone;
	tommy_tutone.jenny = 8675309;
	tommy_tutone.rootbeer = 1010101;
	tommy_tutone.idiosyncratic = 'Q';

	printf("Jenny Jenny, Who can I turn to %d\n", tommy_tutone.jenny);
	printf("Rootbeer float: %d\n",tommy_tutone.rootbeer );
	printf("Random character: %c\n", tommy_tutone.idiosyncratic);

	char BONUS[sizeof(tommy_tutone)];
	memcpy(BONUS, &tommy_tutone, sizeof(tommy_tutone));

	size_t Bonus_value = str_hash_function1(BONUS);

	std::cout << "The hash of the stuct is: " << Bonus_value << std::endl;

	// Demonstate the Multiplication hash.
	std::cout << "Multiplication Hash:\n";
	for(int i = 4; i <= 8; i++){
		size_t abc = multi_hash(i);
		std::cout << "The multi-hash of " << i << " is " << abc << std::endl;
	}

	if(argc != 2){ // Argument Check.
		printf("Not enough/too many arguments.\n");
		exit(1);
	}

	Test_Hashes(argv[1]); // Tests a test file.
	std::cout << "\n";
	// Collects the hash of the cmd line file.
	// using function 1.
	size_t val1 = hash_file(argv[1], true);
	std::cout << "The hexadecimal value of " << val1
	<< " is: " << ItoHex(val1) << "\n";
	std::cout << "\n";
	// Collects the hash of the cmd line file.
	// using function 2.
	size_t val2 = hash_file(argv[1], true);
	std::cout << "The hexadecimal value of " << val2
	<< " is: " << ItoHex(val2) << std::endl;

	return 0;
}
