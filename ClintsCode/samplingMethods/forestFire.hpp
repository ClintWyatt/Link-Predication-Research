#ifndef FORESTFIRE_HPP
#define FORESTFIRE_HPP

using namespace std;
void forest_fire(A_Network &S, A_Network &X)
{
  //Initialize randNumm seed
  srand(time(NULL));

  int pf = 75, pb;
  int seed_node; 
  int randNum, sampleEdges = 0;
  queue<int> burnedQueue;//represents the burned nodes in the origionla graph
  vector<bool> burned;//represents nodes that have been burned

  //Initialize sample as empty network
  S.clear();
  S.resize(X.size());

  burned.clear();
  burned.resize(X.size());

  for(int i =0; i < X.size(); i++){burned[i] = false;}

  setUpSample(S, X.size());
  //Pick randNumm seed node
  seed_node = rand() % S.size();
  
  burnedQueue.push(seed_node);
  burned.at(seed_node) = true;

  //sampleEdges will likely never get to the number of edges (k) 
  while(!burnedQueue.empty()){
  //do{
    burnedQueue.pop();//remove the front of the burnedQueue
    
    //Go through each neighbor of the seed_node. 
    for(int i = 0; i < X.at(seed_node).ListW.size(); i++)//going through all the neighbors of the burned node
    {
      randNum = rand() % 100 + 1; //generating a randNumm number
      if (randNum <= pf)//If randNum is less than pf, then try to burn an edge of the seed_node
      { 
        if(burned.at(X.at(seed_node).ListW[i].first) == false)//if node is not burned
        {
          burnedQueue.push(X.at(seed_node).ListW[i].first);//add burned node to the queue
          burned.at(X.at(seed_node).ListW[i].first) = true;//node is now burned
        }      
      }
      else//Add non-burned edge to the sample graph
      {
        S.at(seed_node).ListW.push_back(X.at(seed_node).ListW[i]);//add the seed node's unburned neighbor to the sample graph
        S.at(seed_node).Ops.push_back(0);
        sampleEdges++;//increment the number of sample edges
      }
    }

    if(burnedQueue.empty())//if the queue is empty, end this algorithm
    {
      break;
    }
    seed_node = burnedQueue.front();//getting the next burned node
  }//while(!burnedQueue.empty());
}

#endif