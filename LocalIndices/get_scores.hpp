#ifndef GET_SCORES_HPP
#define GET_SCORES_HPP
#include "link_predication_algorithms.hpp"
#include "new_elim_game.hpp"
#include "compute_precision_recall.hpp"
using namespace std;



//Prints top 80 scores
void print_scores(vector<Edge> nonexist, vector<float> scores)
{
  cout << "Scores of each node\n";
  for(int i = 0; i < scores.size(); i++)
  {
    if(i == 80)
    {
      break;
    }
    cout << "(" << nonexist[i].node1 << ", " << nonexist[i].node2 << "): " << scores[i] << endl;
  }
}

//Sort all scores and pick only top 80 scores
//Uses "insertsion sort" (for now)
void sort_scores(vector<Edge> &nonexist, vector<float> &scores)
{
  float key, j;
  Edge key2;
  for(int i = 1; i < scores.size(); i++)
  {
    key = scores[i];
    key2 = nonexist[i];
    j = i - 1;

    //Moves key with lower number one position
    while(j >= 0 && scores[j] < key)
    {
      scores[j + 1] = scores[j];
      nonexist[j + 1] = nonexist[j];
      j = j - 1;
    }
    scores[j + 1] = key;
    nonexist[j+ 1] = key2;
  }
}

//Helper functions to run all local indices algorithms



//Common Neighbor
void CN_helper(A_Network *X, vector<Edge> nonexist, vector<Edge> real_edges)
{
  vector<float> scores;
  int CN_score;
  Edge mye;
  
  //cout << "Common Neighbors: \n";  
 
  //Checks possible pair of edge each pair of edges that dont exist
  for(int i = 0; i < nonexist.size(); i++)
  {
    //Add the score to the scores List
    CN_score = common_neighbours(X, nonexist[i].node1, nonexist[i].node2);
    scores.push_back(CN_score);  
  }
 // cout << "Finished CN\n";

  sort_scores(nonexist, scores);

  /*
  ofstream os("randomEdgeCN.txt");
  for(int i = 0; i < nonexist.size(); i++)
  {
    os << nonexist[i].node1 << " " << nonexist[i].node2 << " " << scores[i] << endl;
  }
  os.close();*/
  
  //print_scores(nonexist, scores);
  compute_precision_recall(X, nonexist, real_edges, scores);
 
}

/*
//Salton index
void Salton_helper(A_Network &X, vector<Edge> nonexist, vector<Edge> real_edges, vector<int> CN_scores, vector<int_int> D)  
{
  vector<float> scores;

  cout << "Salton Index: \n";
   
  for(int i = 0; i < nonexist.size(); i++)
  {
    //Add the score to the scores List
    scores.push_back(salton_index(X, nonexist[i].edge_wt, nonexist[i].node1, nonexist[i].node2, D));
  }

  sort_scores(nonexist, scores);
  //print_scores(nonexist, scores);
  compute_precision_recall(X, nonexist, real_edges, scores);
}
*/

//Jaccard index
void Jaccard_helper(A_Network *X, vector<Edge> nonexist, vector<Edge> real_edges)
{  
  vector<float> scores;

  cout << "Jaccard Index: \n";
  
  for(int i = 0; i < nonexist.size(); i++)
  {
    //Add the score to the scores List
    scores.push_back(jaccard_index(X, nonexist[i].edge_wt, nonexist[i].node1, nonexist[i].node2));
  }

  sort_scores(nonexist, scores);
  //print_scores(nonexist, scores);
  compute_precision_recall(X, nonexist, real_edges, scores);
}

/*
//Sorensen index
void Sorensen_helper(A_Network &X, vector<Edge> nonexist, vector<Edge> real_edges, vector<int_int> D)  
{
  
  vector<float> scores;
  
  cout << "Sorensen Index: \n";
  
  for(int i = 0; i < nonexist.size(); i++)
  {
    //node1 = X[nonexist[i].node1].Row;
    //node2 = X[nonexist[i].node2].Row;
    //Add the score to the scores List
    scores.push_back(sorensen_index(X, nonexist[i].edge_wt, D, nonexist[i].node1, nonexist[i].node2));
  }

  sort_scores(nonexist, scores);
  //print_scores(nonexist, scores);
  
  compute_precision_recall(X, nonexist, real_edges, scores);
}


//Hub Promoted index
void Hub_promoted_helper(A_Network &X, vector<Edge> nonexist, vector<Edge> real_edges, vector<int_int> D) 
{
  
  vector<float> scores;

  cout << "Hub Promoted Index: \n";
  
  for(int i = 0; i < nonexist.size(); i++)
  {
    //Add the score to the scores List
    scores.push_back(hub_index(X, nonexist[i].edge_wt, D, nonexist[i].node1, nonexist[i].node2, 0));
  }

  sort_scores(nonexist, scores);
  //print_scores(nonexist, scores);
  
  compute_precision_recall(X, nonexist, real_edges, scores);
}

//Hub Depressed index
void Hub_depressed_helper(A_Network &X, vector<Edge> nonexist, vector<Edge> real_edges, vector<int_int> D) 
{
  
  vector<float> scores;

  cout << "Hub Depressed Index: \n";
  
  for(int i = 0; i < nonexist.size(); i++)
  {
    //Add the score to the scores List
    scores.push_back(hub_index(X, nonexist[i].edge_wt, D, nonexist[i].node1, nonexist[i].node2, 1));
  }

  sort_scores(nonexist, scores);
  //print_scores(nonexist, scores);
  
  compute_precision_recall(X, nonexist, real_edges, scores);
}


//Preferential Attachment index  
void PA_helper(A_Network &X, vector<Edge> nonexist, vector<Edge> real_edges, vector<int_int> D) 
{
  
  vector<float> scores;

  cout << "Preferential Attachment Index: \n";
  
  for(int i = 0; i < nonexist.size(); i++)
  {
    //Add the score to the scores List
    scores.push_back(preferential_attachment_index(X, D, nonexist[i].node1, nonexist[i].node2));
  }

  sort_scores(nonexist, scores);
  //print_scores(nonexist, scores);
  
  compute_precision_recall(X, nonexist, real_edges, scores);
}
*/

//Adamic Adar index

void AA_helper(A_Network *X, vector<Edge> nonexist, vector<Edge> real_edges, vector<int_int> D) 
{
  
  vector<float> scores;

  cout << "Adamic Adar Index: \n";

  for(int i = 0; i < nonexist.size(); i++)
  {
    //Add the score to the scores List
    scores.push_back(adamic_adar_index(X, D, nonexist[i].node1, nonexist[i].node2));
  }

  sort_scores(nonexist, scores);
  //print_scores(nonexist, scores);
  
  compute_precision_recall(X, nonexist, real_edges, scores);
}

/*
//Resource Allocation index
void RA_helper(A_Network &X, vector<Edge> nonexist, vector<Edge> real_edges, vector<int_int> D) 
{
  
  vector<float> scores;

  cout << "Resource Allocation Index: \n";
  
  for(int i = 0; i < nonexist.size(); i++)
  {
    //Add the score to the scores List
    scores.push_back(resource_allocation_index(X, D, nonexist[i].node1, nonexist[i].node2));
  }

  sort_scores(nonexist, scores);
  //print_scores(nonexist, scores);
  
  compute_precision_recall(X, nonexist, real_edges, scores);
}*/

#endif
