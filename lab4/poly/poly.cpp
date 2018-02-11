// Alex Cherekdjian
// Coen 79 lab4

/* 
Invariants: The degree asociated with the coefficient in the coeff array is the index.
The maximum degree should never be exceeded. 
*/

#include <cassert>
#include <iostream>
#include <climits>
#include <assert.h>
#include <math.h>
#include "poly.h"

using namespace std;
using namespace coen79_lab4;

namespace coen79_lab4
{
    polynomial::polynomial(double c, unsigned int exponent){
    	assert(exponent <= polynomial::MAXIMUM_DEGREE); // ensure exponent in range
    	currentDegree = 0; // assign current degree to 0
    	for (int i = 0; i <= polynomial::MAXIMUM_DEGREE; ++i){
    		coeff[i] = 0; // set all coeff's to 0
    	}
    	coeff[exponent] = c; // if exponent given, then assign
    }

	void polynomial::update_current_degree(){
		for (int i = polynomial::MAXIMUM_DEGREE; i >= 0; --i){
			if(coeff[i] != 0){
				currentDegree = i; // assign current degree to largest exponent
				break;
			}
		}
	}

    void polynomial::assign_coef(double coefficient, unsigned int exponent){
	  	assert(exponent <= polynomial::MAXIMUM_DEGREE); // ensure exponent in range
	  	coeff[exponent] = coefficient; // assign the coeff to exponent
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent){
    	assert(exponent <= polynomial::MAXIMUM_DEGREE); // ensure exponent in range
    	coeff[exponent] += amount; // add amount to exponent
    }

    void polynomial::clear(){
        for (int i = 0; i < polynomial::MAXIMUM_DEGREE+1; ++i){
    		coeff[i] = 0; // assign all coeff to 0
    	}
    }

    polynomial polynomial::antiderivative() const{
    	assert(degree() < polynomial::MAXIMUM_DEGREE); // ensure largest exponent < max degree
 			polynomial temp = polynomial(0.0,0); // create temp variable
    	for (int i = MAXIMUM_DEGREE; i > 0; --i){
    		temp.coeff[i] = coeff[i-1]; // assign previous coeff to current
    		temp.coeff[i] /= i; // divide coeff by exponent
    	}
    	return temp; 
    }

    double polynomial::coefficient(unsigned int exponent) const{
    	if(exponent > polynomial::MAXIMUM_DEGREE)
    		return 0.0; // if larger exponent given, return 0
    	return coeff[exponent]; // else return coeff of exponent given
    }

    double polynomial::definite_integral(double x0, double x1) const{
    	polynomial temp = antiderivative(); // create temp and assign antiderivative
    	double ans = temp.eval(x1) - temp.eval(x0); // eval definite integral (top - bottom)
    	return ans;
    }

    unsigned int polynomial::degree() const{
        for (int i = polynomial::MAXIMUM_DEGREE; i >= 0; --i){
			if(coeff[i] != 0){
				return i; // return highest exponent 
			}
		}
		return 0;
    }

    polynomial polynomial::derivative() const{
 		polynomial temp = polynomial(0.0,0); // initialize temp variable
    	for (int i = 0; i <= polynomial::MAXIMUM_DEGREE; ++i){
    		temp.coeff[i] = coeff[i+1]; // assign next index to previous
    		temp.coeff[i] *= (i+1); // mult by next index
    	}
    	return temp;
    }

	double polynomial::eval(double x) const{
    	double ans = 0;
    	for (int i = 0; i <= polynomial::MAXIMUM_DEGREE; ++i){
    		ans += coeff[i]*pow(x,i); // calculate each exponent and add to answer
    	}
    	return ans;
    }

    bool polynomial::is_zero() const{
        if(degree() == 0)
       		return true; // if degree is 0 return true
       	return false;
    }

    unsigned int polynomial::next_term(unsigned int e) const{
    	for (int i = e+1; i <= MAXIMUM_DEGREE; ++i){
    		if((coeff[i] > coeff[e]) && (coeff[i] != 0))
    			return i; // return next exponent with a coeff > than e
    	}
        return 0;
    }

    unsigned int polynomial::previous_term(unsigned int e) const{
    	for (int i = e-1; i >= 0; --i){
    		if(coeff[i] < coeff[e] && coeff[i] != 0)
    			return i; // return next exponent with a coeff < than e
    	}
        return UINT_MAX;			
    }

    double polynomial::operator() (double x) const{
    	return eval(x); // call eval function
    }

    polynomial operator +(const polynomial& p1, const polynomial& p2){
     	polynomial temp = polynomial(0.0,0);
        for (int i = 0; i <= polynomial::MAXIMUM_DEGREE; ++i){
    		temp.coeff[i] = p1.coeff[i] + p2.coeff[i]; // add p1 and p2 coeffs, store in temp
    	}	
        return temp; // return new polynomial
    }

    polynomial operator -(const polynomial& p1, const polynomial& p2){
     	polynomial temp = polynomial(0.0,0); // init temp var
        for (int i = 0; i <= polynomial::MAXIMUM_DEGREE; ++i){
    		temp.coeff[i] = p1.coeff[i] - p2.coeff[i]; // subtract p1 and p2 coeffs, store in temp
    	}	
        return temp; // return new polynomial       	
    }

    polynomial operator *(const polynomial& p1, const polynomial& p2){
        assert((p1.degree() + p2.degree()) <= polynomial::MAXIMUM_DEGREE); // ensure both degrees < max
     	polynomial temp = polynomial(0.0,0); // init temp 

        for (int i = 0; i <= p1.degree(); ++i){
        	for (int j = 0; j <= p2.degree(); ++j){
        		temp.coeff[i+j] += p1.coeff[i]*p2.coeff[j]; // mult coeffs, then add to temp coeff of (i+j)
        	}
        }
        return temp; // return new polynomial
    }

    std::ostream& operator << (std::ostream& out, const polynomial& p){
    	
    	int largest = p.degree(); // getting value of largest degree

    	for (int i = largest; i >= 0; --i){

    		if(p.coeff[i] == 0){
    			continue; // if not degree, than skip to next
    		}

    		if (i == largest && (i != 1)){
    			out << p.coeff[i] << "x^" << i; // syntax for first degree not equal to 1
    			continue;
    		}else if(i == largest && (i == 1)) {
                out << p.coeff[i] << "x"; // syntax for first degree equal to 1
                continue;
            }

    		if (p.coeff[i] > 0){ // positive
    			if(i > 1){ 
    				out << " + " << p.coeff[i] << "x^" << i; // syntax for greater than 1
    			}else if(i == 1){
    				out << " + " << p.coeff[i] << "x"; // syntax for x
    			}else if(i == 0){
    				out << " + " << p.coeff[i]; // syntax for constant
    			}
    			continue;
    		}

    		if (p.coeff[i] < 0){ // negative
    			if(i > 1){ 
    				out << " - " << fabs(p.coeff[i]) << "x^" << i; // syntax for greater than 1
    			}else if(i == 1){
    				out << " - " << fabs(p.coeff[i]) << "x"; // syntax for x
    			}else if(i == 0){
    				out << " - " << fabs(p.coeff[i]); // syntax for constant
    			}
    		}
    	}
    	return out;
    }
};
