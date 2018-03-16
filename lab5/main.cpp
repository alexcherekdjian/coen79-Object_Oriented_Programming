//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//

#include <iostream>
#include "mystring.h"

using namespace std;
using namespace coen79_lab5;


int main(int argc, char const *argv[]) {

    char input = 'd';
    coen79_lab5::string s1(input);
    cout << "s1 = " << s1 << endl;

    // char inputString [] = {'A','L','E','X'};
    coen79_lab5::string s2("Alex");
    cout << "s2 = " << s2 << endl;

    coen79_lab5::string s3(s2);
    cout << "s3 = " << s3 << endl;


    // operator char string addend
    s2.operator+=(s3);
    cout << "s21 = " << s2 << endl;

    // operator char addend addend
    char input2[] = "furrr";
    s2.operator+=(input2);
    cout << "s22 = " << s2 << endl;  

    // operator char addend
    s2.operator+=(s1);
    cout << "s23 = " << s2 << endl;
    cout << "s23length = " << s2.length() << endl;


    // operator =
    s2.operator=(s1);
    cout << "s1= = " << s1 << endl;
    cout << "s2= = " << s2 << endl;
    cout << "s2length = " << s2.length() << endl;


    coen79_lab5::string s4("treat");


    // insert
    s4.insert(s3,2);
    cout << "AFTER " << endl;
    cout << "s3insert = " << s3 << endl;
    cout << "s4insert = " << s4 << endl;
    cout << "s4length = " << s4.length() << endl;
    cout << "s3length = " << s3.length() << endl;


    // dlt
    s4.dlt(0,2);
    cout << "s4dlt = " << s4 << endl;

    cout << "s4length = " << s4.length() << endl;


    // replace char c positoin
    s4.replace('z', 5);
    cout << "s4replace = " << s4 << endl;

    cout << "s4length = " << s4.length() << endl;

    // replace string position
    coen79_lab5::string s5("gerb");
    s4.replace(s5,2);
    cout << "s4replace = " << s4 << endl;

    // operator []
    cout << " operator[] = "<<s4.operator[](3) << endl;

    // search
    char garb = 'e';
    cout << " search = "<<s4.search(garb)<< endl;

    // search 
    coen79_lab5::string s6("er");
    cout << " search = "<<s4.search(s6)<< endl;

    // count
    cout <<" count = "<< s4.count('e') << endl;

    if(s4 != s5)
        cout << "!= works" << endl;

    coen79_lab5::string s7("a");
    coen79_lab5::string s8("b");


    if(s7 < s8)
        cout << "< works" << endl;

    if(s8 > s7)
        cout << "> works" << endl;
   
    coen79_lab5::string s9("a");
    coen79_lab5::string s10("a");

    // works
    if(s9 == s10)
        cout << "== works" << endl;


    if(s7 <= s8)
        cout << "<= works1" << endl;
    if(s9 <= s10) // works
        cout << "<= works2" << endl;

    //
    if(s8 >= s7)
        cout << ">= works1" << endl;
    if(s9 >= s10)
        cout << ">= works2" << endl;



    cout << "s9 = " << s9 << endl;
    cout << "s8 = " << s8 << endl;

    cout << "operator+ " << s9+s8 << endl;
    
    cout << "s9 = " << s9 << endl;
    cout << "word = " << "real" << endl;

    cout << "operator+ " << s9+"real" << endl;
  

    coen79_lab5::string stringS("a");
    cin >> stringS;
    cout << "LAST: "<< stringS << endl;
      return 0;
}
