#ifndef DETACH_EDGES_HPP
#define DETACH_EDGES_HPP

using namespace std;

//Find total number of Edges
int total_edges_degree(A_Network *X, vector<int_int> *D)
{
  int num_edges = 0;
  int_int de;
  //Increments each edge in network
  for(int i = 0; i < X->size(); i++)
  {
    for(int j = 0; j < X->at(i).ListW.size(); j++)
    {
      num_edges++;
    }
    de.first = i;
    de.second = X->at(i).ListW.size();
    //Gets degree of each node
    D->push_back(de);
  }

  //Divide by 2 for repeated edges
  return num_edges/2;
}

int total_edges_unique(A_Network *X, vector<int_int> *D)
{
  int num_edges = 0;
  int_int de;
  for(int i =0; i < X->size(); i++)
  {
    for(int j =0; j < X->at(i).unique.size(); j++)
    {
      num_edges++;
    }
    de.first = i;
    de.second = X->at(i).unique.size();
    D->push_back(de);
  }
  return num_edges/2;
}

//used for edges in the sample and original network that are not in the complete graph. 
int os_total_edges_degree(A_Network *X, vector<int_int> *D)
{
  int num_edges =0;
  int_int de;
  for(int i =0; i < X->size(); i++)
  {
    for(int j =0; j < X->at(i).missingSample_Origional.size(); j++)
    {
      num_edges++;
    }
    de.first = i;
    de.second = X->at(i).missingSample_Origional.size();
    D->push_back(de);
  }
  return num_edges/2;
}

int sample_edges_degree(A_Network *S, vector<int_int> *D)
{
  int num_edges =0;
  int_int de;
  for(int i =0; i < S->size(); i++)
  {
    for(int j =0; j < S->at(i).missingEdges.size(); j++)
    {
      num_edges++;
    }
    de.first = i;
    de.second = S->at(i).missingEdges.size();
    D->push_back(de);
  }
  return num_edges/2;
}

//Find total number of Edges
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

//Detaches 10 percent of nodes from network
void detach_edges(A_Network *X, vector<int_int> *D,  vector<Edge> *real_edges, int p)
{
  int rand_row, rand_col, rand_col_addr, ops;
  Edge myEdge;
  
  D->clear();
  int total = total_edges_degree(X, D);

  //10 percent of edges
  double perc=double(p)/100.00;
  cout << perc <<"\n";
  int num_detached = ceil(double(total*perc));
  srand(time(0));

  cout << "Network edges: " << total << " Num_detached: " << num_detached << endl;

  //Always clear a vector before using it::::SB
  real_edges->clear();
  
  for(int i = 0; i < num_detached; i++)
  {
    //Pick random edge to delete
    rand_row = rand() % X->size();
     //Check for nodes with 0 degree
    if(X->at(rand_row).ListW.size() == 0)
    {
      i--;
      continue;
    }
      
      
    rand_col_addr = rand() % X->at(rand_row).ListW.size();
    //Check if edge was already removed
    if(X->at(rand_row).ListW[rand_col_addr].second == -1)
    {
      i--;
      continue;
    }
      
    rand_col = X->at(rand_row).ListW[rand_col_addr].first;
    ops = X->at(rand_row).Ops[rand_col_addr];
    
    //cout << "Removing Edge: " << rand_row << " " << rand_col << endl;//" " << rand_col_addr << endl;

    //Keeps track of real edges in network for later computation
    myEdge.node1 = rand_row;
    myEdge.node2 = rand_col;
    myEdge.edge_wt = 1;
    real_edges->push_back(myEdge);

    //Set weight to -1 to remove 
    //Remove both entries from temporary network
    X->at(rand_row).ListW[rand_col_addr].second = -1;
    X->at(rand_col).ListW[ops].second = -1;
      
    //Subtracts the degree number of each node
    D->at(rand_row).second--;
    D->at(rand_col).second--;

  }

 //Remove a-b for experiment
    /*int a=49;
    int b=188;
    for (int gg=0;gg<X->at(a).ListW.size();gg++)
    {
        int n1=X->at(a).ListW[gg].first;
        if(n1==b)
        {
            X->at(a).ListW[gg].second=-1;
            ops = X->at(a).Ops[gg];
            break;
        }
    }//end of for
    X->at(b).ListW[ops].second=-1;
    //Keeps track of real edges in network for later computation
    myEdge.node1 = a;
    myEdge.node2 = b;
    myEdge.edge_wt = 1;
    real_edges->push_back(myEdge);*/
    
    
    
    
    return;
    
}
/**End of Function ***/

#endif



  
  //Print temporary network with detached edges
  //print_detail(X);

//  cout << "Begin finding K-distance nodes\n";
 // find_k_dist_nonedge(X, nonexist, k_dist, CN_scores);

 // cout << "Common Neighbour:\n";
  //Gets the first PR for common neighbor
 // compute_first_precision_recall(X, nonexist, real_edges);
  

  //print_edges(nonexist);
  //cout << "Begin Local Indices Alogrithms\n";
  //Run local indices link predication algorithms
  
  
  /*Salton_helper(X, nonexist, real_edges, CN_scores, D);
  Jaccard_helper(X, nonexist, real_edges, CN_scores);
  Sorensen_helper(X, nonexist, real_edges, D);
  Hub_promoted_helper(X, nonexist, real_edges, D);
  Hub_depressed_helper(X, nonexist, real_edges, D);
  PA_helper(X, nonexist, real_edges, D);
  AA_helper(X, nonexist, real_edges, D);
  RA_helper(X, nonexist, real_edges, D);*/

  //Elimination Game
  /*
  cout << "Elimination game (Min degree):" << endl;
  new_elim_game(X, real_edges, 1, D);
  cout << "Elimination game (Max Clustering Coefficient):" << endl;
  new_elim_game(X, real_edges, 2, D);
  cout << "Elimination game (# Occur per Level 1):" << endl;
  new_elim_game(X, real_edges, 3, D);
*/

  
  //Clear temp network
  /*for(int i = 0; i < D.size(); i++)
  {
    cout << D[i] << endl;
  }*/


