#ifndef UNIVERSAL_FUNC_HPP
#define UNIVERSAL_FUNC_HPP

#include"structure_defs.hpp"

using namespace std;
//Functions used through program


//Add opposite edges to network
//Used for adding oppsite edges to sample networks
//Assume that whole network is initalized
void add_opposite_edge(A_Network *S)
{
  int op_node;
  int_double list;
  bool already_entered;

  //Go through whole network
  for(int i = 0; i < S->size(); i++)
  {
    
    //Go through each neihgbor
    for(int j = 0; j < S->at(i).ListW.size(); j++)
    {
      already_entered = false;
      op_node = S->at(i).ListW[j].first;
      
      //Check if the opposite node was already entered
      for(int k = 0; k < S->at(op_node).ListW.size(); k++)
      {
        if(S->at(op_node).ListW[k].first == S->at(i).ListW[j].first)
        {
          already_entered = true;
          break;
        }
      }

      //Added opposite node if it was not already entered
      if(!already_entered)
      {
        list.first = S->at(i).Row;
        list.second = 0;

        //cout << "Add " << list.first << " to op_node " << op_node << endl;

        //Add edge to opposite node
        S->at(op_node).ListW.push_back(list);
        S->at(op_node).Ops.push_back(0);
      }
    }
  }
}


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

void write_network(A_Network *X, string fileName)
{
  ofstream output(fileName);//preparing to write to the user defined file

  for(int i =0; i < X->size(); i++)
  {
    output << X->at(i).Row << ": ";
    for(int j =0; j < X->at(i).ListW.size(); j++)
    {
      output << X->at(i).ListW[j].first << " ";
    }
    output <<endl;
  }

  output.close();
}

//Prints all edges
void print_edges(vector<Edge> edges)
{
  cout << "Nonexistent edges: \n";
  for(int i = 0; i < edges.size(); i++)
  {
    cout << "(" << edges[i].node1 << ", " << edges[i].node2 << ")" << endl;
  }
}

void print_missingEdges(A_Network *X)
{
  for(int i =0; i < X->size(); i++)
  {
    cout << "Row " << X->at(i).missingEdges[0].node1 <<": ";
    for(int j =0; j < X->at(i).missingEdges.size(); j++)
    {
      cout << X->at(i).missingEdges[j].node2 << " ";
    }
    cout << endl;
  }
}

//Checks if selected edge was already selected
bool check_edge(vector<Edge> edges, int row, int col)
{
  for(int i = 0; i < edges.size(); i++)
  {
    if(edges[i].node1 == row && edges[i].node2 == col)
    {
      return true;
    }
  }
  return false;
}

//Check if node b is in a
bool check_List(vector<int_double> list, int b)
{
  for(int i = 0; i < list.size(); i++)
  {
    if(list[i].first == b && list[i].second != -1)
    {
      return true;
    }
  }
  return false;
}

//Zero check for division
bool is_zero(float num)
{
  if(num == 0.0 || num == 0)
  {
    return true;
  }

  return false;
}

int sameEdge(vector<int_double> sample, vector<int_double> origional)
{
  int _edges = 0;
  for(int l = 0; l < origional.size(); l++)
  {

    for(int j =0; j < sample.size(); j++)
    {
      if(origional[l].first == sample[j].first)
      {
        _edges++;
        break;
      }
    }
  }
  return _edges;

}


void edgeComparison(A_Network *S, A_Network *X)
{
  
  int sameEdges = 0;
  for(int i =0; i < X->size(); i++)
  {
    
    for(int j =0; j < S->size(); j++)
    {
      if(S->at(j).Row == X->at(i).Row)//if both networks contain the same node
      {
        sameEdges += sameEdge(S->at(j).ListW, X->at(i).ListW);
      }
      else if(S->at(j).Row > X->at(i).Row)//if the row has already been processed or does not exist
      {
        break;//break from the inside for loop
      }
    }
  }
  cout <<"Number of similar edges: " << sameEdges/2 << endl;
}

//method is used for edges in the sampled network and origional network; in relation to a complete graph
void nonAdjacent(A_Network *S, A_Network *X)
{
  Edge mye; 
  for(int i =0; i < X->size(); i++)//looping through network X, which is the same size as network S in terms of rows
  {
     X->at(i).missingSample_Origional.clear();//doing this to clear the last time a sampling algorithm was used
     //cout << X->at(i).missingEdges.size() << " ";
     //cout << S->at(i).missingEdges.size() << endl;
    for(int j =0; j < X->at(i).missingEdges.size(); j++)//j represents the index of the missing edges of network x
    {
      for(int k =j; k < S->at(i).missingEdges.size(); k++)//k represents the index of missing edges of network s
      {
        if(X->at(i).missingEdges[j].node2 == S->at(i).missingEdges[k].node2)//if both networks have the same missing edge
        {
          
          mye.node1 = S->at(i).missingEdges[j].node1;
          mye.node2 = S->at(i).missingEdges[j].node2;
          X->at(i).missingSample_Origional.push_back(mye);//adding the edge to the edge vector representing missing form both sample and origional
          break;
        }
      }
    }
  }
}

//method is used for putting edges that dont exist into A_Netwrok X (could be sample or origional graph)
void completeGraph(A_Network *X)
{
  //cout <<"In method" << endl;
  Edge mye;//represents the edge that does not exist in the origional network
  vector<int> found;//represents edges for each node in the row of the adjacency list
  for(int i =0; i < X->size(); i++)
  {
    X->at(i).missingEdges.clear();//doing this to have differnt missing edges for different sampling algorithms
    //cout << X->at(i).missingEdges.size() << " ";
    for(int j =0; j < X->at(i).ListW.size(); j++)//find the edges in the ith row
    {
      if(X->at(i).ListW.size() !=0)
      {
        //cout << X->at(i).ListW[j].first << " ";
        found.push_back(X->at(i).ListW[j].first);//pushing the adjecent nodes to the found vector
      }
    }
    for(int k =0, index =0; k < X->size(); k++)//looping through the network to see if there is a row that is not 
    {
      if(index < X->at(i).ListW.size())//if there are any more connected edges in the row
      {
        if(X->at(k).Row != X->at(i).Row)//the node is not a self loop
        {
          if(X->at(k).Row != found[index])// the node was not previously a edge to the row
          {
            mye.node1 = X->at(i).Row;
            mye.node2 = X->at(k).Row;
            mye.edge_wt =0;
            X->at(i).missingEdges.push_back(mye);
            //X->at(i).missingEdges.push_back(X->at(k).Row);//adding another row as the missing edge
          }
          else//node is a edge to the row
          {
            index++;
          }
        }
      }
      else//there are no more edges in the row
      {
        if(X->at(k).Row != X->at(i).Row)//the node is not a self loop 
        {
          mye.node1 = X->at(i).Row;
          mye.node2 = X->at(k).Row;
          mye.edge_wt = 0;
          X->at(i).missingEdges.push_back(mye);//adding another row as the missing edge
        }
      }
    }
    found.clear();
  }
}

void printGraph(A_Network *X)
{
  
  for(int i =0; i < X->size(); i++)
  {
    cout << X->at(i).Row <<": ";
    for(int j =0; j < X->at(i).ListW.size(); j++)
    {
      cout << X->at(i).ListW[j].first << " ";
    }
    cout << endl;
  }

}

//prints missing edges from the origional and sample network
void missing_orig_sample(A_Network *X)
{
  for(int i =0; i < X->size(); i++)
  {
    cout <<"Row " <<X->at(i).missingSample_Origional[0].node1 << ": ";
    for(int j =0; j < X->at(i).missingSample_Origional.size(); j++)
    {
      //cout <<"("<<X->at(i).missingSample_Origional[j].node1 <<"," <<X->at(i).missingSample_Origional[j].node2 <<")" << " ";
      cout << X->at(i).missingSample_Origional[j].node2 << " ";
    }
    cout << endl;
  }
  
}

//Used to get unique edges in a network when compared to another network. 
//For instance, this method is used when we want edges that are in the origional network, but not the sampled (vice versa as well). 
void minusIntersection(A_Network *S, A_Network *X)
{
  int_double de; //represents a edge
  bool found = false;
  for(int i =0; i < X->size(); i++)
  {
    
    for(int j =0; j < X->at(i).ListW.size(); j++)
    {
      found = false;
      if(S->at(i).ListW.size() > 0)//case that the sample graph has at least 1 node in the row
      {
        for(int k =0; k < S->at(i).ListW.size(); k++)
        {
          if(X->at(i).ListW[j].first == S->at(i).ListW[k].first)//if there is a match
          {
            found = true;
            break;
          }
        }
        if(found == false)//if there is no match between the networks
        {
          de.first = X->at(i).ListW[j].first;
          de.second = X->at(i).ListW[j].second;
          X->at(i).unique.push_back(de);//adding the edge to the unique vector
        }
      }
      else
      {
        //cout << "Row " << X->at(i).Row << ": " << X->at(i).ListW.size() << " \t";
        for(int l =0; l < X->at(i).ListW.size(); l++)
        {
          de.first = X->at(i).ListW[l].first;
          de.second = X->at(i).ListW[l].second;
          X->at(i).unique.push_back(de);
        }
        break;
      }
    }
  }

}



void printUnique(A_Network *X)
{

  for(int i =0; i < X->size(); i++)
  {
    cout << X->at(i).Row <<": ";
    for(int j =0; j < X->at(i).unique.size(); j++)
    {
      cout << X->at(i).unique[j].first << " ";
    }
    cout <<endl;
  }

}

#endif
