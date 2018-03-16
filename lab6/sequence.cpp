//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.

#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init(){
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence :: sequence(){
        init();
    }

    //Copy Constructor
    sequence :: sequence(const sequence& source){
        init();
        *this = source;
    }

    sequence::~sequence(){
        list_clear(head_ptr);
        many_nodes = 0;
    }
        
    void sequence::start(){
        cursor = head_ptr; // initialize to start
        precursor = NULL; // initialize to NULL
    }

    void sequence::end(){
       if(many_nodes == 0){
           precursor = NULL; // if there are no nodes in the list, both are NULL
           cursor = NULL;
       }else{
           cursor = tail_ptr; // init cursor to last value
           precursor = head_ptr; // init the precursor to the beggining
           int i = 0;
           while(i < (many_nodes-1)){
               precursor = precursor->link(); // increment precursor for the number of nodes-1 
               ++i;
           }
       }
    }
    
    void sequence::advance(){
        assert(is_item() == true); // ensure item is true
        if(cursor == NULL){
            return; // if cursor is at the end of the list or list is empty, do  nothing
        }
        precursor = cursor; // else precursor is given the cursor
        cursor = cursor->link(); // increment the cursor
    }
    
    void sequence::insert(const value_type& entry){
        if(is_item() == true){ // cursor points to element
            if(precursor == NULL){
                list_head_insert(head_ptr, entry); // insert at the head if no precursor
                cursor = head_ptr; // assign cursor to head
                
            }else{
                list_insert(precursor, entry); // insert before the cursor 
                cursor = precursor->link(); // reinitialize cursor to be next link in segment
            }
        }else{
            list_head_insert(head_ptr, entry); // if no item then cursor is at empty list
            cursor = head_ptr; // init cursor
            precursor = NULL; // no precursor
        }
        ++many_nodes; // increment node value

        node* temp = head_ptr;
        for (int i = 0; i < many_nodes; ++i) {
            tail_ptr = temp; // assign tail_ptr after every insertion to ensure correct
            temp = temp->link(); 
        }
    }
    
    void sequence::attach(const value_type& entry){
        if (is_item() == true){
            precursor = cursor; // if there is an item then increment precursor
            list_insert(cursor, entry); // insert after the cursor
            cursor = cursor->link(); // increment cursor to point to added value
        }else{
            if (head_ptr == NULL){
                list_head_insert(head_ptr, entry); // if empty list then attach to head_ptr
                cursor = head_ptr; // init cursor
                precursor = NULL; // init precursor
            }else{
                list_locate(head_ptr, many_nodes); // if not, locate the node we need to add after
                list_insert(precursor, entry); // insert the node after
                cursor = precursor->link(); // re init cursor
            }
        }
        ++many_nodes; // increment nodal value
    }
    
    void sequence::operator =(const sequence& source){
        if(this == &source)
            return; // if self assignment then quit
        
        list_clear(head_ptr); // re init assigned value
        init();
        list_copy(source.head_ptr, head_ptr, tail_ptr); // copy all contents from source to dest list
        
        if(source.precursor == NULL){
            if(source.cursor != NULL){
                cursor = head_ptr; // if cursor valid in source, assign it to head of new copy
            }else{
                cursor = NULL; // assign cursor to null if cursor points to nothing
            }
            precursor = NULL;  // if the source precursor is null, so is the copy
        }else{
            node* temp = head_ptr;
            node* sourceTemp = source.head_ptr;
            
            while(sourceTemp != source.precursor){
                sourceTemp = sourceTemp->link(); // if sourceTemp & source precursor dont match then continue to increment 
                temp = temp->link();
            }
            cursor = temp->link(); // since found precursor init cursor to the link
            precursor = temp; // assign precursor
        }
        
        many_nodes = source.many_nodes; // copy the number of nodes from source to destination
    }
    
    void sequence::remove_current(){
        assert(is_item() == true);
        
        if(many_nodes == 1){
            list_head_remove(head_ptr); // deleting head if only one node (but going to empty list)
            cursor = NULL; // re init all cursor, precursor, head_ptr
            precursor = NULL;
            head_ptr = NULL;
            many_nodes--; // decrement the amount of nodes to 0
            return;
        }
        
        if(cursor == head_ptr){
            node* temp = head_ptr; // if we are deleting head pointer set pointer to it (with a list still)
            head_ptr = head_ptr->link(); // re init head_ptr to next node
            delete(temp); // delete head
            cursor = head_ptr; // re init cursor value
            precursor = NULL; // since cursor at head then precursor is nothing
            many_nodes--; // decrement number of nodes
            return;
        }
        
        cursor = cursor->link(); // then we are removing from the list or end
        list_remove(precursor); // remove value
        many_nodes--; // decrement number of nodes
    }
    
    sequence::size_type sequence::size() const{
        return many_nodes; // return number of nodes value
    }
    
    bool sequence::is_item() const{
        if(cursor == NULL){
            return false; // if cursor doesnt point to anything, return false
        }
        return true;
    }
    
    node::value_type sequence::current() const{
        assert(is_item() == true);
        return cursor->data(); // return data stored in what cursor points to
    }   
};
