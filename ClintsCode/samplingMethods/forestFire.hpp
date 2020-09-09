#ifndef FORESTFIRE_HPP
#define FORESTFIRE_HPP

using namespace std;
void forest_fire(A_Network *S, A_Network *X, int k, vector<Edge> *missing)
{
  //Initialize random seed
  srand(time(NULL));

  int pf = 70, pb;
  int seed_node; 
  int rando, S_edges = 0;
  queue<int> nodeQueue;
  vector<bool> visited;//represents nodes that have been burned

  cout << "Running Forest Fire\n";

  //Initialize sample as empty network
  S->clear();
  S->resize(X->size());

  visited.clear();
  visited.resize(X->size());

  for(int i =0; i < X->size(); i++){visited[i] = false;}

  //Pick random seed node
  seed_node = rand() % S->size();
  //seed_node = 23;
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
      if (rando <= pf)//Burn link with probability of pf
      { 
        if(visited.at(X->at(seed_node).ListW[i].first) == false)//if node is not burned
        {
          nodeQueue.push(X->at(seed_node).ListW[i].first);//add burned node to the queue
          visited.at(X->at(seed_node).ListW[i].first) = true;//node is now burned
        }      
      }
      else//Add non-burned edge to sample
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
    seed_node = nodeQueue.front();//getting the front node of the burned nodes
    //if(seed_node == 23){cout <<"true"<<endl;}
  }
}

#endif