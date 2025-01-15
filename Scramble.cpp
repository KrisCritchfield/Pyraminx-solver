#include "Pyraminx.h"
#include "NodeandAstar.h"

int main()
{
    int k;
    std::cout<<"input k moves to scramble: ";
    std::cin>>k;
    std::cout<<std::endl;

    //first creates a solved pyraminx and then copies that pyraminx 5 times to make 5 different scrambles 
    //(named after my cats I've had through my life)

    pyraminx solved;
    pyraminxNode* cookie = new pyraminxNode(pyraminx(solved), nullptr);
    int cookiecounter;
    pyraminxNode* cream = new pyraminxNode(pyraminx(solved), nullptr);
    int creamcounter;
    pyraminxNode* sun = new pyraminxNode(pyraminx(solved), nullptr);
    int suncounter;
    pyraminxNode* casca = new pyraminxNode(pyraminx(solved), nullptr);
    int cascacounter;
    pyraminxNode* cotton = new pyraminxNode(pyraminx(solved), nullptr);
    int cottoncounter;

    // Scramble each Pyraminx state by k moves
    cookie->state.scramble(k);
    cookie->hCost=getheuristicvalue(cookie->state);
    cream->state.scramble(k);
    sun->state.scramble(k);
    casca->state.scramble(k);
    cotton->state.scramble(k);

    //my Astar algorithm returns a vector of nodes in order from scramble to solved
    std::vector<pyraminxNode*> cookiepath = aStarSearch(cookie, solved, cookiecounter);
    std::vector<pyraminxNode*> creampath = aStarSearch(cream, solved, creamcounter);
    std::vector<pyraminxNode*> sunpath = aStarSearch(sun, solved, suncounter);
    std::vector<pyraminxNode*> cascapath = aStarSearch(casca, solved, cascacounter);
    std::vector<pyraminxNode*> cottonpath = aStarSearch(cotton, solved, cottoncounter);

    //print the paths for each pyraminx seperated by lines
    std::cout<<"BELOW IS THE PATH FOR THE COOKIE PYRAMINX IT HAD: "<< cookiecounter<<" EXPANSION"<<std::endl
    <<"-------------------------------------------"<<std::endl;
    for(int i=0; i<cookiepath.size();i++)
    {
       cookiepath[i]->state.printpyraminx();
       std::cout<<std::endl;
    }


    std::cout<<"BELOW IS THE PATH FOR THE CREAM PYRAMINX IT HAD: "<< creamcounter<<" EXPANSION"<<std::endl
    <<"-------------------------------------------"<<std::endl;
    for(int i=0; i<creampath.size();i++)
    {
       creampath[i]->state.printpyraminx();
       std::cout<<std::endl;
    }


    std::cout<<"BELOW IS THE PATH FOR THE SUN PYRAMINX IT HAD: "<< suncounter<<" EXPANSION"<<std::endl
    <<"-------------------------------------------"<<std::endl;
    for(int i=0; i<sunpath.size();i++)
    {
       sunpath[i]->state.printpyraminx();
       std::cout<<std::endl;
    }


    std::cout<<"BELOW IS THE PATH FOR THE CASCA PYRAMINX IT HAD: "<< cascacounter<<" EXPANSION"<<std::endl
    <<"-------------------------------------------"<<std::endl;
    for(int i=0; i<cascapath.size();i++)
    {
       cascapath[i]->state.printpyraminx();
       std::cout<<std::endl;
    }

    std::cout<<"BELOW IS THE PATH FOR THE COTTON PYRAMINX IT HAD: "<< cottoncounter<<" EXPANSION"<<std::endl
    <<"-------------------------------------------"<<std::endl;
    for(int i=0; i<cottonpath.size();i++)
    {
       cottonpath[i]->state.printpyraminx();
       std::cout<<std::endl;
    }
    
};