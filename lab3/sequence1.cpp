// Alex Cherekdjian
// Coen 79 lab3

/* 
Invariants:
The size of the sequence class must always be less than the capacity. With advancing, printing current items
remove current item, and remove front isitem must return true. Furthermore, the order of the items added to 
the class must be sustained.
*/

#include <cassert>
#include <iostream>
#include <math.h>
#include "sequence1.h"

using namespace std;
using namespace coen79_lab3;

namespace coen79_lab3
{
	sequence::sequence(){
		used = 0; // initializing used variable
		current_index = 0; // initializing current_index variable
	}

	void sequence::start(){
		current_index = 0; // assigning current_index to start of array
	}

	void sequence::end(){
		current_index = (used-1); // assigning current_index to end of used portion
	}

	void sequence::last(){
		current_index = (sequence::CAPACITY-1); // assigning current_index to end of array
	}

	sequence::value_type sequence::current() const{
		assert(is_item() == true); // asserting an item is there
		return data[current_index]; // returning that data
	}

	void sequence::advance(){
		assert(is_item() == true); // asserting an item is there
		if(current_index != (sequence::CAPACITY-1)){
			current_index++; // as long as the index is not at the end increase current_index
		}
	}

	void sequence::retreat(){
		if(current_index != 0){
			current_index--; // as long as not at start, decrease current_index
		}
	}

	void sequence::insert(const value_type& entry){
		assert(size() < sequence::CAPACITY); // assert size of used is < capacity
		if(is_item() == true){
			for(int i = used; i > current_index; i--){
				data[i] = data[i-1]; // move all items down one if items present, make space for new item
			}
			data[current_index] = entry; // insert new item before
		}else{
			data[current_index] = entry; // insert new item in current index since first element 
		}
		used++; // increment used parameter since added element
	}

	void sequence::attach(const value_type& entry){
		assert(used < sequence::CAPACITY);
		if(is_item() == true){
			for(int i = used; i > (current_index+1); i--){
				data[i] = data[i-1]; // move all items down one if items present, make space for new item
			}
			data[current_index+1] = entry; // insert new item after index
		}else{
			data[current_index] = entry; // insert new item in current index since first element
		}
		used++; // increment used parameter since added element
		current_index++; // increment current index
	}

	void sequence::remove_current(){
		assert(is_item() == true); // making sure item is there to remove
		for(int i = current_index; i < (used-1); i++){
			data[i] = data[i+1]; // move all items up one, overwriting data to remove
		}
		used--; // decrement used
	}

	void sequence::insert_front(const value_type& entry){
		assert(size() < sequence::CAPACITY); // assert used is less than capacity
		for(int i = used; i > 0; i--){
			data[i] = data[i-1]; // move all items down one, make space for new item
		}
		data[0] = entry; // insert at front
		used++; // increase used
		current_index = 0; // assign current_index to first value
	}

	void sequence::attach_back(const value_type& entry){
		assert(size() < sequence::CAPACITY); // ensure used is less than capacity
		data[used] = entry; // assigning entry to end index
		current_index = used; // assigning current index to entry value
		used++; // increment used
	}

	void sequence::remove_front(){
		assert(is_item() == true); // ensure item is present
		for(int i = 0; i < (used-1); i++){
			data[i] = data[i+1]; // move all items up one,overwriting data[0] slot
		}
		
		used--; // decrement used since removed
		current_index = 0; // initialize current_index
	}

	sequence::size_type sequence::size() const{
		return used; // return # of elts used array
	}

	bool sequence::is_item( ) const{
		if(current_index < used){
			return true; // if current_index is a value, will be within 0-used
		}
		return false;
	}

	sequence::value_type sequence::operator[](int index) const{
		assert(index < used); // ensure value will be present
		return data[index]; // return value at index
	}

	double sequence::mean() const{
		double sum = 0.0; // initializing 
		double ans;

		for(int i = 0; i < used; i++){
			sum += data[i]; // add up all values
		}

		ans = sum/(double)used; // calculate mean by dividing # of total values in sequence
		
		return ans;
	}

	double sequence::standardDeviation() const{
		double mean1 = mean(); // calc mean
		double squaredSum = 0.0; // initialzing variables
		double ans;
		
		for(int i = 0; i < used; i++){
			
			squaredSum += (data[i]-mean1)*(data[i]-mean1); // calculating squaredSum
		}
		
		ans = squaredSum / (double)used; // taking mean of squaredSum
		ans = pow(ans, 0.5); // square rooting answer
		return ans;
	}

	sequence operator +(const sequence& lhs, const sequence& rhs){
		
		assert((lhs.used + rhs.used) < sequence::CAPACITY); // ensure all elements will fit into capacity

		sequence temp; // create temp variable
		for(int i = 0; i < lhs.used; i++){
			temp.data[i] = lhs.data[i]; // add all values from lhs first
			temp.used++; // increment used variable for every successful transfer
		}
		for(int j = 0; j < rhs.used; j++){
			temp.data[(lhs.used) + j] = rhs.data[j]; // store all values of rhs at end of temp
			temp.used++; // increment used variable for every successful transfer
		}
		
		return temp;
	}

	sequence operator +=(const sequence& lhs, const sequence& rhs){
		sequence temp;
		int i;
		int j;
		// finding smallest size
		
		if(lhs.used == rhs.used){ // same # of elts thus no problem in adding
			for(i = 0; i < rhs.used; i++){
				temp.data[i] = lhs.data[i] + rhs.data[i]; // add lhs to rhs store in new variable
				temp.used++; // increase temp used variable
			}
			return temp;
		}

		// otherwise one is larger than other, so implement safeguard for adding empty index to an elt
		if(lhs.used < rhs.used){
			for(i = 0; i < lhs.used; i++){
				temp.data[i] = lhs.data[i] + rhs.data[i]; // add lhs to rhs store in new variable
				temp.used++; // increase temp used variable
			}
			// end of this loop would have added all values from least used, thus all thats left is to copy rest of values from larger array
			for(j = lhs.used; j < rhs.used; j++){
				temp.data[j] = rhs.data[j]; // add the rest of the elements not added
				temp.used++; // increase temp used variable
			}
		}else{
			for(i = 0; i < rhs.used; i++){
				temp.data[i] = lhs.data[i] + rhs.data[i]; // add lhs to rhs store in new variable
				temp.used++; // increase temp used variable
			}
			// end of this loop would have added all values from least used, thus all thats left is to copy rest of values from larger array
			for(j = rhs.used; j < lhs.used; j++){
				temp.data[j] = lhs.data[j]; // add the rest of the elements not added
				temp.used++; // increase temp used variable
			}
		}
		return temp;
	}

	sequence::value_type summation(const sequence &s){
		sequence::value_type sum = 0.0; // initializing sum value

		for(int i = 0; i < s.used; i++){
			sum += s[i]; // adding up all values
		}
		return sum;
	}

};
