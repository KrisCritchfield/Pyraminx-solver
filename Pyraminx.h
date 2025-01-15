#ifndef PYRAMINX_H
#define PYRAMINX_H

#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

class pyraminx
{
    public:
    std::vector<char> redside;
    std::vector<char> greenside;
    std::vector<char> yellowside;
    std::vector<char> blueside;
    // Function to rotate a face of the pyraminx
    void rotateface(std::vector<char>& face, int clockwise);

    pyraminx();

    pyraminx(const pyraminx& other);
    
    // Moves
    void topcornercounter();
    void topcorner();
    void toprow1counter();
    void toprow1();
    void toprow2counter();
    void toprow2();
    void toprow3counter();
    void toprow3();
    void topcornercounterplus(int k);
    void topcornerplus(int k);

    void leftcornercounter();
    void leftcorner();
    void leftrow1counter();
    void leftrow1();
    void leftrow2counter();
    void leftrow2();
    void leftrow3counter();
    void leftrow3();
    void leftcornercounterplus(int k);
    void leftcornerplus(int k);

    void rightcornercounter();
    void rightcorner();
    void rightrow1counter();
    void rightrow1();
    void rightrow2counter();
    void rightrow2();
    void rightrow3counter();
    void rightrow3();
    void rightcornercounterplus(int k);
    void rightcornerplus(int k);

    void backcornercounter();
    void backcorner();
    void backrow1counter();
    void backrow1();
    void backrow2counter();
    void backrow2();
    void backrow3counter();
    void backrow3();
    void backcornercounterplus(int k);
    void backcornerplus(int k);

    std::vector<pyraminx> getNeighbors();

    // Function to print the pyraminx as a 3D structure
    void printpyraminx();
    
    // Function to scramble the pyraminx
    void scramble(int numberofmoves);

    bool operator==(const pyraminx& other) const;
};

#endif // PYRAMINX_H