#include "NodeandAstar.h"

struct PyraminxHash {
    std::size_t operator()(const pyraminx& p) const {
        std::size_t hashValue = 0;
        // Combine the hash of each side's vector into a single hash value
        for (const auto& side : {p.redside, p.greenside, p.yellowside, p.blueside}) {
            for (const auto& color : side) {
                hashValue ^= std::hash<int>()(color) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
            }
        }
        return hashValue;
    }
};

// Helper function to reconstruct the path from the goal node to the start node
std::vector<pyraminxNode*> reconstructPath(pyraminxNode* node) {
    std::vector<pyraminxNode*> path;
    while (node != nullptr) {
        path.push_back(node);
        node = node->parent;
    }
    std::reverse(path.begin(), path.end()); //[0]=scramble, [path.size()-1] = solved
    return path;
}

// Main A* search function
std::vector<pyraminxNode*> aStarSearch(pyraminxNode* startNode, pyraminx& goalState, int& totalNodesExpanded) {
    // Priority queue (min-heap) to hold open nodes, sorted by fCost
    auto cmp = [](pyraminxNode* a, pyraminxNode* b) { return a->fCost() > b->fCost(); };
    std::priority_queue<pyraminxNode*, std::vector<pyraminxNode*>, decltype(cmp)> openSet(cmp);

    // Set to keep track of states in the open set
    std::unordered_set<pyraminx, PyraminxHash> openSetStates;

    // Set to keep track of closed nodes (explored nodes)
    std::unordered_set<pyraminx, PyraminxHash> closedSet;

    // Insert the start node into the open set
    openSet.push(startNode);
    openSetStates.insert(startNode->state);

    totalNodesExpanded = 0;

    while (!openSet.empty()) {
        // Get the node with the lowest fCost
        pyraminxNode* currentNode = openSet.top();
        openSet.pop();
        openSetStates.erase(currentNode->state); // Remove from the open set states

        // Check if we reached the goal
        if (currentNode->state == goalState) 
        {
            return reconstructPath(currentNode); // Return the path from start to goal
        }
        
        totalNodesExpanded++; //increase number of nodes expanded

        // Add current node's state to the closed set
        closedSet.insert(currentNode->state);

        // Generate child nodes (neighbors of current node)
        std::vector<pyraminx> neighbors = currentNode->state.getNeighbors();

        for (const auto& neighborState : neighbors) {
            // Skip if the neighbor is already in the closed set
            if (closedSet.count(neighborState) > 0) {
                continue;
            }

            // Check if the neighbor state is already in the open set
            bool inOpenSet = openSetStates.count(neighborState) > 0;

            // If the neighbor is not in the open set, create a new node
            if (!inOpenSet) 
            {
                pyraminxNode* neighborNode = new pyraminxNode(neighborState, currentNode);
                neighborNode->gCost = currentNode->gCost + 1;
                neighborNode->hCost = getheuristicvalue(*neighborNode); // Compute heuristic value

                // Add the neighbor node to the open set and mark its state
                openSet.push(neighborNode);
                openSetStates.insert(neighborState);

                // Increment counter since this is a newly expanded node
            }
        }
    }

    // Return empty path if no solution found
    return {};
}






    int pyraminxNode::fCost() const { return gCost + hCost; }  // Total cost (f(n) = g(n) + h(n))

    // Constructor
    pyraminxNode::pyraminxNode(pyraminx currentstate, pyraminxNode* parentpointer)
    : state(currentstate),  // Initialize state directly using the copy constructor of pyraminx
      parent(parentpointer),  // Initialize the parent pointer
      gCost(0),               // Initialize gCost to 0
      hCost(0)                // Initialize hCost to 0
    {}
    // The constructor body can be empty since everything is initialized in the initialization list


    // Comparison operator for priority queue (lower fCost has higher priority)
    bool pyraminxNode::operator<(const pyraminxNode& other) const {
        return fCost() > other.fCost();  // Greater fCost means lower priority (min-heap behavior)
    }



    int getheuristicvalue(pyraminxNode example)
    {
        std::vector<char> front{example.state.redside[0]};
        std::vector<char> left{example.state.greenside[0]};
        std::vector<char> right{example.state.yellowside[0]};
        std::vector<char> bottom{example.state.blueside[0]};

        for (int i = 1; i < 16; i++) 
        {
        // Check for unique colors and add them if not present
        if (std::find(front.begin(), front.end(), example.state.redside[i]) == front.end()) 
        {
            front.push_back(example.state.redside[i]);
        }

        if (std::find(left.begin(), left.end(), example.state.greenside[i]) == left.end()) 
        {
            left.push_back(example.state.greenside[i]);
        }

        if (std::find(right.begin(), right.end(), example.state.yellowside[i]) == right.end()) 
        {
            right.push_back(example.state.yellowside[i]);
        }

        if (std::find(bottom.begin(), bottom.end(), example.state.blueside[i]) == bottom.end()) 
        {
            bottom.push_back(example.state.blueside[i]);
        }
    }

        return (std::max({front.size(), left.size(), right.size(), bottom.size()})-1);
    }