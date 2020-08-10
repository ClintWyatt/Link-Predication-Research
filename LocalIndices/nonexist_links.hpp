#ifndef NONEXIST_LINKS_HPP
#define NONEXIST_LINKS_HPP
//#include "get_scores.hpp"
#include "link_predication_algorithms.hpp"
#include "unary_set_operations.hpp"

using namespace std;

//Gets K-distance nonexistent nodes for node a using BFS
//K = 2
void find_k_dist_nonedge(A_Network *X, vector<Edge> *nonexist, int k_dist)
{
  //first = node
  //second = k-dist
  queue<int_int> q;
  vector<bool> visited; //whether a nodes is visited, as per BFS rules
  vector<int> visited_K; //visited at distance k_dist; keeps track of number of times node is visited
  vector<int> neighbors_K; //list of neighbors at distance K_dist
  int k = 0;
  int current, node;
  int_int qpush;
  Edge mye;
  
  /*  visited.resize(X->size(),false);
    visited_K.resize(X->size(),0);
    neighbors_K.clear();*/
  
  //Clear nonexist vector
  nonexist->clear();
    
  //For all vertices
  for(int a = 0; a < X->size(); a++)
  {
    //Initialize containers
    visited.clear();
    visited.resize(X->size(),false);
    visited_K.clear();
    visited_K.resize(X->size(),0);
    neighbors_K.clear();
      
    //Reset k for next node
    k = 0; 
    //Initialize current node
    qpush.first = a;
    qpush.second = k;
    q.push(qpush);
    visited[a]=true;;
 
    //Finds k-neighbors and finishes after exceeding k-distance
    //DO BFS for k_dist levels
    while(!q.empty())
    {
      //get current node
      current = q.front().first;
      k = q.front().second;
      q.pop();
        
      //Puts neighbors of nodes
      for(int i = 0; i < X->at(current).ListW.size(); i++)
      {
        node = X->at(current).ListW[i].first;

        //if(node < a){continue;}
        //Checks if its a deleted edge
        if(X->at(current).ListW[i].second != -1)
        {
            //if(a==49)
            //{cout << a<< "::"<< current<<"::"<<node <<"::"<< visited[node]<<"::"<<visited_K[node]<<"\n";}
            //Checks if the node has already been visited/queued
          if(!visited[node])
          {
            //If reached k-dist create non-existent edges
            //Adds edges to nonexistent list if node is at distance k_dist
            if(k+1 == k_dist && a<node)
            {
                visited_K[node]++;
                if(visited_K[node]==1) //only push in the first time
                {neighbors_K.push_back(node);}
            }
            else //push to q
            {
              qpush.first = node;
              qpush.second = k+1;
              q.push(qpush);
              visited[node]=true;
            }//end of else  
          }//end of if visited
        }//end of if not deleted edge
      }//end of for--going through neighbors   
    }//end of while

//Dont need to pop since q is empty
     
    //For all vertices add to heap
    for(int v=0;v<neighbors_K.size();v++)
    {
      int n1=neighbors_K[v];
      if(visited_K[n1]>0)
      {
        mye.node1=a;
        mye.node2=n1;
        mye.edge_wt=visited_K[n1];
 //       cout << a << " " << " " << n1 << " " << visited_K[n1] << endl;
        nonexist->push_back(mye);
              
      }
          
    }       
  }//end of for all vertices

  make_heap(nonexist->begin(), nonexist->end(), inc_wt);
  /*for(int i = 0; i < nonexist->size(); i++)
  {
    cout << nonexist->at(i).node1 << " " << nonexist->at(i).node2 << " " << nonexist->at(i).edge_wt << endl;
  }*/
  //print_edges(*nonexist);
  //cout << "Number of Nonexist nodes found: " << nonexist->size() << endl;
  return;
}
/* End of Function */

#endif
