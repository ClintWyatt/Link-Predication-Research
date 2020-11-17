#ifndef RANDOMEDGE_HPP
#define RANDOMEDGE_HPP

using namespace std;

void random_edge(A_Network &X, A_Network &S, int size)
{
  Edge *allEdges;
  int numEdges = totalEdges(&X);
  int index, currentSize, row, node;
  int_double edge;
  allEdges = new Edge[numEdges*2];
  for(int i =0, index=0; i < X.size(); i++)
  {
    for(int j =0; j < X[i].ListW.size(); j++)
    {
      allEdges[index].node1 = i;
      allEdges[index].node2 = X[i].ListW[j].first;
      allEdges[index].edge_wt = X[i].ListW[j].second;
      index++;
    }
  }
  cout << endl;

  S.resize(X.size());
  setUpSample(S, X.size());

  vector<bool> bitVector;
  bitVector.resize(numEdges *2);
  bitVector.assign(numEdges *2, 0);
  currentSize =0;
  while(currentSize < size)
  {
    index = rand() % numEdges *2;
    if(bitVector[index] == 0)
    {
      row = allEdges[index].node1;
      edge.first = allEdges[index].node2;
      edge.second = allEdges[index].edge_wt;
      S[row].ListW.push_back(edge);
      currentSize++;
      bitVector[index] =1;
    }
  }

  //sort the edges in the 
  for(int i =0; i < S.size(); i++)
  {
    quicksort(S[i].ListW, 0, S[i].ListW.size() -1);
  }
  //free memory
  delete [] allEdges;
  //delete allEdges;
}

#endif