#ifndef MISSINGEDGES_HPP
#define MISSINGEDGES_HPP

//represents the actual missing edges
void missingEdges(A_Network *X, A_Network *S, vector<Edge> *nonexist)
{
  int listwX, listwS;//indexes for the lists for x and s
  Edge mye; //represents the edge that is in the origional network but not the sample network
  for(int i =0; i < X->size(); i++)
  {
    listwX =0, listwS =0;
    if(S->at(i).ListW.size() > 0)
    {
      while(listwX < X->at(i).ListW.size() && listwS < S->at(i).ListW.size())//while both lists have not been looked through 
      {
        if(X->at(i).ListW[listwX].first >=i && X->at(i).ListW[listwX].first >S->at(i).ListW[listwS].first)//edge is not a duplicate and 
        //the node in sorted list for x is greater than the node in sample netwroks sorted list
        {
          mye.node1 = X->at(i).Row;
          mye.node2 = X->at(i).ListW[listwX].first;
          nonexist->push_back(mye);
          listwS++;
        }
        else if(X->at(i).ListW[listwX].first >=i && X->at(i).ListW[listwX].first < S->at(i).ListW[listwS].first)//edge is not a duplicate and 
        //the node in sorted list for S is greater than the node in x networks sorted list
        {
          mye.node1 = X->at(i).Row;
          mye.node2 = X->at(i).ListW[listwX].first;
          nonexist->push_back(mye);
          listwX++;
        }
        else//both are equal
        {
          listwX++;
          listwS++;
        }
       
      }
      //adding the rest of the nodes to the nonexistent array since the origional networks rows will always be >= to the sample networks rows
      while(listwX < X->at(i).ListW.size())
      {
        if(X->at(i).ListW[listwX].first >=i)//if the node has not been processed earlier (preventing duplicate edges)
        {
          mye.node1 = X->at(i).Row;
          mye.node2 = X->at(i).ListW[listwX].first;
          nonexist->push_back(mye);
        }
        listwX++;
      }
    }
    else//the s networks row is empty
    {
       while(listwX < X->at(i).ListW.size())
        {
          if(X->at(i).ListW[listwX].first >=i)//if the edge has not been processed earlier (preventing duplicate edges)
          {
            mye.node1 = X->at(i).Row;
            mye.node2 = X->at(i).ListW[listwX].first;
            nonexist->push_back(mye);
          }
          listwX++;
        }
    }
   
  }
}

//represents the predicted edges missing
void missingSample(A_Network *S, vector<Edge> *missing)
{
  Edge mye;//represents the edge to be added to the missing list
  bool found;//used to see if i is in the S networks' j row
  for(int i=0; i < S->size(); i++)
  {
    found = false;
    for(int j =i+1; j <S->size(); j++)//going through every node (row) below in the sample network
    {
      for(int k =0; k < S->at(j).ListW.size(); k++)//going through an individual row that is below 
      {
        if(S->at(j).ListW[k].first == i)//if the node in j's row of the S network is the same as i (an edge is between the node in the list for the sample's row and i)
        {
          found = true;
          break;//go to the next row since an edge exists between i and a node in the current row
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