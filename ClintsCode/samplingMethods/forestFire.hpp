#ifndef FORESTFIRE_HPP
#define FORESTFIRE_HPP

using namespace std;
void forest_fire(A_Network *S, A_Network *X, int k, vector<Edge> *missing)
{
  //Initialize random seed
  srand(time(NULL));

  int pf = 80, pb;
  int seed_node; 
  int rando, S_edges = 0;
  queue<int> nodeQueue;
  vector<bool> visited;

  cout << "Running Forest Fire\n";

  //Initialize sample as empty network
  S->clear();
  S->resize(X->size());

  visited.clear();
  visited.resize(X->size(), false);

  //Pick random seed node
  seed_node = rand() % S->size();
    
  //Initial queue 
  nodeQueue.push(seed_node);
  visited.at(seed_node) = true;

  while(S_edges < k)
  {
    nodeQueue.pop();
    
    //Go through each edge on the node
    for(int i = 0; i < X->at(seed_node).ListW.size(); i++)
    {
      //Burn node: Add node to queue if link was burned
      rando = rand() % 100 + 1; //Random number
      if (rando <= pf)          //Burn link with probability of pf
      { 
        //Check if node has already burned links
        if(visited.at(X->at(seed_node).ListW[i].first) == false)
        {
          //Add node to queue
          nodeQueue.push(X->at(seed_node).ListW[i].first);
          //visit node
          visited.at(X->at(seed_node).ListW[i].first) = true;
        }      
      }
      else //Add non-burned edge to sample
      {
        S->at(seed_node).ListW.push_back(X->at(seed_node).ListW[i]);
        S->at(seed_node).Ops.push_back(0);
        S_edges++;
      }
    }

    if(nodeQueue.empty())
    {
      break;
    }
    seed_node = nodeQueue.front();
    
  }
}

#endif