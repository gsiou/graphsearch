#include <stdlib.h>

#include "node_index.h"
#include "buffer.h"
#include <iostream>

NodeIndex::NodeIndex(Buffer* buffer){
    this->buffer_ = buffer;
    this->data_ = (NodeIndexData*) malloc(sizeof(NodeIndexData) * INITIAL_SIZE);
    this->currentSize_ = 0;
    this->maxSize_ = INITIAL_SIZE;
    for(int i = 0; i < this->maxSize_; i++){
        this->data_[i] = PTR_NULL;
    }
}

NodeIndex::~NodeIndex(){
    free(data_);
}

uint32_t NodeIndex::getCurrentSize(){
    return this->currentSize_;
}

uint32_t NodeIndex::getMaxSize(){
    return this->maxSize_;
}

bool NodeIndex::insertNode(uint32_t nodeId){
    if(this->buffer_ == 0){
        return false;
    }

    // Create new node in buffer
    ptr nodeLoc;
    nodeLoc = this->buffer_->allocNewNode();

    NodeIndexData nodeData = nodeLoc;

    // See if we have space in array
    if(nodeId >= this->maxSize_){
        // We have to give more space
        NodeIndexData* resized;
        // We add +1 in memory calculations because node index array
        // is 0-indexed so id 20 gets in the 21st position etc.
        int resize_factor = (nodeId + 1) / this->maxSize_;
        if((nodeId + 1) % this->maxSize_ != 0){ // If we have remainder we need one more
            resize_factor++;
        }
        resized = (NodeIndexData*) realloc(this->data_, this->maxSize_ * resize_factor * sizeof(NodeIndexData));
        if(resized == NULL){
            // Realloc failed, free resources and fail
            free(this->data_);
            return false;
        }

        //std::cout << "REALLOC GOOD MAN,LAST SIZE:"<< this->maxSize_ << " ,NEW SIZE:" << this->maxSize_ * resize_factor <<std::endl;

        // Reallocation was successful, overwrite data
        this->data_ = resized;
        int oldMax = this->maxSize_;
        this->maxSize_ = this->maxSize_ * resize_factor;
        for(int i = oldMax; i < this->maxSize_; i++){
            this->data_[i] = PTR_NULL;
        }
    }

    // Store pointer to index
    this->data_[nodeId] = nodeData;
    this->currentSize_++;
    //std::cout << "index-after data ok" <<std::endl;
    return true;
}

ptr NodeIndex::getListHead(uint32_t nodeId){
    if(nodeId >= this->maxSize_){
        // We dont have information for such node
        return PTR_NULL;
    }

    return this->data_[nodeId];
}
