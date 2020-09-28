#ifndef KATZ_HPP
#define KATZ_HPP

using namespace std;

int pathLength4(vector<int> *node1Neighbors, vector<int> *node2Neighbors, Edge missing, A_Network *X);
int pathLength3(vector<int> *node1Neighbors, vector<int> *node2Neighbors, Edge missing, A_Network *X);

void katz(A_Network *X, vector<Edge> *missing, vector<double_string> & predictedEdges, string alg)
{
    vector<int> node1Neighbors;//represents nodes that are on a path for node1. Gets updated every time we go a path futher (n + 1).
    vector<int> node2Neighbors;//represents the nodes that are adjacent to node2. Used for path of 3
    double score;//represetns the score for the missing edges
    string edge; //represents the 
    double_string index;
    int n1, n2, commonCount;//n1 and n2 are indexes in the lists of node1 and node2 of the missing edge. Commoncount represents the number of paths for lengths of 1, 2, and 3.
    for(int i =0; i < missing->size(); i++)
    {
        //cout <<"missing edge: " << missing->at(i).node1 << " " << missing->at(i).node2 << endl;
        score = 0.0;//resetting the score for the current missing edge
        node1Neighbors.clear();//clearing the previous neighbors for the last node1 (part of the previous missing edge)
        node2Neighbors.clear();//clearing the previous neighbors for the last node2 (part of the previous missing edge)
        node1Neighbors.resize(X->size(), 0);//resizing the neighbors of node 1 to the number of nodes in the X network, initialing them to 0 (not adjacent not node1)
        node2Neighbors.resize(X->size(), 0);//resizing the neighbors of node 2 to the number of nodes in the X network, initialing them to 0 (not adjacent not 

        n1 =0; n2 =0, commonCount =0;

        //see if the nodes are connected to eachother in the origional graph
        for(int j =0; j < X->at(missing->at(i).node1).ListW.size(); j++)
        {
            if(X->at(missing->at(i).node1).ListW[j].first == missing->at(i).node2)
            {
                //cout <<"common path of 1 for "<<missing->at(i).node1 <<"-"<<missing->at(i).node2 <<endl;
                score += 0.05;//adding 0.05 to the score since both nodes are connected togeather in the origional graph
                break;
            }
        }
        //getting path of 2, which is the same as the common neighbors algorithm
        while(n1 != X->at(missing->at(i).node1).ListW.size() && n2 != X->at(missing->at(i).node2).ListW.size())
        {
            if(X->at(missing->at(i).node1).ListW[n1].first < X->at(missing->at(i).node2).ListW[n2].first){n1++;}
            else if(X->at(missing->at(i).node1).ListW[n1].first > X->at(missing->at(i).node2).ListW[n2].first){n2++;}
            else
            {
                commonCount++, n1++, n2++;
            }
            
        }
        //getting the neighbors of node 1
        for(int l =0; l < X->at(missing->at(i).node1).ListW.size(); l++)//node1's list
        {
            if(X->at(missing->at(i).node1).ListW[l].first != missing->at(i).node2)//if the neighbor is not node2
                node1Neighbors[X->at(missing->at(i).node1).ListW[l].first] =1;//using a bit vector to mark the neighbors of node1
        }
        //getting the neighbors of node 2
        for(int l =0; l < X->at(missing->at(i).node2).ListW.size(); l++)//node2's list
        {
            if(X->at(missing->at(i).node2).ListW[l].first != missing->at(i).node1)//if the neighbor is not node1
                node2Neighbors[X->at(missing->at(i).node2).ListW[l].first] =1;//using a bit vector to mark the neighbors of node2
        }
        //cout <<"path 2 is " <<commonCount << endl;
        score += pow(0.05, 2) * commonCount;
        //pathlength of 3
        score += pow(0.05, 3) * pathLength3(&node1Neighbors, &node2Neighbors, missing->at(i), X);
        score += pow(0.05, 4) * pathLength4(&node1Neighbors, &node2Neighbors, missing->at(i), X);
        index.first = score;
        edge = to_string(missing->at(i).node1) + " " + to_string(missing->at(i).node2);
        index.second = edge;
        predictedEdges.push_back(index);
    }
    //insertionSort(&predictedEdges);//sorting the scores using insertion sort
    quicksort(predictedEdges, 0, predictedEdges.size() -1);
}

//If a neighbor of node1 is adjacent to a neighbor of node2, then there is a pathlength of 3
//node1Neighbors and node2Neighbors are bit vectors
/*
    Here, when we find a neighbor of node1, we go through the neighbor's row in the adjacency list to see if
    there is an edge to a neighbor of node2: node2Neighbors->at(X->at(i).ListW[j].first) == 1 is refering to a neighbor
    of node 2 who is in the adjacency list for the neighbor of node 1.
*/ 
int pathLength3(vector<int> *node1Neighbors, vector<int> *node2Neighbors, Edge missing, A_Network *X)
{
    int count =0;//represents the number of paths that are length of 3
    vector<int> node1Copy, node2Copy;//used to store the neighbors of node1 and node2 that are adjacent of each other

    //case1, getting the paths between the missing edges
    for(int i =0; i < node1Neighbors->size(); i++)//looping through neighbor 1's bit vector
    {
        if(node1Neighbors->at(i) == 1)//if the neighbor exists for node1
        {
            //cout << i << endl;
            for(int j =0; j < X->at(i).ListW.size(); j++)//Going through list for the neighbor(at index i) of node1
            {   
                if(node2Neighbors->at(X->at(i).ListW[j].first) == 1 && X->at(i).ListW[j].first != missing.node2)//node2Neighbors->at(X->at(i).ListW[j].first)
                //refers to a neighbor of node2 that has an edge to the neighbor(at index i) of node1
                {
                    count++;
                    //adding the locations of the nodes with a common neighbor for the copy arrays, which will help in getting neighbors farther out
                    node1Copy.push_back(i);
                    //node2Copy.push_back(X->at(i).ListW[j].first);
                }
            }
        }  
    }
    //case2, if node1 and node2 have a edge between them, get all the neighbors of node2 (except for node1) and add them to the score. 
    //For example, if A and B are connected and B has a neighbor C, then A->B->C->B is a path length of 3
    //if(path1 == true){count += X->at(missing.node2).ListW.size()-1;}//add the total number of neighbors to node2 minus node1 to the number of paths that are length 3

    node1Neighbors->clear();//clearing all data in the bit vector
    node1Neighbors->resize(X->size(), 0);//resetting the node1Neighbors array
    int index;//used to get the value of the node on a path of 3 between node1 and node2

    /*
      Need to get the adjacent nodes of the neighbors from node1. Then all possible paths of 4 will be found.
      Duplicate nodes in a path may be possible since katz consideres all possible paths
    */
    for(int i =0; i < node1Copy.size(); i++)//going through the nodes adjacent to node1 that produced a path of 3 to node 2
    {
        index = node1Copy[i];
        for(int j =0; j < X->at(index).ListW.size(); j++)//going through the neighbors of the nodes that are neighbors of node1
        {
            if(X->at(index).ListW[j].first != missing.node1 && X->at(index).ListW[j].first != missing.node2)//if the node being marked is not node1 or node2
            {
                node1Neighbors->at(X->at(index).ListW[j].first) = 1;//adding the neighbor of an adjacent node to node1 as a marked node to be used for path of 4
            }
        }
    }

    //cout <<"path 3 is " << count << endl;
    return count;
}

//goes though each list of the neighbors of the adjacent neighbors for node 1. If the nodes are the same, path 4 exists. 
int pathLength4(vector<int> *node1Neighbors, vector<int> *node2Neighbors, Edge missing, A_Network *X)
{
    int count =0;//represents the number of paths that are length of 3
    vector<int> node1Copy, node2Copy;//used to store the neighbors of node1 and node2 that are adjacent of each other
    for(int i =0; i < node1Neighbors->size(); i++)//looping through neighbor 1's bit vector
    {
        if(node1Neighbors->at(i) == 1)//if the neighbor exists for node1
        {
            //cout << i << endl;
            for(int j =0; j < X->at(i).ListW.size(); j++)//Going through list for the neighbor(at index i) of node1
            {   
                if(node2Neighbors->at(X->at(i).ListW[j].first) == 1 && X->at(i).ListW[j].first != missing.node2)//node2Neighbors->at(X->at(i).ListW[j].first)
                //refers to a neighbor of node2 that has an edge to the neighbor(at index i) of node1
                {
                    count++;
                    //adding the locations of the nodes with a common neighbor for the copy arrays, which will help in getting neighbors farther out
                    //node1Copy.push_back(i);
                    //node2Copy.push_back(X->at(i).ListW[j].first);
                }
            }
        }  
    }
    //cout << "path length 4 " << count << endl;
    return count;
}
#endif