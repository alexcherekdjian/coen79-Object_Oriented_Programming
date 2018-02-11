// Alex Cherekdjian
// COEN 79 Lab 2
// Friday 2:15 - 5:00

#include <cassert>
#include <iostream>
#include "random.h"

namespace coen79_lab2 {

	rand_gen::rand_gen(int seed, int multiplier, int increment, int modulus){
		
		// assigning new values of integers to specified containers using this command
		this->seed = seed; 
		this->multiplier = multiplier;
		this->increment = increment;
		this->modulus = modulus;
	}
	
	void rand_gen::set_seed(int newSeed){
		seed = newSeed; // assigning the new seed to be the integer passed to the function
	}

	int rand_gen::next(){
		int answer; // declaring temp variable
		answer = (multiplier * seed + increment) % modulus; // calculating the next random number
		seed = answer; // assigning the answer as the new seed
		return answer; // returning new random number generated
	}

	void rand_gen::print_info(){
		//  printing out all private member variables to console 
		cout << "Seed: " << seed << endl;
		cout << "Multiplier: " << multiplier << endl;
		cout << "Increment: " << increment << endl;
		cout << "Modulus: " << modulus << endl;
	}
}