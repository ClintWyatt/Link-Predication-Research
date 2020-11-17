#ifndef RANDOMNODE_HPP
#define RANDOMNODE_HPP
using namespace std;

//the size will need to be at least half of the number of nodes in the graph

//first add all the possible random nodes to a array
//second, sort the nodeList
//third, add all the random nodes to the sample graph by through doing a comparison to the origional graph
void randomNode(A_Network &X, A_Network &S, int size)
{
    vector<bool> visited; 
    vector <int> nodeList; //used to keep track of the random nodes added
    int_double node;
    visited.resize(X.size());
    int nodeCount =0;
    int edge;
    visited.assign(visited.size(), 0);
    S.clear();
    S.resize(X.size());


    for(int i =0; i < S.size(); i++)
    {
        S[i].Row = i;
    }

    
    //start of the randomNode algorithm
    while(nodeCount < size)
    {
        edge = rand() % S.size();
        if(visited[edge] == 0)
        {
            visited[edge] =1;
            
            nodeCount++;
        }
    }

    //sort the node list by radix sort

}



#endif