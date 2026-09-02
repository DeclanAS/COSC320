#ifndef DICTIONARY_H
#define DICTIONARY_H
#define time_datatype std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1, 1000000000> > >

/* Name: Declan Sheehan
   Course: COSC320-001
   Desc: The dictionary.h file holds all functions
   in order for the dictionary to run. Some of them
   are more spaghetti-like than others.
*/

const int DSIZE = 8192; // Size of our hashtable.
const char alp[] = "abcdefghijklmnopqrstuvwxyz";

time_datatype Timerstart(){ // Time start function.
   auto start = std::chrono::system_clock::now();
   return start;
}

void Elapsedtime(time_datatype start){ // Time elapsed func.
   auto end = std::chrono::system_clock::now();
   std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << "Execution time: " << elapsed_seconds.count() << "s  |\n";
}

struct Node{
   Node* next;
   std::string word;
   Node* prev;
};

struct Index{
   Node* head = nullptr;
   Node* tail = nullptr;
   int Numofnodes = 0;
};

class dictionary{ // dictionary class.
   private:
      Index Hashtable[DSIZE]; // Hashtable.
      Index Suggestedwords[20]; // Corrected words.

   public:
      dictionary(); // Default constructor.
      ~dictionary(); // Default destructor.

      void deleteDLL(); // Deletes Suggested-words nodes.

      void statistics(); // Prints out statistics about hashtable.

      bool isEmpty(int a); // Checks if hashtable at index is empty.
      bool isEmpty2(int a); // Checks if Sugg. word at index is empty.

      int multi_hash2(char* a); // Multiplication hash.
      int hash_division(char* a); // Division hash.

      void readEnglish(char* a); // Loads dict.
      void insertWord(char a[]); // Adds word to dict.

      bool findword(std::string str); // Finds word in dict.
      bool find(Node* n, std::string str); // Find word in DLL.
      std::string fetchword(Node* a, int b, int c); // Grabs corrected word.

      void count(Node* a, int b, int &c); // Statistics subroutine.
      void printnext(Node* a, int b, int c); // DLL printer.

      struct Node* setNode(const char str[]); // Sents DLL node.

      void addletter(bool a, Node* b, int c); // 1-edit SR
      void removechar(bool a, Node* b, int c); // 1-edit SR
      void swapletter(bool a, Node* b, int c); // 1-edit SR
      void replaceletter(bool a, Node* b, int c); // 1-edit SR
      std::string editdistance(std::string a, int b, int c); // Spell checking.

      void insertNode(const char* str, int index_num); // Adds node.
      void insertNode2(const char* str, int index_num); // Adds node.
};

dictionary::dictionary(){ // Default constructor.

}

dictionary::~dictionary(){ // Default destructor.
   deleteDLL();
}

int dictionary::multi_hash2(char* str){ // Mult. hash.
   size_t ASCII = 0;
   for(int i = 0; str[i] != '\0'; i++)
      ASCII += str[i];
   ASCII *= str[0];
   size_t w = 31;
   size_t s = 777777777;
   size_t hash_value = s * ASCII;
   hash_value = hash_value % ((size_t)1<<w) >> (w-13);
   return hash_value;
}

int dictionary::hash_division(char* str){ // Division hash.
   size_t ASCII = 0;
   for(int i = 0; str[i] != '\0'; i++)
      ASCII += str[i];
   ASCII *= str[0];
	return (ASCII % DSIZE);
}

void dictionary::insertWord(char str[]){ // Inserts node.
   int index_num = multi_hash2(str); // Gets index of word...
   insertNode(str, index_num); // ..to insert in Index.
}

void dictionary::readEnglish(char* file_name){ // Loads english.txt
   std::ifstream infile(file_name);          // into hashtable.
   if(infile.fail())
      printf("%s File Error\n", file_name);
   std::string bfr = "";
   auto start = Timerstart();
   while(infile >> bfr){
      char word[bfr.size() + 1];
      strcpy(word, bfr.c_str());
      insertWord(word);
   }
   Elapsedtime(start);
   infile.close();
}

struct Node* dictionary::setNode(const char str[]){ // Sets node.
   Node* newNode = new Node; // New node.
   newNode->word = str; // Sets string.
   newNode->prev = NULL; // Sets to nullptr.
   newNode->next = NULL;
   return newNode;
}

bool dictionary::isEmpty(int index_num){ // Checks if hash at index is empty.
    if(Hashtable[index_num].tail == nullptr)
        return true;
    else
        return false;
}

bool dictionary::isEmpty2(int index){ // Checks if Sugg. word at index is empty.
   if(Suggestedwords[index].head == nullptr)
      return true;
   else
      return false;
}

void dictionary::insertNode(const char* str, int index_num){
   Node* newNode = setNode(str); // Makes new node w/ data.
   if(isEmpty(index_num)){ // If DLL is empty, insert.
      newNode->prev = Hashtable[index_num].tail;
      Hashtable[index_num].head = newNode;
      Hashtable[index_num].tail = newNode;
      Hashtable[index_num].Numofnodes++;
   } else { // If DLL is not empty, insert.
      newNode->prev = Hashtable[index_num].tail;
      Hashtable[index_num].tail->next = newNode;
      Hashtable[index_num].tail = newNode;
      Hashtable[index_num].Numofnodes++;
    }
}

void dictionary::insertNode2(const char *str, int index_num){
   Node* newNode = setNode(str); // Makes new node w/ data.
   if(isEmpty2(index_num)){ // If DLL is empty, insert.
      newNode->prev = Suggestedwords[index_num].tail;
      Suggestedwords[index_num].head = newNode;
      Suggestedwords[index_num].tail = newNode;
      Suggestedwords[index_num].Numofnodes++;
   } else { // If DLL is not empty, insert.
      newNode->prev = Suggestedwords[index_num].tail;
      Suggestedwords[index_num].tail->next = newNode;
      Suggestedwords[index_num].tail = newNode;
      Suggestedwords[index_num].Numofnodes++;
    }
}

void dictionary::deleteDLL(){ // Deletes dict. & Sugg `table`.
   for(int index_num = 0; index_num < DSIZE; index_num++){
      if(!isEmpty(index_num)){
         Node* current = Hashtable[index_num].head;
         Node* A;
         while(current != NULL){
            A = current->next;
            delete current;
            current = A;
         }
      }
   }
   for(int i = 0; i < 20; i++){
      if(!isEmpty(i)){
         Node* current = Suggestedwords[i].head;
         Node* A;
         while(current != NULL){
            A = current->next;
            delete current;
            current = A;
         }
      }
   }
}

/* Recurisively calls itself to move forward in a DLL
   in order to print the contents.  */
void dictionary::printnext(Node* node, int num, int i){
   if(num == 11) // Formatting.
      printf("\n");
   if(node == Suggestedwords[i].head){ // Skips first node.
      num++;
      printf("->");
      printnext(node->next, num, i);
   } else if(node != NULL && num+1 == Suggestedwords[i].Numofnodes || num == 20){ // Ends at 20.
      std::cout << " [" << num << "]" << node->word << "<-\n";
   } else if(node){ // Regular node printout.
      if(node->word != Suggestedwords[i].head->word){
         std::cout << "[" << num << "]" << node->word << ", ";
         num++;
      }
      printnext(node->next, num, i);
   } else {
      return;
   }
}

/* Recursively calls itself to move forward in a DLL
   in order to find a certain word. */
bool dictionary::find(Node* node, std::string str){
   if(node != nullptr){
      if(node->word == str){
         return true;
      } else {
         return(find(node->next, str));
      }
   } else {
      return false;
   }
   return false;
}

/* Recursively calls itself to move forward in a DLL
   in order to count up the total words in the hashtable. */
void dictionary::count(Node* n, int index_num, int &total){
   if(n){
      total++;
      count(n->next, index_num, total);
   } else {
      return;
   }
}

void dictionary::statistics(){ // Prints statistics
   int nums[8192] = {0}; // Sets array to 0.
   char a; /* Declaring variables. */
   int min = 25, max = 0;
   int beg = 0, end = 0, usedbuckets = 0, total = 0, i = 0;
   /* Loops through hashtable (checking if head isn't NULL)
      and gets each bucket size, and # of used buckets. */
   for(int index_num = 0; index_num < DSIZE; index_num++){
      if(Hashtable[index_num].head){
         if(!Hashtable[index_num].head->word.empty())
            usedbuckets++;
         int beg = total;
         count(Hashtable[index_num].head, index_num, total);
         end = (total - beg);
         nums[index_num] = end;
      }
   }
   /* Finds min and max */
   for(i = 0; i < DSIZE; i++){
      if(nums[i] < min && nums[i] != 0)
         min = nums[i];
      if(nums[i] > max)
         max = nums[i];
   }
   /* Print outs for the statistics */
   printf("The least sized bucket is: %d.\n", min);
   printf("The most sized bucket is: %d.\n", max);
   printf("Used buckets: %d/8192, Total Words: %d.\n", usedbuckets, total);
   printf("Average # of words in a bucket: %d.\n", total/usedbuckets);
}

bool dictionary::findword(std::string str){ // Finds word in dictionary.
   char word[str.size() + 1];
   strcpy(word, str.c_str());
   int index_num = multi_hash2(word);
   if(find(Hashtable[index_num].head, str) == true){
      return true; // FOUND.
   } else {
      return false; // NOT FOUND.
   }
}

template <typename T>
void swap (T &A, T &B){ // Template swap.
   T C = A;
   A = B;
   B = C;
}

void dictionary::addletter(bool one, Node* node, int index_num){
   if(!node) // If the node is very bad, we skip this function.
      return;
   Node* header = Suggestedwords[index_num].head;
   int size = 0;
   std::string reference(node->word);
   const char* pass = reference.c_str();
   char* str = strdup(pass); // Makes copy word.
   for(int i = 0; str[i] != '\0'; i++)
      size++;
   size++;
   char newstr[size]; // New char[] w/ size + 1;
   for(int i = 0; i < size; i++)
      newstr[i+1] = str[i]; // Copies contents to new char[]

   for(int i = 0; i < size; i++){ // For each position.
      newstr[i] = ' '; // Fill position with space
      for(int k = 0; k < 26; k++){ // For each letter in alph.
         newstr[i] = alp[k]; // Sets our empty spot to char.
         std::string word(newstr); // Sets it to string.
         if((findword(word.c_str()) == true) && (find(header, word.c_str()) != true))
            insertNode2(word.c_str(), index_num); // Inserts it.
      }
      if(i != size-1)
         swap(newstr[i], newstr[i+1]); // Swaps positions.
      newstr[i+1] = ' ';
   }
   delete str; // These give me some funky valgrind error
}

void dictionary::replaceletter(bool one, Node* node, int index_num){
   if(!node) // If the node is very bad, we skip this function.
      return;
   Node* header = Suggestedwords[index_num].head;
   std::string reference(node->word);
   const char* pass = reference.c_str();
   char* str = strdup(pass); // Makes copy of string.
   int size = 0, j = 0;
   for(int i = 0; str[i] != '\0'; i++)
      size++; // Gets size of string.
   char copy[size + 1]; // Our `temp`
   for(int k = 0; k < size + 1; k++) // Assign to temp
      copy[k] = str[k];
   for(int i = 0; i < size; i++){
      for(int k = 0; k < 26; k++){
         str[i] = alp[k]; // Swaps char
         std::string word(str);
         if((findword(word.c_str()) == true) && (find(header, word.c_str()) != true))
            insertNode2(word.c_str(), index_num); // Inserts if a word.
         str[i] = copy[i]; // Copies back to get original word.
      }
   }
   delete str;
}

void dictionary::removechar(bool one, Node* node, int index_num){
   if(!node) // If the node is very bad, we skip this function.
      return;
   Node* header = Suggestedwords[index_num].head;
   std::string reference(node->word);
   const char* pass = reference.c_str();
   char* str = strdup(pass); // Creates a copy of the string.
   int size = 0, j = 0;
   for(int i = 0; str[i] != '\0'; i++) // Gets size of string.
      size++;
   char copy[size+1];
   char del[size];
   for(int i = 0; i < size; i++)
      copy[i] = str[i];
   for(int i = 0; i < size; i++){
      std::string word(str);
      std::string cut = word;
      cut.erase(cut.begin()+i); // Deletes only 1 char each time.
      if(findword(cut.c_str()) == true && (find(header, cut.c_str()) != true))
         insertNode2(cut.c_str(), index_num); // Inserts if a word.
   }
   delete str;
}

void dictionary::swapletter(bool one, Node* node, int index_num){
   if(!node) // If the node is very bad, we skip this function.
      return;
   std::string reference(node->word);
   Node* header = Suggestedwords[index_num].head;
   const char* pass = reference.c_str();
   char* str = strdup(pass); // Creates a copy of the string.
   int i;
   for(i = 0; str[i] != '\0'; i++)
      ; // Gets size of string.
   char copy[i+1]; // Our `temp`
   for(int k = 0; k < i+1; k++) // Assign to temp
      copy[k] = str[i];
   for(int j = 0; j < i-1; j++){
      if(str[j] != str[j+1]){
         swap(str[j], str[j+1]); // Swaps 2 characters.
         std::string altword(str);
         if(findword(altword) == true && (find(header, altword.c_str()) != true))
            insertNode2(altword.c_str(), index_num); // Inserts if string is a word.
         swap(str[j], str[j+1]); // Swaps back.
      }
   }
   delete str;
}

std::string dictionary::fetchword(Node* node, int count, int pick){
   if(node != nullptr){
      if(count == pick){
         return node->word;
      } else {
         count++;
         return(fetchword(node->next, count, pick));
      }
   } else {
      return "";
   }
   return "";
}


std::string dictionary::editdistance(std::string str, int distance, int index_num){
   bool one;
   if(distance == 1)
      one = true;
   else
      one = false;
   char choice;
   insertNode2(str.c_str(), index_num); // Inserts misspelled word at head.
   Node* node = Suggestedwords[index_num].head;
   if(one == true){ // One-edit path
      auto start = Timerstart();
      replaceletter(one, node, index_num);
      swapletter(one, node, index_num);
      removechar(one, node, index_num);
      addletter(one, node, index_num);
      Elapsedtime(start);
   } else { // Two-edit path.
      auto start = Timerstart();
      replaceletter(one, node, index_num);
      swapletter(one, node, index_num);
      removechar(one, node, index_num);
      addletter(one, node, index_num);
      int iterate = Suggestedwords[index_num].Numofnodes - 1;
      if(Suggestedwords[index_num].head){
         node = Suggestedwords[index_num].head->next;
         /* Loops through each valid one-edit word to run
            one-edit on again. */
         for(int i = 0; i < iterate; i++){
            replaceletter(one, node, index_num);
            swapletter(one, node, index_num);
            removechar(one, node, index_num);
            addletter(one, node, index_num);
            if(node->next)
               node = node->next;
            else
               break;
         }
      }
   Elapsedtime(start);
   }
   /* Printout out results format */
   if(one == true && Suggestedwords[index_num].Numofnodes > 1)
      printf("\n\t\t\t\t\tOne-Edit-Distance:\n");
   else if(one == false && Suggestedwords[index_num].Numofnodes > 1)
      printf("\n\t\t\t\t\tTwo-Edit-Distance:\n");
   else
      printf("\n\t\t\t\t\tNo available corrections for '%s'.\n", str.c_str());
   /* Prints out suggestions */
   if(Suggestedwords[index_num].Numofnodes > 1){
      printf("Total number of possible corrections: %d.\n", Suggestedwords[index_num].Numofnodes-1);
      printf("Instead of '%s', did you mean:\n", str.c_str());
      printnext(Suggestedwords[index_num].head, 0, index_num);

      printf("┌╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾┐\n");
      printf("│[1] - Add Word        │\n");
      printf("│[2] - Pick Correction │\n");
      printf("└╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾╼╾┘\n>");

      std::cin >> choice;
      while(choice != '1' && choice != '2'){
         printf("Invalid selection\n>");
         std::cin >> choice;
      }
      if(choice == '1'){
         const char* pass = str.c_str();
         char* addword = strdup(pass);
         insertWord(addword);
         printf("Word added to dictionary!\n");
         delete addword;
         return str;
      } else {
         int pick = 0;
         printf("Pick a word from above.\n>");
         std::cin >> pick;
         while(pick < 0 || pick > 20 || pick > Suggestedwords[index_num].Numofnodes){
            printf("Invalid selection\n>");
            std::cin >> pick;
         }
         Node* header = Suggestedwords[index_num].head;
         std::string WORD = fetchword(header, 0, pick);
         return WORD;
      }
   } else {
      char option;
      printf("\nWould you like to still add your word into the dictionary (y/n)?\n>");
      std::cin >> option;
      while(option != 'y' && option != 'Y' && option != 'n' && option != 'N'){
         printf("Invalid option, re-enter\n>");
         std::cin >> option;
      }
      if(option == 'y' || option == 'Y'){
         const char* pass = str.c_str();
         char* addword = strdup(pass);
         insertWord(addword);
         printf("Word added to dictionary!\n");
         delete addword;
         return str;
      }
   }
   std::string blank = ";";
   return blank;
}

#endif
