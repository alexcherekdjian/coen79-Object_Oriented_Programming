
#ifndef ITEM_CPP
#define ITEM_CPP
#include <cassert>
#include <string>
#include "node.h"

namespace coen79_lab7
{
    node::node(const std::string &itemName, const float &newPrice, node *nextNode) {
        name = itemName; // init name
        price = newPrice; // init price
        link = nextNode; // init link
    }
    
    void node::setName(const std::string &newName) {
        name = newName; // set new name
    }
    
    void node::setPrice(const float &newPrice) {
        price = newPrice; // set new price
    }
    
    void node::setLink(node *new_next) {
        link = new_next; // set new link
    }
    
    node* node::getLink() {
        return link; // get the link
    }
    
    const node* node::getLink() const {
        return link; // const version get the link
    }
    
    std::string node::getName() const{
        return name; // get the name
    }
    
    float node::getPrice() const {
        return price; // get the price
    }
    
    void list_init(node*& head, node*& tail, const std::string& newName, const float& newPrice) {
        head = new node(newName, newPrice, NULL); // create a new head node with name and price pointing to NULL
        tail = head; // assign tail as head 
    }
    
    void list_tail_insert(node*& tail, const std::string &newName, const float &newPrice){
    	assert(tail != NULL); // ensure tail is not empty
    	assert(newName.length() > 0); // ensure name is inputed with characters

    	node* newNode = new node(newName, newPrice, NULL); // create a new node
    	tail->setLink(newNode);	// tail points to new node
    	tail = newNode; // assign tail pointer as the new node
    }
    
    void list_clear(node*& head){
    	while (head != NULL) 
    	    list_head_remove(head); // as long as not end of list, remove from head
    }
    
    void list_copy(const node *old_head, node* &new_head, node* &new_tail) {
        new_head = NULL; // init new head
        new_tail = new_head; // init new tail to new head
        
        const node *cur = old_head; // create cursor
        while (cur != NULL) {
            if (new_head == NULL) {
                new_head = new node(cur->getName(), cur->getPrice()); // insert at head
                new_tail = new_head; // assign head to tail
            }
            else {
                new_tail->setLink(new node(cur->getName(), cur->getPrice())); // insert node into new node
                new_tail = new_tail->getLink(); // reassign tail pointer
            }
            cur = cur->getLink(); // increment cursor
        }
    }
    
    void list_head_remove(node*& head){
        assert(head != NULL); // ensure head pointer is valid
        node *remove_ptr; // init new remove ptr

    	remove_ptr = head; // assign to head
    	head = head->getLink(); // reinitialize head pointer
    	delete (remove_ptr); // delete pointer
    }
    
    void list_print(node *head){
        node *cur = head; // init cursor to head
        while (cur != NULL) {
            std::cout << "- " << cur->getName() << ", where the price is $" << cur->getPrice() << std::endl; // as long as nodes, print out values
            cur = cur->getLink(); // increment cursor
        }
    }
    
    bool list_contains_item(node *head_ptr, const std::string& newName) {
        return (list_search(head_ptr, newName) != NULL); // if name match the return true
    }
    
    
    node* list_search(node* head_ptr, const std::string& target){
        node *cursor; // init cursor
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
            if (target == cursor->getName( ))
                return cursor; // if target is name than return the pointer
        return NULL; // if not found then return NULL
    }
    
    const node* list_search(const node* head_ptr, const std::string & target){
        const node *cursor; // init cursor
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
            if (target == cursor->getName( ))
                return cursor; // if target is name than return the pointer
        return NULL; // if not found then return NULL
    }
}

#endif
