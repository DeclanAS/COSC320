#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>
#include <vector>
#include <cmath>
#include <fstream>
#include <chrono> // Timing
#include "dictionary.h"

/* Custom Elapsed-Time Function */
void CElapsedtime(std::string str, time_datatype start){
   auto end = std::chrono::system_clock::now();
   std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << str << elapsed_seconds.count() << "s\n";
}

 /*	Name: Declan Sheehan
 	Course: COSC320-001
 	Desc: In the main, We create an instance of the dictionary,
 	then load in file `english.txt` using readEnglish().
 	After that, we load statistics about the hashtable using
 	statistics(). Lastly, we prompt the user to write a sentence
 	in which the program checks if it is in the dictionary, then
 	prints out corrections if said word was mispelled.

 */

bool contains(std::string word, std::string list[]){
	for(int i = 0; i < 10; i++)
		if(list[i] == word)
			return true;
		else
			;
	return false;
}

int main(){
	/* Declares file name & loads in dictionary */
	dictionary *Spellchecker = new dictionary;
	char file_name[] = "english.txt";
	std::cout << "﹢---------------------------﹢\n";
	printf("| Time to insert %s |\n", file_name);
	std::cout << "﹢---------------------------﹢\n| ";
	Spellchecker->readEnglish(file_name);
	std::cout << "﹢---------------------------﹢\n";
	Spellchecker->statistics();

	std::string sentence[64];
	std::string misspelled[20];
	std::string corrected[20];
	int errorpositions[20] = {0};
	std::string str;
	std::cout << "------------------------------------------\n";
	std::cout << "Enter something:\n>";
	std::getline(std::cin, str);
	std::istringstream is(str);
	std::string word;
	int i = 0, k = 0, p = 0;
	std::cout << "\n";
	/* Streams the sentence into a loop to print */
	while(is >> word)
		sentence[i++] = word;
	for(int j = 0; j < i; j++){
		transform(sentence[j].begin(), sentence[j].begin()+1, sentence[j].begin(), ::toupper);
		std::string FirstCap = sentence[j];
		transform(sentence[j].begin(), sentence[j].end(), sentence[j].begin(), ::toupper);
		std::string Upper = sentence[j];
		transform(sentence[j].begin(), sentence[j].end(), sentence[j].begin(), ::tolower);
		if((Spellchecker->findword(sentence[j])) == false && (Spellchecker->findword(Upper)) == false && (Spellchecker->findword(FirstCap)) == false){
			misspelled[k++] = sentence[j];
			errorpositions[p++] = j;
			std::cout << "\033[1;31m" << sentence[j] << "\033[0m ";
		} else {
			std::cout << sentence[j] << " ";
		}
	}
	/* For-loops the misspelled words for changes */
	// TO CHANGE TO A 1-EDIT DISTANCE, CHANGE THE 2 TO A 1 BELOW
	printf("\nThere were %d misspelled word(s) in your sentence.\n", k);
	if(k > 0){
		for(int i = 0; i < k; i++){
			corrected[i] = Spellchecker->editdistance(misspelled[i], 2, i); // HERE
			printf("\n");
		}
	std::cout << "\n";

	for(int v = 0; v < p; v++)
		sentence[errorpositions[v]] = corrected[v];

	i = 0;
	bool skip = false;
	/* Checks if `no-corrections` for any misspelled word was made */
	if(contains(";", corrected))
		skip = true;
	/* Skips printout of the sentence if so*/
	if(!skip){
		printf("What you meant to say:\n\"");
		for(int v = 0; !sentence[v].empty(); v++){
			if(!sentence[v+1].empty()){
				if(contains(sentence[v], corrected))
					std::cout << "\033[1;32m" << sentence[v] << "\033[0m ";
				else
					std::cout << sentence[v] << " ";
			} else {
				if(contains(sentence[v], corrected))
					std::cout << "\033[1;32m" << sentence[v] << "\033[0m.\"";					else
				std::cout << sentence[v] << ".\"";
				}
			}
		} else {
			printf("There were words that couldn't be corrected, cannot print out correction.\n");
		}
	}

	/* Allows user to search the dictionary to test it out */
	std::string WordSearch = "";
	printf("\nIf you have added a word into the dictionary, check here\n");
	while(true){
		printf("\nEnter any word; to break loop type \"$\":\n>");
		std::cin >> WordSearch;
		if(WordSearch == "$")
			break;
		auto cstart = Timerstart();
		bool found = Spellchecker->findword(WordSearch);
		CElapsedtime("Search time: ", cstart);
		if(found == true)
			std::cout << WordSearch << " was found.\n";
		else if (found == false)
			std::cout << WordSearch << " was not found.\n";
	}
	
	delete Spellchecker;
	return 0;
}
