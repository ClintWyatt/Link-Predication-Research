#ifndef KATZ_HPP
#define KATZ_HPP

using namespace std;

//use vector<int> * commonNeighbors as one of the arguments if the common neigbbors for path length of 2 need to not be checked
//If a neighbor of node1 is adjacent to a neighbor of node2, then there is a pathlength of 3
int pathLength3(vector<int> *node1Neighbors, vector<int> *node2Neighbors, Edge missing, A_Network *X)
{
    int count =0;//represents the number of paths that are length of 3
    vector<int> node1Copy, node2Copy;//used to store the neighbors of node1 and node2 that are adjacent of each other
    for(int i =0; i < node1Neighbors->size(); i++)//looping through neighbor 1's bit vector
    {
        if(node1Neighbors->at(i) == 1)//if the neighbor exists for node1
        {
            //cout << i << endl;
            for(int j =0; j < X->at(i).ListW.size(); j++)//Going through the adjacent nodes of the neighbor node for node1
            {   
                if(node2Neighbors->at(X->at(i).ListW[j].first) == 1 && X->at(i).ListW[j].first != missing.node2)//if a neighbor of node 2 is adjacent to a neighbor of node1
                //(the neighbor from node2 is in the list of the neighbor from node1) and the node being checked is not node 2
                {
                    count++;
                    //adding the locations of the nodes with a common neighbor for the copy arrays, which will help in getting neighbors farther out
                    node1Copy.push_back(i);
                    node2Copy.push_back(X->at(i).ListW[j].first);
                }
            }
        }  
    }
    node1Neighbors->clear();//clearing all data in the bit vector
    node1Neighbors->resize(X->size(), 0);//resetting the node1Neighbors array
    int index;//used to get the value of the node on a path of 3 between node1 and node2

    /*
      Need to get the neighbors of the neighbors from node1. Then all possible paths of 4 will be found.
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

//not finsihed yet, but the logic will be similar to a path of 3
int pathLength4(vector<int> *node1Neighbors, vector<int> *node2Neighbors, Edge missing, A_Network *X)
{
    int score =0;

    return score;
}

void katz(A_Network *X, vector<Edge> *missing, string alg)
{
    vector<int> node1Neighbors;//represents nodes that are on a path for node1. Gets updated every time we go a path futher (n + 1).
    vector<int> node2Neighbors;//represents the nodes that are adjacent to node2. Used for path of 3
    float score;//represetns the score for the missing edges
    vector<float>scores;
    int n1, n2, commonCount;//n1 and n2 are indexes in the lists of node1 and node2 of the missing edge. Commoncount represents the number of paths for lengths of 1, 2, and 3.
    ofstream katzResults("results/"+alg+"katz.txt");
    ofstream katzPredicated("results/predicated/"+alg+"katz.txt");
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
                //cout <<"common path of 1 is 1"<<endl;
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
        for(int j =2; j < 4; j++)
        {
            if(j == 2)//path of 3
            {
                score += pow(0.05, j+1) * pathLength3(&node1Neighbors, &node2Neighbors, missing->at(i), X);
            }
            /* use the else statement below if a path of 4 is required
            else
            {
                score += pow(0.05, j+1) * pathLength4(&node1Neighbors, &node2Neighbors, missing->at(i), X);
            }
            */
        }
        //cout << score << endl;
        scores.push_back(score);
    }
    insertionSort(&scores);//sorting the scores using insertion sort

    for(int i =scores.size()-1; i > -1; i--)
    {
        if(scores[i] >= 0.5)//threshold based off the aves-wildbird file
        {
            katzPredicated << scores[i] << endl;
        }
        katzResults << scores[i]<<endl;
    }
    katzResults.close();
}
#endif