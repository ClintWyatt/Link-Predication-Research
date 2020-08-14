#ifndef MISSINGEDGES_HPP
#define MISSINGEDGES_HPP


void missingEdges(A_Network *X, A_Network *S, vector<Edge> *nonexist)
{

  bool found;
  vector<bool> visited;
  vector<float> scores;
  vector<int_int> D;
  string filename;
  Edge mye;

  //Tracks sample nodes that are visited
  visited.resize(X->size(), false);//initializing all nodes representing visited for network X to false. 

  //Visit nodes in sample network
  for (int i = 0; i < S->size(); i++)
  {
    //If node on sample has edges
    if(S->at(i).ListW.size() != 0)
    {
      visited.at(S->at(i).Row) = true;//set the row to true in the visited vector
    }
  }

  //Getting edges that dont exist in sample, but in the origional
  for(int i = 0; i < X->size(); i++)
  {
    //If the node isnt in sample, then add all edges to nonexistent 
    if(visited.at(S->at(i).Row) == false)//if there are no edges for the row in the S network
    {
      //Add all edges in the same row in the X network to nonexistent list
      for(int j = 0; j < X->at(i).ListW.size(); j++)
      {
        mye.node1 = X->at(i).Row;//pushing back the node with neighbors to the edge mye
        mye.node2 = X->at(i).ListW[j].first;
        mye.edge_wt = 0;
  
        nonexist->push_back(mye);//adding the edge to the vector of edges
      }
    }
    else //else check the sample node and add edges that are not in sample
    {
      //Check which nodes are in original but not in sample
      for(int k = 0; k < X->at(i).ListW.size(); k++)//this loop goes through the edges for the row in network x
      {
        found = false;
        for(int l = 0; l < S->at(i).ListW.size(); l++)//goes through the edges for the row in network s
        { 
          //node was found
          if(S->at(i).ListW[l].first == X->at(i).ListW[k].first)//j refers to the loop at line 553
          {
            found = true;
            break;
          }
        }
        //Add node that is missing from sample network
        if(found == false)
        {
          mye.node1 = X->at(i).Row;
          mye.node2 = X->at(i).ListW[k].first;
          mye.edge_wt = 0;

          nonexist->push_back(mye);//pushing back the edge to the vector of edges
        }
      }
    }
  }
}

void missingSample( A_Network *S, vector<Edge> *missing)
{
  Edge mye;//represents the edge to be added to the missing list
  bool found = false;
  for(int i=0; i < S->size(); i++)
  {
    for(int j =i+1; j <S->size(); j++)
    {
      for(int k =0; k < S->at(j).ListW.size(); k++)
      {
        if(S->at(j).ListW[k].first == i)
        {
          found = true;
          break;
        }
      }
      if(found == false)//if the edge between i and j was not found, add it to the missing edges array
      {
        mye.node1 = i;
        mye.node2 = j;
        missing->push_back(mye);
      }
      found = false;
    }
  }
}

#endif