// Alex Cherekdjian
// COEN 79 Lab 2
// Friday 2:15 - 5:00

#include <cassert>
#include <iostream>
#include "statistician.h"

using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2
{
	// declaring constructor that initializes all private values to 0
	statistician::statistician(){
		length1 = 0;
		sum1 = 0;
		mean1 = 0;
		smallest = 0;
		largest = 0;
	}

	void statistician::next(double r){
		length1++; // incrementing length by 1
		sum1 += r; // adding new value to sum
		
		if (length1 == 1){ // if r is the only value, then assign it to smallest and largest
			smallest = r;
			largest = r;
		}else if(smallest > r){ // if not compare with current smallest and replace if necessary
			smallest = r;
		}

		if (largest < r){ // compare with current largest and replace if necessary
			largest = r;
		}

		mean1 = (sum1 / length1); // calculate new mean and store in mean1 variable
	
	}

	int statistician::length(){
		return length1; // returning length of the object
	}

	double statistician::sum(){
		return sum1; // returning sum of the object
	}

	double statistician::mean(){
		assert(length1 > 0); // ensuring the numbers have been inputed to object
		return mean1; // returning mean of the object
	}

	double statistician::minimum(){
		assert(length1 > 0); // ensuring the numbers have been inputed to object
		return smallest; // returning smallest of the object
	}

	double statistician::maximum(){
		assert(length1 > 0); // ensuring the numbers have been inputed to object
		return largest; // returning largest of the object
	}

	// function resets all private member values to 0
	void statistician::reset(){
		length1 = 0;
		sum1 = 0;
		mean1 = 0;
		smallest = 0;
		largest = 0;
	}

	statistician operator +(const statistician& s1, const statistician& s2){
		statistician temp; // declaring temp object
		temp.length1 = s1.length1 + s2.length1; // combining lengths of both original object
		temp.sum1 = s1.sum1 + s2.sum1; // combining sum of both original object
	
		// calculating smallest value for new object
		if(s1.smallest < s2.smallest){
			temp.smallest = s1.smallest;
		}else{
			temp.smallest = s2.smallest;
		}
		
		// calculating largest value for new object
		if(s1.largest > s2.largest){
			temp.largest = s1.largest;
		}else{
			temp.largest = s2.largest;
		}
	
		temp.mean1 = (temp.sum1 / temp.length1); // calculating new mean for object
	
		return temp; // returning new combined object
	}

	statistician operator *(double scale, const statistician& s){
		statistician temp; // declaring temp object 
		temp.length1 = s.length1; // assigning new length to object
		temp.largest = s.smallest * scale; // scaling the smallest value
		temp.smallest = s.largest * scale; // scaling the largest value
		temp.sum1 = s.sum1 * scale; // scaling the sum
		temp.mean1 = (temp.sum1/temp.length1); // calculating the new mean
		return temp; // returning the new object
	}

	bool operator ==(const statistician& s1, const statistician& s2){
		if(s1.length1 == 0 && s2.length1 == 0) // if lengths == the return true
			return true;
		// if not then the everything of each private value must be equal to return true
		if(s1.length1 == s2.length1)
			if(s1.mean1 == s2.mean1)
				if(s1.smallest == s2.smallest)
					if(s1.largest == s2.largest)
						if(s1.sum1 == s2.sum1)
							return true;
		return false; 
	}	
};
