#ifndef RANDOMEDGE_HPP
#define RANDOMEDGE_HPP

using namespace std;

void random_edge(A_Network &X, A_Network &S, int size)
{
  Edge *allEdges;
  int numEdges = _2xEdges(X);
  int index, currentSize, row, node;
  int_double edge;
  allEdges = new Edge[numEdges];//allocating memory for the edges
  for(int i =0, index=0; i < X.size(); i++)
  {
    for(int j =0; j < X[i].ListW.size(); j++)
    {
      allEdges[index].node1 = i; //adding the first edge
      allEdges[index].node2 = X[i].ListW[j].first;//adding the second node to the edge
      allEdges[index].edge_wt = X[i].ListW[j].second;//adding the edge weight
      index++;//going to the next index of the array
    }
  }

  S.clear();//clearing the sample graph
  S.resize(X.size());//resizing the sample graph to be the same as the original graphs size in terms of verticies
  setUpSample(S, X.size());//setting up the rows in the sample

  vector<bool> bitVector;//using a bit vector to mark which edges have been used
  bitVector.resize(numEdges);
  bitVector.assign(numEdges, 0);//assigning zeros to all indexes of the bt vector
  currentSize =0;//number of edges that have been selected
  while(currentSize < size)
  {
    index = rand() % numEdges;
    if(bitVector[index] == 0)
    {
      row = allEdges[index].node1;//getting the first edge
      edge.first = allEdges[index].node2;//setting the first edge
      edge.second = allEdges[index].edge_wt;//getting the weight of the node
      S[row].ListW.push_back(edge);//adding the edge to the sample graph
      currentSize++;//increment the current size
      bitVector[index] =1;//mark the index as selected
    }
  }
  //sort the edges in the 
  for(int i =0; i < S.size(); i++)
  {
    quicksort(S[i].ListW, 0, S[i].ListW.size() -1);//sort each row of the adjacency list
  }
  //free memory
  delete [] allEdges;

}

#endif