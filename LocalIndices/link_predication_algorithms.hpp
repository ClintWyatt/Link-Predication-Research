#ifndef LINK_PREDICATION_ALGORITHMS_HPP
#define LINK_PREDICATION_ALGORITHMS_HPP
#include "universal_func.hpp"
using namespace std;

float write_common_neighbours(A_Network *X, int node1, int node2, ofstream &output)
{
  //intersection
  //Check for deleted nodes (-1 weight)
  float common_count = 0.0;
  int c1 = 0, c2 = 0;
  
  //Compares Rows of node1 and node2 and adds to counter if similiar neighbor was found
  //We assume lists are in increasing node order
  output << "Common neighbors between " << X->at(node1).Row << " and " << X->at(node2).Row << ": ";
  while(c1 != X->at(node1).ListW.size() && c2 != X->at(node2).ListW.size()) //use for normal comparisons
  {
    int n1 = X->at(node1).ListW[c1].first;
    int n2 = X->at(node2).ListW[c2].first;
    
    //cout << "N1: " << n1 << " N2: " << n2 << endl;
    //Move c1 if the c2 address is bigger
    //Move c2 if c1 address is bigger
    //Move both and add to counter if they are same neighbor
    if(X->at(node1).ListW[c1].first < X->at(node2).ListW[c2].first)
    {
      c1++;
    }
    else if(X->at(node1).ListW[c1].first > X->at(node2).ListW[c2].first)
    {
      c2++;
    }
    else if(X->at(node1).ListW[c1].first == X->at(node2).ListW[c2].first)
    {
      output << X->at(node1).ListW[c1].first <<" -> ";
      c1++;
      c2++;
      common_count++;
      
      //cout << "C1: " << c1 << " C2: " << c2 << " CC: " << common_count << endl;
      //cout << "Node1 Neigh: " << n1 << " Node2 Neigh: " << n2 << endl;
      //cout << "Node1: " << node1 << " Node2: " << node2 << endl;
      
    }
    //}
    
  }
  output << endl;
  return common_count;
}

//method for non adjacent edges for the sample and origional graph (in realtion to a complete graph)
float Os_common_neighbours(A_Network *X, int node1, int node2)
{
  //intersection
  //Check for deleted nodes (-1 weight)
  float common_count = 0.0;
  int c1 = 0, c2 = 0;

  //Compares Rows of node1 and node2 and adds to counter if similiar neighbor was found
  //We assume lists are in increasing node order
  while(c1 != X->at(node1).missingSample_Origional.size() && c2 != X->at(node2).missingSample_Origional.size())
  {
    //int n1 = X->at(node1).ListW[c1].first;
    //int n2 = X->at(node2).ListW[c2].first;
    //cout << "N1: " << n1 << " N2: " << n2 << endl;
    //Move c1 if the c2 address is bigger
    //Move c2 if c1 address is bigger
    //Move both and add to counter if they are same neighbor
    if(X->at(node1).missingSample_Origional[c1].node2 < X->at(node2).missingSample_Origional[c2].node2)
    {
      c1++;
    }
    else if(X->at(node1).missingSample_Origional[c1].node2 > X->at(node2).missingSample_Origional[c2].node2)
    {
      c2++;
    }
    else if(X->at(node1).missingSample_Origional[c1].node2 == X->at(node2).missingSample_Origional[c2].node2)
    {
      c1++;
      c2++;
      common_count++;
      
    }
    
  }

  return common_count;


}

float sample_CN(A_Network *S, int node1, int node2)
{
  float common_count = 0.0;
  int c1 = 0, c2 = 0;

  while(c1 != S->at(node1).missingEdges.size() && c2 != S->at(node2).missingEdges.size())
  {
    //int n1 = X->at(node1).ListW[c1].first;
    //int n2 = X->at(node2).ListW[c2].first;
    //cout << "N1: " << n1 << " N2: " << n2 << endl;
    //Move c1 if the c2 address is bigger
    //Move c2 if c1 address is bigger
    //Move both and add to counter if they are same neighbor
    if(S->at(node1).missingEdges[c1].node2 < S->at(node2).missingEdges[c2].node2)
    {
      c1++;
    }
    else if(S->at(node1).missingEdges[c1].node2 > S->at(node2).missingEdges[c2].node2)
    {
      c2++;
    }
    else if(S->at(node1).missingEdges[c1].node2 == S->at(node2).missingEdges[c2].node2)
    {
      c1++;
      c2++;
      common_count++;
      
    }
  }
  return common_count;  

}

//Uses common neighbor divided by the degree(x) * degree(y) square rooted
//Degree is the size of ListW of that node
float salton_index(A_Network *X, int CN_score, int node1, int node2, vector<int_int> D)
{
  float salton;
  
  if(!is_zero((float)sqrt(D[node1].second * D[node2].second)))
  {
    salton = CN_score / (float)sqrt(D[node1].second * D[node2].second);
  }

  return (float)salton;
}

//Takes common_neighbours divided by the total neighbors
float jaccard_index(A_Network *X, int CN_score, int node1, int node2)
{
  int c1 = 0, c2 = 0;
  float jaccard = 0.0;
  
  //Adds node1 edges first
  jaccard += (float)X->at(node1).ListW.size();

  //Finds the union of the two nodes
  while(c1 != X->at(node1).ListW.size() && c2 != X->at(node2).ListW.size())
  {
    //Move c1 if the c2 address is bigger
    //Move c2 if c1 address is bigger
    //Move both and add to counter if they are same neighbor
    if(X->at(node1).ListW[c1].first < X->at(node2).ListW[c2].first)
    {
      c1++;
      jaccard++;
    }
    else if(X->at(node1).ListW[c1].first > X->at(node2).ListW[c2].first)
    {
      c2++;
      jaccard++;
    }
    else
    {
      c1++;
      c2++;
      jaccard++;
    }  
  }

  //Intersection divided by union
  if(!is_zero(jaccard))
  {
    jaccard = CN_score / jaccard;
  }

  return jaccard;
}

//Takes common_neighbour divided by the added degrees of both nodes
float sorensen_index(A_Network X, int CN_score, vector<int_int> D, int node1, int node2)
{
  int degree1 = D[node1].second;
  int degree2 = D[node2].second;
  float sorensen;

  if(!is_zero(degree1 + degree2))
  {
    sorensen = (2 * CN_score / (degree1 + degree2));
  }

  return sorensen;
}


//Hub Index
//Promoted takes the min degree to divide
//Depressed takes the max geree to divide
float hub_index(A_Network X, int CN_score, vector<int_int> D, int node1, int node2, int mode)
{
  int degree;
  float hub;

  //Case 0 = Promoted, Case 1 = Depressed
  switch(mode)
  {
    case 0:
      degree = min(D[node1].second, D[node2].second);
      break;
    case 1:
      degree = max(D[node1].second, D[node2].second);
      break;
    default:
      break;
  }

  //common set divided by degree
  //float point exeception
  if(!is_zero((float)degree))
  {
    hub = CN_score / (float)degree;
  }

  return hub;

}


//Takes degree of both nodes and multiples degrees
//this represents the probability that new link "x" and "y" is proportional to degree(x) * degree(y)
float preferential_attachment_index(A_Network X, vector<int_int> D, int node1, int node2)
{
  float PA = (float)D[node1].second * (float)D[node2].second;

  return PA;
}
//Take node1(x) and node2(y) and scores by cardinality of the same neigbors
float common_neighbours(A_Network *X, int node1, int node2)
{
  //intersection
  //Check for deleted nodes (-1 weight)
  float common_count = 0.0;
  int c1 = 0, c2 = 0;
  
  //Compares Rows of node1 and node2 and adds to counter if similiar neighbor was found
  //We assume lists are in increasing node order

  while(c1 != X->at(node1).ListW.size() && c2 != X->at(node2).ListW.size()) //use for normal comparisons
  {
    int n1 = X->at(node1).ListW[c1].first;
    int n2 = X->at(node2).ListW[c2].first;
    
    //cout << "N1: " << n1 << " N2: " << n2 << endl;
    //Move c1 if the c2 address is bigger
    //Move c2 if c1 address is bigger
    //Move both and add to counter if they are same neighbor
    if(X->at(node1).ListW[c1].first < X->at(node2).ListW[c2].first)
    {
      c1++;
    }
    else if(X->at(node1).ListW[c1].first > X->at(node2).ListW[c2].first)
    {
      c2++;
    }
    else if(X->at(node1).ListW[c1].first == X->at(node2).ListW[c2].first)
    {
     
      c1++;
      c2++;
      common_count++;
      
      //cout << "C1: " << c1 << " C2: " << c2 << " CC: " << common_count << endl;
      //cout << "Node1 Neigh: " << n1 << " Node2 Neigh: " << n2 << endl;
      //cout << "Node1: " << node1 << " Node2: " << node2 << endl;
      
    }
    //}
    
  }
  
  return common_count;
}

//Finds the common neighbor of both nodes and sums the inverse of the log(degree)
float adamic_adar_index(A_Network *X, vector<int_int> D, int node1, int node2)
{
  vector<int> neighbor;
  float AA = 0;
  int c1 = 0, c2 = 0;
  //Same common neighbor intersect but add it to nodes and then also keep track of the sum
  //First find the intersceting nieghbors
  while(c1 != X->at(node1).ListW.size() && c2 != X->at(node2).ListW.size())
  {
    if(X->at(node1).ListW[c1].first < X->at(node2).ListW[c2].first)
    {
      c1++;
    }
    else if(X->at(node1).ListW[c1].first > X->at(node2).ListW[c2].first)
    {
      c2++;
    }
    else if(X->at(node1).ListW[c1].first == X->at(node2).ListW[c2].first)
    {
      neighbor.push_back(X->at(node1).ListW[c1].first);
      c1++;
      c2++;
      //cout << "node1 " << node1 << " node2 " << node2 << endl;
      //cout << "found neigh: " << X[node1].ListW[c1].first << " " << c1 << " " << c2 <<endl;
    }
  }
  //Second add the summation of 1/log(degree(z)) of each intersectiing nodes
  for(int i = 0; i < neighbor.size(); i++)
  {
    if(!is_zero((float)log(D[neighbor[i]].second)))//D.second means the size of ListW of X's row
    {
      AA += (1/(float)log(D[neighbor[i]].second));
    }
  }
  //cout << "Score found " << AA << endl;*/
  return AA;
}

//method for non adjacent edges for the sample and origional graph (in realtion to a complete graph)
float os_adamic_adar_index(A_Network *X, vector<int_int> D, int node1, int node2)
{ 
  vector<int> neighbor;
  float AA = 0;
  int c1 = 0, c2 = 0;

  //Same common neighbor intersect but add it to nodes and then also keep track of the sum
  //First find the intersceting nieghbors
  while(c1 != X->at(node1).missingSample_Origional.size() && c2 != X->at(node2).missingSample_Origional.size())
  //while(c1 != X->at(node1).ListW.size() && c2 != X->at(node2).ListW.size()) //use for normal comparisons
  {
    
    if(X->at(node1).missingSample_Origional[c1].node2 < X->at(node2).missingSample_Origional[c2].node2)
    {
      c1++;
    }
    else if(X->at(node1).missingSample_Origional[c1].node2 > X->at(node2).missingSample_Origional[c2].node2)
    {
      c2++;
    }
    else if(X->at(node1).missingSample_Origional[c1].node2 == X->at(node2).missingSample_Origional[c2].node2)
    {
      neighbor.push_back(X->at(node1).missingSample_Origional[c1].node2);
      c1++;
      c2++; 
    }
  }
//Second add the summation of 1/log(degree(z)) of each intersectiing nodes
  for(int i = 0; i < neighbor.size(); i++)
  {
    if(!is_zero((float)log(D[neighbor[i]].second)))
    {
      AA += (1/(float)log(D[neighbor[i]].second));
    }
  }
  //cout << "Score found " << AA << endl;*/
  return AA;
}

float sample_adamic_adar_index(A_Network *S, vector<int_int> D, int node1, int node2)
{ 
  vector<int> neighbor;
  float AA = 0;
  int c1 = 0, c2 = 0;

  //Same common neighbor intersect but add it to nodes and then also keep track of the sum
  //First find the intersceting nieghbors
  while(c1 != S->at(node1).missingEdges.size() && c2 != S->at(node2).missingEdges.size())
  //while(c1 != X->at(node1).ListW.size() && c2 != X->at(node2).ListW.size()) //use for normal comparisons
  {
    
    if(S->at(node1).missingEdges[c1].node2 < S->at(node2).missingEdges[c2].node2)
    {
      c1++;
    }
    else if(S->at(node1).missingEdges[c1].node2 > S->at(node2).missingEdges[c2].node2)
    {
      c2++;
    }
    else if(S->at(node1).missingEdges[c1].node2 == S->at(node2).missingEdges[c2].node2)
    {
      neighbor.push_back(S->at(node1).missingEdges[c1].node2);
      c1++;
      c2++; 
    }
  }
//Second add the summation of 1/log(degree(z)) of each intersectiing nodes
  for(int i = 0; i < neighbor.size(); i++)
  {
    if(!is_zero((float)log(D[neighbor[i]].second)))
    {
      AA += (1/(float)log(D[neighbor[i]].second));
    }
  }
  //cout << "Score found " << AA << endl;*/
  return AA;
}


//Finds the common neighbor of both nodes and sums the inverse of the degree
float resource_allocation_index(A_Network *X, vector<int_int> D, int node1, int node2)
{
  vector<int> neighbor;
  float RA = 0;

  //First find the intersceting nieghbors
  for(int i = 0; i < X->at(node1).ListW.size(); i++)
  {
    for(int j = 0; j < X->at(node2).ListW.size(); j++)
    {
      if(X->at(node1).ListW[i].second == -1 && X->at(node1).ListW[i].first == X->at(node2).ListW[j].first)
      {
        neighbor.push_back(X->at(node1).ListW[i].first);
      }
    }
  }

  //Second add the summation of 1/degree(z) of each intersectiing nodes
  for(int i = 0; i < neighbor.size(); i++)
  {
    if(!is_zero((float)D[neighbor[i]].second))
    {
      RA += (1/(float)D[neighbor[i]].second);
    }
  }

  return RA;
}

//Global Indice Katz
//beta = damping factor
//l = max length of path connecting node1 and node2
float katz(A_Network *X, float beta, int l, int node1, int node2)
{
  int current_l = 0, previous_l; //Tracks length of path
  int current_node; //Current node from the queue
  float score = 0; //Score of Katz index
  float paths = 0; //Number of paths found

  //First = node in queue
  //Second = length of node from node1
  queue<int_int> nodeQueue; //node queue for BFS searching
  int_int q_node;

  //Initialize queue and current node
  q_node.first = node1;
  q_node.second = 0;
  nodeQueue.push(q_node);
  current_node = node1;

 // cout << "Two nodes testing: " << node1 << " " << node2 << endl;

  //Loops until length l is reached
  while(current_l <= l)
  { 
    //Pop queue
    nodeQueue.pop();

    for(int i = 0; i < X->at(current_node).ListW.size(); i++)
    {
      //Check if a path was found
      if(X->at(current_node).ListW[i].first == node2)
      {
        paths++;
       //cout << "Path was found " << X->at(current_node).ListW[i].first << " " << node2 << endl;
      }
      else //Else put the node into the queue
      {
        q_node.first = X->at(current_node).ListW[i].first;
        q_node.second = current_l + 1;
        nodeQueue.push(q_node);
        //cout << "Q node length " << q_node.second << endl;
      }
    }

    //Set next current node and current length
    current_node = nodeQueue.front().first;
    previous_l = current_l; //Check for summation 
    current_l = nodeQueue.front().second;

    //Reset number of paths found if the current legnth is changed and add score for that length
    if(current_l != previous_l)
    {
      score += (pow(beta, current_l) * paths);
      //cout << (pow(beta, current_l) * paths) << " " << paths << " "; 
      paths = 0;
      //cout << "Score is " << score << endl;
    }
    //cout << "Current L " << current_l << endl;
  }
  return score; 
}

#endif
