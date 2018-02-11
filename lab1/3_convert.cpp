// Alex Cherekdjian
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

int main(int argc , char *argv[]){

if (argc != 2) // if nothing inputed just quit
	return -1;

string word; // initializing word string
ifstream file; // initializing file pointer
file.open(argv[1]); // opening argument file

while(file >> word){ // run as long as can store a word 

	for (int i = 0; i < word.length(); i++){
		if(isalnum(word.at(i)) == 0){ // erasing all nonalpha characters
			word.erase(i,1);
			i--; // double check space after erasing
		}
	}

	if (word.length() < 10) // if less than 10 skip
		continue;

	for (int i = 0; i < word.length(); i++){ 
                word.at(i) = toupper(word.at(i)); // changing all chars to uppercase
        }	

	cout << word << endl; // printing result
}
file.close(); // closing file

return 0;
}
