#ifndef CRAWL_NETWORK_HPP
#define CRAWL_NETOWRK_HPP
using namespace std;

void crawl_network(A_Network *X, int k_dist)
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
    ofstream os("K_nodes.txt");
 
  
    //Clear nonexist vector
    nonexist->clear();
    
  
    //Initialize containers
    visited.clear();
    visited.resize(X->size(),false);
    visited_K.clear();
    visited_K.resize(X->size(),0);
    neighbors_K.clear();

    //Initialize current node
    qpush.first = a;
    qpush.second = k;
    q.push(qpush);
    visited[a]=true;;
 
    //Finds k-neighbors and finishes after exceeding k-distance
    //DO BFS for k_dist levels
    while(!q.empty())
    {
        //Stop adding edges to network once k_dist nodes are met
        if(k > k_dist)
        {
            break;
        }
      //get current node
      current = q.front().first;
      k = q.front().second;
      q.pop();
        
      //Puts neighbors of nodes
      for(int i = 0; i < X->at(current).ListW.size(); i++)
      {
        node = X->at(current).ListW[i].first;

      
        //Checks if its a deleted edge
        if(X->at(current).ListW[i].second != -1)
        {
            //Checks if the node has already been visited/queued
          if(!visited[node])
          {
            //If reached k-dist create non-existent edges
            //Adds edges to nonexistent list if node is at distance k_dist or below
            if(k+1 <= k_dist && a<node)
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
    /*for(int v=0;v<neighbors_K.size();v++)
    {
      int n1=neighbors_K[v];
      if(visited_K[n1]>0)
      {
        mye.node1=a;
        mye.node2=n1;
        mye.edge_wt=visited_K[n1];
        nonexist->push_back(mye);       
      }     
    }*/       
  return;
}

#endif