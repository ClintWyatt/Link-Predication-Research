#ifndef LCC_HPP
#define LCC_HPP
#include <queue>

int sameEdges(vector <int_double> &adj, int index, A_Network &S);

//number of edges between the neighbors divided by 2.
float local_clustering_score(A_Network & S)
{
    int commonNeighbors; //used to represent the total common neighbors between nodes on a row
    float totalScore = 0.0;
    /*
    queue <int> discoveredSet;
    queue <int> frontierQueue;
    float lcScore = 0.0;
    vector<bool> visited;
    vector<int_double> adj;
    visited.resize(S.size()); 
    int node;
    for(int i =0; i < S.size(); i++)
    {
        visited.assign(0, S.size());//assigning zeros to all elements in array
        frontierQueue.push(i);
        adj = S[i].ListW;
        while(!frontierQueue.empty())
        {
            node = frontierQueue.front();
        }

    }
    */
   vector<int_double> adj; //First get a copy of the of the row of the adjacency list. 
   //Second, go through each row of each node in the list and find nodes in the copy row. The common neighbors algorithm will work here.

    for(int i =0; i < S.size(); i++)
    {
        commonNeighbors = 0.0;
        adj = S[i].ListW;
        for(int j =0; j < S[i].ListW.size(); j++)
        {
            commonNeighbors += sameEdges(S[i].ListW, S[i].ListW[j].first, S);
        }
        //cout <<"number of common neighbors between nodes on row " << i <<": " << commonNeighbors <<endl;
        commonNeighbors = commonNeighbors*(commonNeighbors - 1.0)/2;
        //cout << "Row " <<i <<" score: " << commonNeighbors << endl;
        totalScore += commonNeighbors;
    }
    totalScore = totalScore/S.size();
    return totalScore;
}

//this method is similar to common neighbors
int sameEdges(vector <int_double> &adj, int index, A_Network &S)
{
    int i =0, l =0;//indexes for 
    int cn =0;//common neighbors
    while(i < S[index].ListW.size() && l < adj.size())
    {
        if(S[index].ListW[i].first < adj[l].first){i++;}
        else if(S[index].ListW[i].first > adj[l].first){l++;}
        else
        {
            cn += 1.0;
            i++;
            l++;
        }
    }
    return cn;
}
#endif