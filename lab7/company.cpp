// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)

#include <iostream>
#include <string>
#include <stdbool.h>
#include <cassert>
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    company::company() {
        this->company_name = ""; // init comapny name
        this->head_ptr = NULL; // init head
        this->tail_ptr = NULL; // init tail
    }
    
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0); // ensure length is above 0 chars

    	this->company_name = company_name; // init comapny name
    	this->head_ptr = NULL; // init head
    	this->tail_ptr = NULL; // init tail
    }
    
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);
	
    	company_name = src.company_name; // init comapny name
    	head_ptr = NULL; // init head
    	tail_ptr = NULL; // init tail
    	list_copy(src.head_ptr, head_ptr, tail_ptr); // copy all nodes into new company
    }

    company& company::operator= (const company &src) {
        Debug("Company assignment operator..." << std::endl);
        list_clear(head_ptr); // erase all contents in lhs
        company_name = src.company_name; // init comapny name
        head_ptr = NULL; // init head
        tail_ptr = NULL; // init tail
	    list_copy(src.head_ptr, head_ptr, tail_ptr); // copy all nodes into lhs company

	   return *this;
    }
     
    company::~company() {
        list_clear(head_ptr); // delete all nodes
    }
    
    std::string company::get_name() const {
        return company_name; // get company name
    }
    
    const node *company::get_head() const {
        return head_ptr; // get head
    }
    
    const node *company::get_tail() const {
        return tail_ptr; // get tail
    }
    
    node* company::get_head() {
        return head_ptr; // get head
    }
    
    node* company::get_tail() {
        return tail_ptr; // get tail
    }
    
    void company::print_items() {
        list_print(head_ptr); // print out all the nodes
    }
    
    
    bool company::insert(const std::string& product_name, const float& price){
        
        assert(product_name.length() > 0); // ensure product length is entered

        if (list_contains_item(head_ptr, product_name)){
            return false; // true, then return nothing happened
        }
        
        if (head_ptr == NULL){
            list_init(head_ptr, tail_ptr, product_name, price); // if no nodes, than call init
        }else{
            list_tail_insert(tail_ptr, product_name, price); // if nodes insert at tail
        }
        
        return true;
    }

    
    bool company::erase(const std::string& product_name){
        assert(product_name.length() > 0); // ensure product name is greater than 0

    	node* remove_ptr = list_search(head_ptr, product_name); // find pointer to remove
    	if(remove_ptr == NULL){
    		return false; // if returns NULL, node not found so return nothing done
    	}else{
    		if(head_ptr == remove_ptr){
    			list_head_remove(head_ptr); // if head is one to remove delete head
    		}else{
    			node* prev_ptr = head_ptr->getLink(); // else prev ptr is the next node from head
    			
    			while(prev_ptr != remove_ptr){
    				prev_ptr = prev_ptr->getLink(); // while still nodes, increment until get prev ptr before removal
    			}
    			
    			prev_ptr->setLink(remove_ptr->getLink()); // reset links with prev ptr
    			delete remove_ptr; // delete actual value to delete
    		}
    	}
	   return true;
    }
   
}
