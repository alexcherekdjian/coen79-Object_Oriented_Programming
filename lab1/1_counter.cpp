// Alex Cherekdjian
#include <iostream>
#include <string>
using namespace std;

int main(){

int alpha = 0; // initializing counters for alpha and nonalpha chars
int nonalpha = 0;

string words; // creating string to store input

cout << "Please type something: \n"; // asking user to type input

getline (cin, words); // getting line and storing into words

int length = words.length(); // obtaining length of words

for(int i = 0; i < length; i++){  
	if (words.at(i) == ' ') // if the character read was a space then skip
		continue;
	if(isalnum(words.at(i)) == 0) // if returns 0 means nonalpha so increment counter accordingly
		nonalpha++;
	else
		alpha++;
	}

cout << "Number of alpha:" << alpha  << endl; // printing results
cout << "Number of nonalpha:" << nonalpha << endl; 

return 0;
}
