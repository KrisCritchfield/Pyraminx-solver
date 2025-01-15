#ifndef NODEANDASTAR_H
#define NODEANDASTAR_H

#include "Pyraminx.h"
#include <queue>
#include <functional>
#include <algorithm>
#include <unordered_set>

class pyraminxNode 
{
    public:
    pyraminx state;                     // Current state of the Pyraminx
    pyraminxNode* parent;               // Pointer to the parent node
    int gCost;                          // Cost from the start node to this node (g(n))
    int hCost;                          // Heuristic cost from this node to the goal (h(n))
    int fCost() const;                  // Total cost (f(n) = g(n) + h(n))
    pyraminxNode(pyraminx currentstate, pyraminxNode* parentpointer = nullptr);
    bool operator<(const pyraminxNode& other) const; // Comparison operator for priority queue (lower fCost has higher priority)
};

int getheuristicvalue(pyraminxNode example); //gets heuristic value by getting max(#different colors on each face)-1
std::vector<pyraminxNode*> reconstructPath(pyraminxNode* node); //returns a vector of in order from scramble to solved
std::vector<pyraminxNode*> aStarSearch(pyraminxNode* startNode, pyraminx& goalState, int& totalNodesExpanded); //the astar search




#endif // NODEANDASTAR_H