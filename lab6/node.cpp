// FILE: node.cpp
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <iostream>
#include <cstdlib>    // Provides NULL and size_t

using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
	const node *cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }

    void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr){
        if(start_ptr == NULL || start_ptr == end_ptr){ 
            head_ptr = NULL; // empty list so init head and tail
            tail_ptr = NULL;
            return;
        }

        if(head_ptr != NULL)
            list_clear(head_ptr); // if not null then clear contents

        list_head_insert(head_ptr, start_ptr->data()); // insert a head
        tail_ptr = head_ptr; // init tail pointer
        node* cursor = start_ptr->link(); // create a cursor at the beginning of original list

        while(cursor != NULL && cursor != end_ptr){
            list_insert(tail_ptr, cursor->data()); // as long as not end of list insert into new list
            cursor = cursor->link(); // increment cursor
            tail_ptr = tail_ptr->link(); // increment tail
        }
    }

    size_t list_occurrences(node* head_ptr, const node::value_type& target){
        node* cursor = head_ptr; // cursor is the start of list
        size_t popularity = 0; // init number of occurrences

        while(cursor != NULL){
            if(cursor->data() == target){
                ++popularity; // if target found increment count
            }
            cursor = cursor->link(); // go to next link until end of list
        }
        return popularity;
    }

    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position){
        assert((position > 0) && (position <= list_length(head_ptr)+1));

        if(position == 1){
            node* addedNode = new node(entry, head_ptr); // if want insert at head
            head_ptr = addedNode; // ensure head_ptr is the new node
        }else{
            node* precursor = head_ptr; // init precursor to head
            node* cursor = list_locate(head_ptr, position); // locate where position is in list

            while(precursor->link() != cursor){
                precursor = precursor->link(); // init precursor to before cursor
            }

            node* addedNode = new node(entry, cursor); // create the new node with correct links

            precursor->set_link(addedNode); // re init precursor link to new node
        }
        
    }

    node::value_type list_remove_at(node*& head_ptr, size_t position){
        assert((position > 0) && (position <= list_length(head_ptr)));
        node::value_type ans;
        node* cursor  = head_ptr;

        if(position == 1){
            head_ptr = cursor->link(); // removing the head so change head_ptr to next node
            ans = cursor->data(); // store data of deletion
            delete(cursor); // delete the cursor
        }else{
            node* precursor = head_ptr;
            node* cursor = list_locate(head_ptr, position); // locate position node

            while(precursor->link() != cursor){
                precursor = precursor->link(); // init precursor to before cursor
            }

            ans = cursor->data(); // store data of deletion
            precursor->set_link(cursor->link()); // re init precursor to exclude deleted node
            delete(cursor); // delete node
        }

        return ans;
    }

    node* list_copy_segment(node* head_ptr, size_t start, size_t finish){
        assert(1 <= start);
        assert(start <= finish);
        assert(finish <= list_length(head_ptr));

        node* cursor = head_ptr; // initialize cursor to beggining of list
        size_t loopCounter = start;

        node* tempList = NULL;

        while((start) != 1){
            cursor = cursor->link(); // want node at item to add to new list
            --start; // decrement loop
        }

        list_head_insert(tempList, cursor->data()); // insert at the head
        node* tail_ptr = tempList;

        for (size_t i = loopCounter+1; i <= finish; ++i){ 
            cursor = cursor->link();
            list_insert(tail_ptr, cursor->data()); // insert the rest of the list if more than a head
            tail_ptr = tail_ptr->link();
        }

        return tempList;
    }

    void list_print(const node* head_ptr){

        while(head_ptr != NULL){
            cout << head_ptr->data() << " "; // while not at the end of list print the node and data
            head_ptr = head_ptr->link(); // continue through list
        }
    }

    void list_remove_dups(node* head_ptr){

        node* cursor = head_ptr;
        while(cursor != NULL){
            node* runner = cursor; // create cursor to check for duplicates

            while(runner->link() != NULL){
                if(cursor->data() == runner->link()->data()){
                    node* tmp_delete = runner->link(); // if not end of list and there is a duplicate get node to delete
                    node* tmp_link = runner->link()->link(); // re init pointers to exclude the deletion node
                    runner->set_link(tmp_link);
                    delete tmp_delete; // delete the duplicate
                }else{
                    runner = runner->link(); // check next value
                }
            }
        cursor = cursor->link(); // check another value of more than one value in list
        }
    }

    node* list_detect_loop(node* head_ptr){
        assert(head_ptr != NULL);
        node* slow_runner = head_ptr;
        node* fast_runner = head_ptr;

        while(fast_runner != NULL && fast_runner->link() != NULL){
            // increment slow (1 hop) and fast runner (2 hops) until either/both NULL 
            slow_runner = slow_runner->link();
            fast_runner = fast_runner->link()->link();
            
            if(slow_runner == fast_runner){
                break; // if they equal each other then we have  aloop
            }
        }

        if(fast_runner == NULL || fast_runner->link() == NULL){
            return NULL; // if either equal NULL then no loop so break
        }

        slow_runner = head_ptr; // reset slow runner

        while(slow_runner != fast_runner){
            slow_runner = slow_runner->link(); // increment each runner until meet
            fast_runner = fast_runner->link(); // thats where loop will reside
        }

        return fast_runner;
    }
    
};
