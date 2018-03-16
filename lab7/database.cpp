// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots

#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    database::database(const size_type& initial_capacity) {
        used_slots = 0; // init used slots
        aloc_slots = initial_capacity; // init aloc slots
        company_array = new company[aloc_slots]; // create new company_array
    }
    
    database::database(const database &src) {
        Debug("Copy constructor..." << std::endl);
        company_array = new company[src.aloc_slots]; // create new company_array
    	aloc_slots = src.aloc_slots; // init aloc slots
    	used_slots = src.used_slots; // init used slots
    	
    	for(int i = 0; i < src.used_slots; ++i){
    		company_array[i] = src.company_array[i]; // copy all contents from source to new object
    	}
    }
    
    database& database::operator= (const database &rhs) {
        Debug("Assignment operator..." << std::endl);
        aloc_slots = rhs.aloc_slots; // init aloc slots
        used_slots = rhs.used_slots; // init used slots

        company_array = new company[rhs.aloc_slots]; // create new company_array with new slots

        for(int i = 0; i < rhs.used_slots; ++i){
            company_array[i] = rhs.company_array[i]; // copy all contents from source to new object
        }

    	return *this;
    }

    database::~database() {
    	delete[](company_array); // delete the allocated array
    	aloc_slots = 0; // init aloc slots
    	used_slots = 0; // init used slots
    }
    
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size

        if (new_capacity < used_slots)
            new_capacity = used_slots; // Cant allocate less than we are using
        
    	company* newCompanyArray = new company[new_capacity]; // allocate new array
    	
    	for(int i = 0; i < used_slots; ++i){
    		newCompanyArray[i] = company_array[i]; // copy all contents from old array to new one
    	}

    	aloc_slots = new_capacity; // init aloc slots
    	company_array = newCompanyArray; // assign new array to company_array
 }

    bool database::insert_company(const std::string &entry) {
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0); // ensure length entry is not empty
        size_type pos = search_company(entry); // find the company
        
        if (pos != COMPANY_NOT_FOUND) {
            return false; // If you find a company then return false, because there are duplicates
        }
	
    	if(used_slots == aloc_slots){
    		reserve(aloc_slots+1); // reserve enough space for another company
        }
    	
        company_array[used_slots] = company(entry); // create new company in last slot
        ++used_slots; // increment used slots
        return true;
    }
    
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0); // ensure both lengths are not empty
            
    	size_type index = 0;
    	index = search_company(company); // check to see if company is in database

    	if(index == COMPANY_NOT_FOUND)
    		return false; // if nothing found, return false
	
	   company_array[index].insert(product_name, price); // insert product into certain index recieved
	   return true; 
    }
    
    bool database::erase_company(const std::string &company) {
        assert(company.length() > 0); // ensure string not empty
        size_type company_index = search_company(company); // find the company in database
        
    	if(company_index == COMPANY_NOT_FOUND)
    		return false; // if company not in database then nothing to delete
    	
    	for(int i = company_index; i < used_slots-1; ++i){
    		company_array[i] = company_array[i+1]; // shift all elts down one to overwrite element to delete
    	}

        --used_slots; // decrement used slots
        return true;
    }
    
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        assert(cName.length() > 0 && pName.length() > 0); // ensure string are not empty

        size_type company_index = search_company(cName); // find the company in database

        if(company_index == COMPANY_NOT_FOUND)
            return false; // if no company found, return false

        node* temp = company_array[company_index].get_head(); // init temp to head to insert into search
        node* answer = list_search(temp, pName); // find the item

        if(answer == NULL)
            return false; // if not found, nothing to delete

        if(answer == company_array[company_index].get_head()){
            list_head_remove(answer); // if item is at the head, call remove head
        }else{
            node* cursor; // init cursor

            for (cursor= company_array[company_index].get_head(); cursor != NULL; cursor = cursor->getLink()){
                if(cursor->getLink() == answer)
                    break; // increment until get previous pointer
            }
            cursor->setLink(answer->getLink()); // reset links using previous pointer
            delete answer; // delete item to delete
        }

        return true;
    }
    
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0); // ensure entry is not empty
    	    	
    	for(int i = 0; i < used_slots; ++i){
    		if(company == company_array[i].get_name()){
    			return i; // if a company is found, return the index
    		}
    	}

	   return COMPANY_NOT_FOUND;
    }
    
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0); // ensure entry is not empty

        size_type c_index = search_company(cName); // find the company
        
        if (c_index == COMPANY_NOT_FOUND) {
            return false; // if no company found then nothing to print
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl; // print company
        company_array[c_index].print_items(); // print the products
        std::cout << std::endl; // end line
        
        return true;
    }
    
    void database::print_companies() {
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl; // print out all the companies
        }
    }
}

#endif
