Pyraminx: For the Pyraminx I made each side a vector of 16 elements, each element representing a triangle. 
From there I made each of the 32 turns by switching elements of each array. 
The Pyraminx class has the 4 vectors, 32 turns, a print function and a scramble function. 
Here is an example of how I numbered each face (also inside the code).

//             G0                            R0                           Y0
//         G1  G2  G3                    R1  R2  R3                   Y1  Y2  Y3
//     G4  G5  G6  G7  G8            R4  R5  R6  R7  R8           Y4  Y5  Y6  Y7  Y8
//  G9 G10 G11 G12 G13 G14 G15    R9 R10 R11 R12 R13 R14 R15   Y9 Y10 Y11 Y12 Y13 Y14 Y15
//              
//                                b15 b14 b13 b12 b11 b10 b9
//                                    b8  b7  b6  b5  b4
//                                        b3  b2  b1
//                                            b0


pyraminxNode: This is the node for Astar algorithm. 
It has a pyraminx, hCost, gCost, a pointer to its parent pyraminxNode, function for returning the Fcost, and an overloaded < operator to compare for the min heap.


Randomizer (scramble function): To make the Astar algorithm more time efficient for demonstration, I made the randomizer only rotate counterclockwise and the solver rotate clockwise. 
I made two functions for each corner that would take an integer argument of 1-3 that would decide the number of rows you want to move, 1 being just the corner, 2 being the corner and next row and so on. 
Here is how the top corner functions are named as example:  “topcornerplus” and “topcornercounterplus”. 
The scramble function then takes an integer argument numberofmoves to determine the number of moves to do and then gets a random number between 1-12 to determine what counterclockwise move to do.


getNeighbors function: getNeighbors is a function that is called in the A* search that creates 12 copies of the pyraminx that was put into the argument and does 1 clockwise move on it and returns a vector of pyraminxs.


PyraminxHash: a structure with a single method called operator(), it is just the hash function for the sets used to store the states of pyraminxs in openSetStates and closedSet. 

 
aStarSearch function: This is the search function, it takes three arguments, a pyraminxNode, a pyraminx, and an integer. I will describe what it does in list form as to make it neater. 

1.	Defines a lambda function called cmp that takes two pyraminx operators and will compare their fcost, this will be used for the priority queue. 
2.	Makes the priority queue called openset using the cmp lambda function. 
3.	Makes another set called opensetstates so it can search for pyraminx states in the open set, along with closed set that will store visited states.
4.	Adds the start scrambled state to openset and opensetstates and then starts the while loop, visiting all nodes if no solution found. 
5.	At the start of the loop, it makes the current node the top of the open set and adds it to the closed set, it then checks if its the solved/goal state and returns the path if it is or continues the loop if it isn’t.
6.	Increments totalNodesExpanded to keep count of total nodes that have had children
7.	Inserts the current nodes state into the closed set to not revisit it
8.	Calls generateNeighbors and stores the list of children in neighbors
9.	Starts new loop, looking at the children from the list, if they are in the closed set already, skip to next child
10.	Checks if the child's state is in the open set, if not, create a node for the child and add it to the open set
11.	Repeat 5-10 until solution is found or return nothing if not found (will most likely crash before not found)


Scramble.cpp: scramble.cpp is a demonstration of the program and the astar search algorithm, here is what it does:
1. asks how many moves you want to scramble by
2. makes a pyraminx
3. makes 5 copies of the pyraminx to make 5 different scrambles
4. scrambles each pyraminx by k moves
5. calls the Astar search algorithm on each pyraminx to solve it
6. prints the path from scrambled to solved for each pyraminx
