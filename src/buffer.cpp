#include "buffer.h"
#include "list_node.h"
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <iostream>


Buffer::Buffer(){
    //Buffer constructor,initialize to inital size
    bufferSpace_ = (ListNode*)malloc(INITIAL_BUFFER_SIZE*sizeof(ListNode));
    bufferSize_ = INITIAL_BUFFER_SIZE;
    numberOfNodes_ = 0;
}

Buffer::~Buffer(){
    // Destructor,deletes bufferSpace
    free(bufferSpace_);
}

ptr Buffer::allocNewNode(){
    //Returns the index of the new block in the buffer

    if(numberOfNodes_ >= bufferSize_){
        // Double the size of the buffer if needed
        bufferSpace_ = (ListNode*)realloc(bufferSpace_,bufferSize_*sizeof(ListNode)*2);
        if(bufferSpace_ == NULL){
            std::cout << "BUFFER OVERFLOW" << std::endl;
            return PTR_NULL;
        }
        bufferSize_ *= 2;
    }

    memcpy(&bufferSpace_[numberOfNodes_], &this->templateListNode_, sizeof(ListNode));
    ptr nodePtr = numberOfNodes_;
    numberOfNodes_++;
    return nodePtr;
}

ListNode* Buffer::getListNode(ptr nodeIndex){
    // Returns a pointer to the requested ListNode
    //  or Null if it does not exists

    if(nodeIndex >= bufferSize_ || nodeIndex >= numberOfNodes_){
        return NULL;
    }
    return (ListNode*)&(bufferSpace_[nodeIndex]);

}
