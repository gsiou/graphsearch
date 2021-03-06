#ifndef SCC_H
#define SCC_H

#include "types.h"
#include "list_node.h"
#include <stdint.h>

struct Component{
    uint32_t component_id;
    uint32_t included_nodes_count;
    uint32_t* included_node_ids;

    uint32_t* componentNeighborsOutgoing;
    uint32_t neighborNumberOutgoing;
    uint32_t neighborMatrixSizeOutgoing;

    uint32_t* componentNeighborsIncoming;
    uint32_t neighborNumberIncoming;
    uint32_t neighborMatrixSizeIncoming;
};

struct SccNode{
    uint32_t node;
    uint32_t index;
    uint32_t lowlink;
    ptr currentNodePtr;
    ListNode* currentListNode;
    uint32_t* nodeNeighbors;
    uint32_t nextNeighbor;
    uint32_t neighborNumber;
    struct SccNode* previous;
};

class SCC{
public:
    SCC(uint32_t numberOfVertices);
    ~SCC();

    uint32_t findNodeStronglyConnectedComponentID(uint32_t nodeId);
    void setComponent(Component* component);
    Component* getComponent(uint32_t component);
    void setStronglyConnectedComponentID(uint32_t nodeId, uint32_t componentNum);
    uint32_t getComponentsCount();

private:
    static const uint32_t initialCmatrixLength_ = 1024;

    Component** components_;
    uint32_t componentsCount_;
    uint32_t* idBelongsToComponent_;
    uint32_t componentMatrixLength_;
};

#endif
