#include <stdlib.h>
#include <stdio.h>
#include "pri_queue.h"
/** @file pri_queue.c */
static Node_ptr_t head = NULL;


/**
 * Insert a Node into a priority queue.
 * @param priority
 * @param data
 * @author Romit Sagu
 */
void PQ_insert(int priority, char * data) {
    Node_ptr_t temp = malloc(sizeof(Node_ptr_t));
    Node_ptr_t temp2 = malloc(sizeof(Node_ptr_t));
    Node_ptr_t new = malloc(sizeof(Node_ptr_t));
    new->priority = priority;
    new->data = data;
    
    temp = head;
    if (head == NULL){ // Works up to 5th assert (Loads the first value when the head is empty)
        head = new;
    }
    else if(head->priority <= priority){ // If the new entity is the highest priority store the 
        temp->data = head->data;         // head in a temp variable and make the new element the head.
        temp->priority = head->priority; // Works up to th 8th assert
        temp->next = head->next;
        
        head = new;
        head->next = temp;      
    }
    else{
        while (temp->next != NULL && new->priority < temp->next->priority){
            temp = temp->next;
        }
        
        if(temp->next != NULL){ // If the priority is somewhere in the middle the while loop ends at the 
            temp2 = temp->next; // element that would be 1 ahead of the new entity.
            temp->next = new;   // Works up to the 19th assert
            new->next = temp2;
        }
        else{ // extra case if the new entity is the last one in the queue (not used in the main)
            temp->next = new;
            new->next = NULL;
        }
    }
    
}

/**
 * Delete and return the node with the highest priority.
 * @return The highest priority Node.
 */
Node_ptr_t PQ_delete() {
  Node_t *temp;
    temp = head;
    head = head->next;    
    temp ->next = NULL;
    return temp;
}

/**
 * Do NOT modify this function.
 * @return A pointer to the head of the list.  (NULL if list is empty.)
 */
Node_ptr_t PQ_get_head() {
    return head;
}

/**
 * Do NOT modify this function.
 * @return the number of items in the queue
 */
int PQ_get_size() {
    int size = 0;
    Node_ptr_t tmp;
    for(tmp = head; tmp != NULL; tmp = tmp->next, size++)
        ;
    return size;
}


