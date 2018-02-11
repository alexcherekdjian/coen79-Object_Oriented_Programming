// Alex Cherekdjian
// Coen 79 lab4

/* 
Invariants: Items must not exceed capacity in either the data or keys array. Used variable
should not exceed max capacity. 
*/

#include <cassert>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "keyed_bag.h"

using namespace std;
using namespace coen79_lab4;

namespace coen79_lab4
{
	keyed_bag::keyed_bag(){
		used = 0; // init used to 0
	}

    void keyed_bag::erase(){
    	
    	for (int i = 0; i < used; ++i){
    		data[i] = '0'; // init all data values to 0
    	}

    	for (int i = 0; i < used; ++i){
    		keys[i] = '\0'; // init all keys to null
    	}

    	used = 0; // init used to 0
    }

    bool keyed_bag::erase(const key_type& key){
    	if (has_key(key) == false){
    		return false; // cannot erase anything return false
    	}else{
    		int index;
    		for (int i = 0; i < used; ++i){
    			if(key == keys[i]){ 
    				index = i; // find elt if equal, stop thats index needed
    				break;
    			}
    		}
  		// overwrite both data and keys
    		for (int j = index; j < used; ++j){
    			data[j] = data[j+1];
    		}
    		for (int j = index; j < used; ++j){
    			keys[j] = keys[j+1];
    		}
    		used--; // erased value
    	return true; // return true if success
    	}
    }

    void keyed_bag::insert(const value_type& entry, const key_type& key){
    	assert(size() < keyed_bag::CAPACITY); // ensure size will fit in max capacity
    	assert(has_key(key) == false); // ensure the key is not already used
    	data[used] = entry; // assign entry to data
    	keys[used] = key; // assign key to keys
    	used++; // increment used
    }

    void keyed_bag::operator +=(const keyed_bag& addend){
    	assert(size() + addend.size() <= keyed_bag::CAPACITY); // ensure will fit in max capacity
    	assert(hasDuplicateKey(addend) == false); // ensure no duplicate key 
    	int j = 0;
    	for (int i = used; i < (used + addend.used); ++i){
    		data[i] = addend.data[j]; // add addend data to data
    		keys[i] = addend.keys[j]; // add corresponding addend.key to keys
    		j++; // increment to next value
    	}
    	used += addend.used; // increment used variable

    }

    bool keyed_bag::has_key(const key_type& key) const{
    	for (int i = 0; i < used; ++i){
    		if(key == keys[i]) // if equal, stop that value is here
    		return true;
    	}
    	return false; // else nothing found so return nothing
    }

   keyed_bag::value_type keyed_bag::get(const key_type& key) const{
    	assert(has_key(key) == true); // ensures key is in the bag
    	int index;
    	for (int i = 0; i < used; ++i){
    		if(key == keys[i]){ 
    			index = i; // if equal, stop thats index needed
    			break;
    		}
    	}
    	return data[index]; // return data of that index

    }

    keyed_bag::size_type keyed_bag::size( ) const{
    	return used; // return size of bag
    }

   keyed_bag::size_type keyed_bag::count(const value_type& target) const{
    	size_type popularity = 0; // init # of popularity 
    	for(int i = 0; i < used; i++){
    		if(data[i] == target){
    			popularity++; // if in bag, increment count
    		}
    	}
    	return popularity; // return popularity of target
    }

    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const{
    	if((used == 0) || (otherBag.used == 0)){
    		return false; // if nothing in bags return false
    	}

    	key_type temp; // init temp var
    	int i;
    	int j;

    	for(i = 0; i < used; i++){
    		temp = keys[i]; // get first value
    		for(j = 0; j < otherBag.used; j++){
   				if(temp == otherBag.keys[j]){
   					return true; // check value with all other values in other bag, if in bag, true
   				}
   			}
    	}
    	return false; // if exits loop, not in bag
    }

    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2){
		assert((b1.size() + b2.size()) <= keyed_bag::CAPACITY); // ensure added size < capacity
		assert((b1.hasDuplicateKey(b2)) == false); // ensure no duplicate key
		keyed_bag temp = keyed_bag(); // create temp bag
		
		temp += b1; // add b1
		temp += b2; // add b2
		return temp; // return new bag
	}
};
