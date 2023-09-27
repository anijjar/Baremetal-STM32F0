#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdint.h>

typedef enum {
    LINKEDLIST_OK = 0U,
    LINKEDLIST_ERROR,
    LINKEDLIST_ERROR_CODES_TOTAL
} eLinkedListErrorCodes_t;

typedef struct {
    void * data;
    struct sNode_t * next;
    struct sNode_t * last;
} sLinkedListElement_t;

typedef struct {
    sLinkedListElement_t * elem; // Point to first node; null for empty list
} sLinkedList_t;

eLinkedListErrorCodes_t linkedList_Initialize(sLinkedList_t * in){
    if(in->elem == NULL){
        return LINKEDLIST_ERROR;
    }
    in->elem = NULL;
    return LINKEDLIST_OK;
}

eLinkedListErrorCodes_t linkedList_Deinitialize(sLinkedList_t * in){
    while(!linkedList_IsEmpty(in)) {
        linkedList_PopAtEnd(in);
    }
    return LINKEDLIST_OK;
}

eLinkedListErrorCodes_t linkedList_insertAtStart(sLinkedList_t * in, sLinkedListElement_t * elem){
    // get set the tail of the elem 
};
eLinkedListErrorCodes_t linkedList_insertAtPosition();
eLinkedListErrorCodes_t linkedList_insertAtEnd();

eLinkedListErrorCodes_t linkedList_Search();

eLinkedListErrorCodes_t linkedList_PopAtStart(sLinkedList_t * in);
eLinkedListErrorCodes_t linkedList_PopAtPosition(sLinkedList_t * in);
eLinkedListErrorCodes_t linkedList_PopAtEnd(sLinkedList_t * in){

}

eLinkedListErrorCodes_t linkedList_Size();

eLinkedListErrorCodes_t linkedList_IsEmpty(sLinkedList_t * in){
    if(in == NULL){
        return LINKEDLIST_OK;
    }
    if(in->elem == NULL){
        return LINKEDLIST_OK;
    }
    return LINKEDLIST_ERROR;
}

#endif