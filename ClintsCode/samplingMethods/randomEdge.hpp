#ifndef RANDOMEDGE_HPP
#define RANDOMEDGE_HPP

using namespace std;
//Insertion sort with network
void sort_network(A_Network *S)
{
    ADJ_Bundle key;
    int j;
    for(int i = 1; i < S->size(); i++)
    {
        key = S->at(i);
        j = i - 1;

        //Moves key with lower number one position
        while(j >= 0 && S->at(j).Row > key.Row)
        {
            S->at(j + 1) = S->at(j);
            j = j - 1;
        }

        S->at(j + 1) = key;
    }

}

int total_edges(A_Network *X)
{
  int num_edges = 0;
  
  //Increments each edge in network
  for(int i = 0; i < X->size(); i++)
  {
    for(int j = 0; j < X->at(i).ListW.size(); j++)
    {
      num_edges++;
    }
  }

  //Divide by 2 for repeated edges
  return num_edges/2;
}

void random_edge(A_Network *S, A_Network *X, int k, vector<Edge> *missing)
{
  //Init random seed
  srand(time(NULL));
  S->clear();
  S->resize(X->size());
  int node, edge, edge_index, S_edges = 0, count = 0;
  vector<bool> visited;
  ADJ_Bundle my_bundle;
  int_double my_ListW;

  visited.clear();
  visited.resize(X->size(), false);
  cout << "Running Random Edge\n";

  //While sample network edge count is less than k egdes
  while (S_edges < k)
  {
    //Pick random node-edge pair
    node = rand() % X->size();//getting the random node row
    edge_index = rand() % X->at(node).ListW.size();//getting the random node index
    edge = X->at(node).ListW[edge_index].first;//getting the actual random node
    //Check if node has zero edges
    if (X->at(node).ListW.size() == 0)
    {
      continue;
    }
    //Check if edge was already added
    if (X->at(node).ListW[edge_index].second == -1)
    {
      cout << "REPEAT\n";
      continue;
    }

    //cout << "Random Edge: " << node << " " << edge << endl;

    //Mark edges on original network
    //X->at(node).ListW[edge_index].second = -1;
    //X->at(edge).ListW[node].second = -1;

    //If the node has not been in the sample yet, add the node to sample
    if (visited.at(node) == false)
    {
      //Create ListW
      my_ListW.first = edge;
      my_ListW.second = 0;

      //Create bundle
      my_bundle.Row = node;
      my_bundle.Ops.push_back(0);
      my_bundle.ListW.push_back(my_ListW);

      //Add bundle to sample network
      S->at(node).ListW.push_back(my_ListW);

      //Clear bundle
      my_bundle.clear();
      //Set node as visited
      visited.at(node) = true;
    }
    else //If node is in sample, add the edge directly
    {
      //Search for the node in sample graph
      for (int i = 0; i < S->size(); i++)
      {
        //Node is found
        if (S->at(i).Row == node)
        {
          //Create ListW
          my_ListW.first = edge;
          my_ListW.second = 0;

          //Add edge to sample network
          S->at(i).ListW.push_back(my_ListW);

          //Break out of for loop
          break;
        }
      }
    }

    //Now we add the opposite node-edge pair into sample network

    //If opposite node is not in sample, add node to sample
    if (visited.at(edge) == false)
    {
      //Create ListW
      my_ListW.first = node;
      my_ListW.second = 0;

      //Create bundle
      my_bundle.Row = edge;
      my_bundle.Ops.push_back(0);
      my_bundle.ListW.push_back(my_ListW);

      //Add bundle to sample
      S->push_back(my_bundle);

      //Clear bundle
      my_bundle.clear();
      //Set opposite node as visited
      visited.at(edge) = true;
    }
    else //If opposite node is in sample, add the edge directly
    {
      for (int i = 0; i < S->size(); i++)
      {
        //Node is found
        if (S->at(i).Row == edge)
        {
          //Create ListW
          my_ListW.first = node;
          my_ListW.second = 0;

          //Add opposite node to sample
          S->at(i).ListW.push_back(my_ListW);

          //Break out of for loop
          break;
        }
      }
    }
    sort_network(S);
    S_edges = total_edges(S);
    count++;
  }
  /*for (int i = 0; i < S->size(); i++)
  {
    cout << "Row: " << S->at(i).Row << endl;
    cout << "E: ";
    for (int j = 0; j < S->at(i).ListW.size(); j++)
    {
      cout << S->at(i).ListW[j].first << " ";
    }
    cout << endl;
  }*/
  missingEdges(X, S, missing);
}


#endif