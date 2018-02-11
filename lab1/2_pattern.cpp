// Alex Cherekdjian
#include <iostream>
#include <iomanip>
using namespace std;

/* 
Prints the following sequence:
0123456789
 9876543210
  0123456789
   9876543210
    0123456789
     9876543210
      0123456789
       9876543210
        0123456789
         9876543210
*/

int main(){

string forward ("0123456789");
string backward ("9876543210");

cout << forward << endl; // initial line

	for(int i = 11; i < 20; i=i+2){ // printing out sequence above
		cout << setw(i);		
		cout << backward << endl;
		if(i != 19){
			cout << setw(i+1);		
			cout << forward << endl;
			}
	}

	return 0;
}
