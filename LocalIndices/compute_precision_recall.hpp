#ifndef COMPUTE_PRECISION_RECALL_HPP
#define COMPUTE_PRECISION_RECALL_HPP
#include "ADJ/add_edge.hpp"
#include "universal_func.hpp"
using namespace std;

//Prints Predicated edges to a file for testing
void print_heap(vector<Edge> nonexist)
{
  ofstream os1("predEdges.txt");
  while(!nonexist.empty())
  {
    os1 << "Predicated Edge: " << nonexist.at(0).node1 << " " << nonexist.at(0).node2 << " Score: " << nonexist.at(0).edge_wt << endl;
    pop_heap(nonexist.begin(), nonexist.end(), inc_wt);
      nonexist.pop_back();
  }

  os1.close();
}

//The first iteration of precision recall
void compute_first_precision_recall(A_Network *X, vector<Edge> nonexist, vector<Edge> *real_edges)
{
  ofstream os("edges.txt");
  
  //Weight of nonexist is the score
  int relevant = real_edges->size();
  int retrieved = 0;
  int rel_intersec_ret = 0;
  float precision, recall;
  int i = 0;
  int percent = real_edges->size()*2;
  
  for(int i = 0; i < real_edges->size(); i++)
  {
    os << "Edge: " << real_edges->at(i).node1 << " " << real_edges->at(i).node2 << endl;
  }

  //print_heap(nonexist);
  cout << "Common Neighbor:\n";
  while(!nonexist.empty())
  {
    if(i == percent)
    {
      break;
    }
    
    //adds the top edges into temporary networks
    //add_edge(&X, nonexist[0]);

    //If the real_edge was in top 80 scores,
    //then it is a relevant element
    //else it was a retrieved element
    if(check_edge(*real_edges, nonexist.at(0).node1, nonexist.at(0).node2) || check_edge(*real_edges, nonexist.at(0).node2, nonexist.at(0).node1))
    {
      rel_intersec_ret++;
      retrieved++;
    }
    else
    {
      retrieved++;
    }
    //cout << nonexist[0].node1 << " " << nonexist[0].node2 << " " << nonexist[0].edge_wt << endl;
    pop_heap(&nonexist, inc_wt);
    i++;
  }
  cout << "Intersec = " << rel_intersec_ret << " Retrieved: " << retrieved << endl;
  //Adds some of the other nodes that were retrieved that were not counted
  //retrieved *= 1.5;
  //Precision
  precision = rel_intersec_ret/(float)retrieved;
  //Recall
  recall = rel_intersec_ret/(float)relevant;

  cout << "Precision: " << precision << endl;
  cout << "Recall: " << recall << endl << endl;
  os.close();

}

//Compute Precision and recall of the Scores
//Relevant elements = Real edges
//Retrieved elements = nonexist
//Taking the top 80 elements for computation
//The "nonexist" edge list is in order by score
void compute_precision_recall(A_Network *X, vector<Edge> nonexist, vector<Edge> real_edges, vector<float> scores)
{
  //ofstream os("edges.txt");
  //ofstream os1("predEdges.txt");
  int relevant = real_edges.size();
  int retrieved = real_edges.size() *2;
  int rel_intersec_ret = 0;
  float precision, recall;
  
  /*for(int i = 0; i < real_edges.size(); i++)
  {
    os << "Edge: " << real_edges[i].node1 << " " << real_edges[i].node2 << endl;
  }*/
  /*for(int i = 0; i < nonexist.size(); i++)
  {
    os1 << "Predicated Edge: " << nonexist[i].node1 << " " << nonexist[i].node2 << " " << scores[i] << endl;
  }*/
  
  //os.close();
  //os1.close();

  //Computes retrieved and relevant elements
  //Uses scores from the given algorithms
  //Stops counting once 25 percent of scores are checked
  for(int i = 0; i < retrieved; i++)
  {
    //Stops at 80th element
    /*if(i == 80)
    {
      break;
    }*/

    //adds the top edges into temporary networks
    add_edge(X, nonexist[i]);
    //os1 << "Predicated Edge: " << nonexist[i].node1 << " " << nonexist[i].node2 << " " << scores[i]  << endl;//" Degree: " << D[nonexist[i].node1].second << " "  << D[nonexist[i].node2].second << endl;
    //If the real_edge was in top 80 scores,
    //then it is a relevant element
    //else it was a retrieved element
    if(check_edge(real_edges, nonexist[i].node1, nonexist[i].node2) || check_edge(real_edges, nonexist[i].node2, nonexist[i].node1))
    {
      rel_intersec_ret++;
      //retrieved++;
    }
    else
    {
      //retrieved++;
    }
  }
  //retrieved *= 1.5;
  cout << "Intersec = " << rel_intersec_ret << " Retrieved: " << retrieved << " Relevant: " << relevant << endl;
  //Precision
  precision = rel_intersec_ret/(float)retrieved;
  //Recall
  recall = rel_intersec_ret/(float)relevant;

  cout << "Precision: " << precision << endl;
  cout << "Recall: " << recall << endl << endl;

  //print_detail(X);
}

//Computees precision and recall for elimination game
//Elimination game does not base on top scores
void compute_elim_precision_recall(A_Network *X, vector<Edge> nonexist, vector<Edge> real_edges)
{
  int relevant = real_edges.size(), retrieved = 0;
  int rel_intersec_ret = 0;
  float precision, recall;
  int percent = real_edges.size()*2;

  for(int i = 0; i < percent; i++)
  {
	  if(check_edge(real_edges, nonexist[i].node1, nonexist[i].node2) || check_edge(real_edges, nonexist[i].node2, nonexist[i].node1))
	  {
		  rel_intersec_ret++;
	  }
	  retrieved++;
  }

  //Precision
  precision = rel_intersec_ret/(float)retrieved;
  //Recall
  recall = rel_intersec_ret/(float)relevant;

  cout << "Precision: " << precision << endl;
  cout << "Recall: " << recall << endl << endl;

  //print_detail(X);



}


#endif
