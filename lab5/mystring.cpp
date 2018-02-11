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
#include <math.h>
#include <string.h>
#include "mystring.h"

using namespace std::cin;
using namespace coen79_lab5;

namespace coen79_lab5
{
    // CONSTRUCTOR, COPY CONSTRUCTOR, and DESTRUCTOR
    string::string(const char str[] = ""){
        int stringLength = strlen(str);
        assert(str[stringLength+1] == '\0');

        allocated = 0;
        reserve(stringLength);
        strncpy(*characters, str, sizeof(str));
        allocated = stringLength+1;
        current_length = stringLength;
    }

    string::string(char c){
        allocated = 0;
        reserve(1);
        strncpy(*characters, c, sizeof(c));
        allocated = 2;
        current_length = 1;
    }   

    string::string(const string& source){
        // string god(guew);
        allocated = 0;
        reserve(source.current_length);

        strncpy(*characters, *source.characters, sizeof(*source.characters));
        allocated = source.allocated;
        current_length = source.current_length;
    }

    string::~string(){
        delete[] characters;
    }

    // MODIFICATION MEMBER FUNCTIONS
    void string::operator +=(const string& addend){
        //like a.operator(b)
        reserve(current_length + addend.current_length);
        strncat(*characters, *addend.characters, sizeof(*addend.characters));
        current_length = current_length + addend.current_length;
        allocated = sizeof(*characters);
    }

    void string::operator +=(const char addend[]){
        int stringLength = strlen(addend);
        assert(addend[stringLength+1] == '\0');

        reserve(current_length + stringLength);
        strncat(*characters, addend, sizeof(addend));
        current_length = current_length + stringLength;
        allocated = sizeof(*characters);
    }

    void string::operator +=(char addend){
        reserve(current_length+1);
        strncat(*characters, addend, sizeof(addend));
        current_length++;
        allocated = sizeof(*characters);
    }

    void string::reserve(size_t n){
        if((n+1) > allocated){
            // copy all of old ish into new ish
            char * temp = new char[n+1]; // n is number of chars without null term
            strncpy(*temp, *characters, sizeof(*characters));
            delete [] characters;
            characters = temp;
        }
    }

    string& string::operator =(const string& source){
        string temp (*source.characters);
        temp.reserve(source.allocated-1);
        current_length = source.current_length;
        allocated = sizeof(*source.characters);
        return temp;
    }

    void string::insert(const string& source, unsigned int position){
        assert(position <= length());
        reserve(current_length + source.current_length);
        memmove(*characters[position+source.current_length], *characters[position], source.current_length);
        strncpy(*characters[position+source.current_length], *source.characters, sizeof(*source.characters));
        current_length += source.length;
        allocated = sizeof(*characters);
    }

    void string::dlt(unsigned int position, unsigned int num){
        assert(position + num <= length());
        memmove(*characters[position], *characters[position+num],num);
        current_length -= num;
    }

    void string::replace(char c, unsigned int position){
        assert(position < length());
        *characters[position] = c;
    }

    void string::replace(const string& source, unsigned int position){
        assert((position + source.length()) <= length());
        strncpy(*characters[position+source.current_length], *source.characters, sizeof(*source.characters)-1);
    }
    
    // CONSTANT MEMBER FUNCTIONS
    char string::operator [](size_t position) const{
        assert(position < length());
        return *characters[position];
    }

    int string::search(char c) const;{
        char* temp;
        temp = strchr(*characters,c);
        if(temp != NULL){
            return temp-characters+1;
        }
    return -1;
    }
    
    int string::search(const string& substring) const{
        int temp;
        temp = strstr(*characters,substring);
        if(temp != NULL){
            return temp-characters+1;
        }
    return -1;
    }
    
    unsigned int string::count(char c) const{
        unsigned int answer = 0;
        answer = strspn(*characters, c);
        return answer;
    }
    
    // FRIEND FUNCTIONS
    std::ostream& operator <<(std::ostream& outs, const string& source){
        int stringLength = strlen(*source.characters);
        for (int i = 0; i =< stringLength; ++i){
            outs << *source.characters[i] << endl;
        }
        return outs;
    }
    
    bool operator ==(const string& s1, const string& s2){
        // go through each character see if equal
        if(strncmp(*s1.characters,*s2.characters, strlen(s1)) == 0){
            return true;
        }else{
            return false;
        }
    }
    
    bool operator !=(const string& s1, const string& s2){
        // return not .operator==
        if(s1 == s2){
            return false;
        }else{
            return true;
        }
    }
    
    bool operator > (const string& s1, const string& s2){
        // return true if strncmp
        if((s1 < s2) || (s1 == s2)){
            return false;
        }else{
            return true;
        }
    }
    
    bool operator < (const string& s1, const string& s2){
    // s1 < s2
    // then s1 happens before s2 alphabetically
    // if s1 = ab and s2 = cd
    // a is before c alphabetically so that is true
        if(strncmp(*s1.characters,*s2.characters, strlen(s1)) < 0){
            return true;
        }else{
            return false;
        }

    }
    
    bool operator >=(const string& s1, const string& s2){
        // call above functions if both true then gucci
        if((s1 > s2) || (s1 == s2)){
            return true;
        }else{
            return false;
        }
    }
    
    bool operator <=(const string& s1, const string& s2){
        // call above functions if both true then gucci
        if(s1 >= s2){
            return false;
        }else{
            return true;
        }
    }
    
    // NON-MEMBER FUNCTIONS for the string class
    string operator +(const string& s1, const string& s2){
        // add s2 to s1 return temp
        string temp;
        temp.reserve(s1.current_length + s2.current_length);
        strncpy(*temp.characters, *s1.characters, sizeof(*s1.characters));
        strncat(*temp.characters, *s2.characters, sizeof(*s2.characters));
        temp.current_length = s1.current_length + s2.current_length;
        temp.addend = sizeof(*temp.characters);
        return temp;
    }
    
    string operator +(const string& s1, const char addend[]){
        string temp;
        int stringLength = strlen(addend);
        temp.reserve(s1.current_length + stringLength);
        strncpy(*temp.characters, *s1.characters, sizeof(*s1.characters));
        strncat(*temp.characters, addend, sizeof(addend));
        temp.current_length = s1.current_length + stringLength;
        temp.addend = sizeof(*temp.characters);
        return temp;
    }
    
    std::istream& operator >> (std::istream& ins, string& target){
        std::cout << "\nInput a string: " << endl; // prompt for argument
        ins >> std::skipws >> target >> endl; // ensuring white space skip flag is enabled
        std::cout << "Read successful\n" << endl;
        return ins;
    }
};
