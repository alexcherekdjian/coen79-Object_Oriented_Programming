// Alex Cherekdjian
// Coen 79 lab5

/* 
Invariants: The characters pointer should point to characters that make a string.
The currentlength is always updated to the string length where the allocated term 
is always updated to the size of the array that is currently allocated in that 
object. 
*/

#include <cassert>
#include <iostream>
#include <stdio.h>
#include <assert.h>
//#include <algorithm>
#include <math.h>
#include <cstring>
#include "mystring.h"

using std::cin;
using std::cout;
using std::endl;
using std::skipws;
using namespace coen79_lab5;

namespace coen79_lab5
{
    // CONSTRUCTOR, COPY CONSTRUCTOR, and DESTRUCTOR
    string::string(const char str[]){
        int stringLength = strlen(str); // init string length
        assert(str[stringLength] == '\0'); // ensuring last character is null

        allocated = 0; // init allocated
        current_length = 0; // init current length
        characters =  NULL; // init characters 
        reserve(stringLength); // reserve space
        strncpy(characters, str, stringLength+1); // copy contents
        allocated = stringLength+1; // reinit allocated
        current_length = stringLength; // reinit stringlength
        
    }

    string::string(char c){
        allocated = 0; // init allocated
        current_length = 0; // init current length
        characters =  NULL; // init characters is null
        reserve(1); // reserve one space

        characters[0] = c; // init character array
        characters[1] = '\0';
        allocated = 2; // reinit allocated
        current_length = 1; // reinit currentlength
    }   

    string::string(const string& source){
        allocated = 0; // init allocated
        current_length = 0; // init current length
        characters =  NULL; // init characters is null
        reserve(source.current_length); // reserve one space

        strncpy(characters, source.characters, source.current_length+1); // copy contents
        allocated = source.allocated; // reinit allocated
        current_length = source.current_length; // reinit currentlength
    }

    string::~string(){
        delete[] characters; // delete heap memory on characters
    }

    // MODIFICATION MEMBER FUNCTIONS
    void string::operator +=(const string& addend){
        reserve(current_length + addend.current_length); // reserve array length of both
        strncat(characters, addend.characters, addend.current_length+1); // append to current array
        current_length = current_length + addend.current_length; // update currentlength
        allocated = sizeof(*characters); // update allocated 
    }

    void string::operator +=(const char addend[]){
        int stringLength = strlen(addend); // get stringlength
        assert(addend[stringLength] == '\0'); // ensure null terminated

        reserve(current_length + stringLength); // reserve space
        strncat(characters, addend, stringLength+1); // add to array
        current_length = current_length + stringLength; // update current length
        allocated = sizeof(*characters); // update allocated
    }

    void string::operator +=(char addend){
        reserve(current_length+1); // reserve space
        strncat(characters, &addend, 1); // add to array
        current_length++; // update current length
        allocated = sizeof(*characters); // update allocated
    }

    void string::reserve(size_t n){
        if((n+1) > allocated){ // if asked for larger than allocated, need more space
            char *temp = new char[n+1]; // n is number of chars without null term

            if(characters != NULL){
                strncpy(temp, characters, current_length+1); // copy data in new array
                delete [] characters; // delete old array
            }

            characters = temp; // assign new array to old array
        }
    }

    string& string::operator =(const string& source){
        reserve(source.allocated-1); // reserve space
        current_length = source.length(); // update current length
        allocated = sizeof(*source.characters); // update allocated
        strncpy(characters, source.characters, source.current_length+1); // copy from source to characters
        return *this; // return value called
    }

    void string::insert(const string& source, unsigned int position){
        assert(position <= length()); // ensure position less than length
        reserve(current_length + source.current_length); // reserve space 
        memmove(characters+(position+source.current_length+1), characters+position, source.current_length+1); // move memory in characters to make space
        strncpy(characters+(position), source.characters, source.current_length); // insert new characters
        current_length += source.length(); // increment length
        allocated = sizeof(*characters); // update allocated
    }

    void string::dlt(unsigned int position, unsigned int num){
        assert(position + num <= length()); // ensure position + num is less than length
        memmove(characters, characters+num,length() - num); // move memory in orginal array to delete
        current_length -= num; // current length decrement by deleted
    }

    void string::replace(char c, unsigned int position){
        assert(position < length()); // ensure position < length
        characters[position] = c; // assign position to character
    }

    void string::replace(const string& source, unsigned int position){
        assert((position + source.length()) <= length()); // ensure position + source  <= length
        strncpy(characters+position, source.characters, current_length-position); // assign string to character position
    }
    
    // CONSTANT MEMBER FUNCTIONS
    char string::operator [](size_t position) const{
        assert(position < length()); // ensure position less than length
        return characters[position]; // return character at that position
    }

    int string::search(char c) const{
        char* temp; // creating temp pointer
        temp = strchr(characters,c); // find first instance
        if(temp != NULL){
            return temp-characters+1; // if character found, return value
        }
        return -1; // found nothing
    }
    
    int string::search(const string& substring) const{
        char* temp; // creating temp pointer
        temp = strstr(characters, substring.characters); // find first instance of substring
        if(temp != NULL){
            return temp-characters+1; // if character found, return value
        }
        return -1; // found nothing
    }
    
    unsigned int string::count(char c) const{
        unsigned int answer = 0; // init answer
        for(int i = 0; i <= current_length; ++i){
            if(characters[i] == c){
                answer++; // if character found then increment
            }
        }
        return answer; // return answer
    }
    
    // FRIEND FUNCTIONS
    std::ostream& operator <<(std::ostream& outs, const string& source){
        int stringLength = source.length(); // init stringlength 
        
        for (int i = 0; i <= stringLength; ++i){
            outs << source.characters[i]; // output the string
        }
        return outs;
    }
    
    bool operator ==(const string& s1, const string& s2){
        if(strncmp(s1.characters,s2.characters, strlen(s1.characters)) == 0){
            return true; // if both strings are equal than true
        }else{
            return false;
        }
    }
    
    bool operator !=(const string& s1, const string& s2){
        if(s1 == s2){
            return false; // returning not of operator== 
        }else{
            return true;
        }
    }
    
    bool operator > (const string& s1, const string& s2){
        if((s1 < s2) || (s1 == s2)){
            return false; // not of < and == operator
        }else{
            return true;
        }
    }
    
    bool operator < (const string& s1, const string& s2){
        if(strncmp(s1.characters,s2.characters, strlen(s1.characters)) < 0){
            return true; // if s1 happens alphabetically before s2 then true
        }else{
            return false;
        }

    }
    
    bool operator >=(const string& s1, const string& s2){
        if((s1 > s2) || (s1 == s2)){
            return true; // returning if both > and == return true
        }else{
            return false;
        }
    }
    
    bool operator <=(const string& s1, const string& s2){
        if(s1 > s2){
            return false; // returning if > is false
        }else{
            return true;
        }
    }
    
    // NON-MEMBER FUNCTIONS for the string class
    string operator +(const string& s1, const string& s2){
        string temp(s1); // init temp with s1
        temp += s2; // adding s2 to temp
        return temp; // returning new string
    }
    
    string operator +(const string& s1, const char addend[]){
        string temp(s1); // init temp with s1 
        temp += addend; // appending addend to temp
        return temp; // return temp
    }
    
    std::istream& operator >> (std::istream& ins, string& target){
        std::cout << "\nInput a string: "; // prompt for argument
        char c; // creating temp char
        while(isspace(ins.peek()) != 0){
            ins.ignore(); // if the space in front is white space, do nothing
        }

        while(ins.eof() == false && isspace(ins.peek()) == 0){
            ins.get(c); // reading in words until another white space and eof reached
            target += c;
        }
    
        std::cout << "Read successful\n" << endl; // let user know success
        return ins;
    }
};
