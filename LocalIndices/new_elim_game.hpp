#ifndef NEW_ELIM_GAME_HPP
#define NEW_ELIM_GAME_HPP
#include "../ESSENS/Basic_Analysis/Level0/ADJ/degree_centrality.hpp"
#include "../ESSENS/Basic_Analysis/Level0/ADJ/clustering_coefficient.hpp"
#include "../ESSENS/Basic_Change/Level0/ADJ/add_edge.hpp"
#include "compute_precision_recall.hpp"
using namespace std;

//Elimination degree using three different methods to pick the node to add edges to


//Method 1
//Sorts all degree by minimum degree
//Uses "insertsion sort" (for now)
void sort_min_degree(vector<int_int> &degreeC)
{
	int_int key;
	int j;
  	for(int i = 1; i < degreeC.size(); i++)
  	{	
    	key.first = degreeC[i].first;
		key.second = degreeC[i].second;
    	j = i - 1;
		//Moves key with higher number one position
    	while(j >= 0 && degreeC[j].second > key.second)
    	{
      		degreeC[j + 1].second = degreeC[j].second;
			degreeC[j + 1].first = degreeC[j].first;
      		j = j - 1;
    	}
    	degreeC[j + 1].first = key.first;
		degreeC[j+ 1].second = key.second;
  	}
}

//Method 2 & Method 3
//Sort all clustering coefficients in decreasing order
//Sorts all totals in decreasing order
void sort_max_cc_occurs(vector<double_int> &cc)
{
	double_int key;
	int j;
  for(int i = 1; i < cc.size(); i++)
  {
    key.first = cc[i].first;
		key.second = cc[i].second;
    j = i - 1;

    //Moves key with higher number one position
    while(j >= 0 && cc[j].first < key.first)
    {
      cc[j + 1].second = cc[j].second;
			cc[j + 1].first = cc[j].first;
      j = j - 1;
    }
    cc[j + 1].first = key.first;
		cc[j+ 1].second = key.second;

  }
}

//Connects neighbors of the node if they are not connected
void connect_neighbors(A_Network &X, vector<Edge> &nonexist, int node)
{
	int current, next;
	vector<int> neighbors;
	int neighbor_check;
	Edge mye;

	//Picks the current node
	//Level 1 nodes
	for(int i = 0; i < X[node].ListW.size(); i++)
	{
		//Level 1 node
		current = X[node].ListW[i].first;

		//Gets all other nodes of the row
		for(int j = i+1; j < X[node].ListW.size(); j++)
		{
			//Another level 1 node
			next = X[node].ListW[j].first;
			neighbor_check = 0;

			//Check the next node if it is neighbors with the current node
			//Checks level 2 nodes
			for(int k = 0; k < X[next].ListW.size(); k++)
			{
				//Checks if level 2 node is same as level 1 node
				if(X[next].ListW[k].first == current && X[next].ListW[k].second != -1)
				{
					neighbor_check = 1;
					break;
				}
			}
			
			mye.node1 = current;
			mye.node2 = next;
			mye.edge_wt = 1;
			//Adds edge if they weren't connected
			if(neighbor_check != 1)
			{
				//cout << "Adding edge " << current << " " << next << endl;
				nonexist.push_back(mye);
				//adds the top edges into temporary networks
		    	add_edge(&X, mye);
			}
		}
	}
}

//only neighbors
void get_neighbors(int node, vector<int_double> Vrow, vector<int> *neighbors, int overload)
{
	//clear neighbors;
	neighbors->clear();
	
	//Add the neighbors;
	for(int i=0;i<Vrow.size();i++)
	{
		//Check for -1 weight
		if(Vrow[i].second != -1)
		{
			neighbors->push_back(Vrow[i].first);
		}
	}
	
return;}

/*** Compute Clustering Coefficient ***/
void compute_CC(A_Network X, int node, double *cc, int overload)
{
    *cc=0.0;
    double numerator=0.0;
    double denominator=0.0;
    vector<int> common_neighs;
    common_neighs.clear();

    
    vector<int> node_set;
    node_set.clear();
    get_neighbors(node,X[node].ListW, &node_set);
    sort(&node_set);
    
    for(int i=0;i<node_set.size();i++)
    { int nx=node_set[i];
        vector<int> myneighbors;
        myneighbors.clear();
        
        get_neighbors(nx, X[nx].ListW, &myneighbors, 0);
        sort(&myneighbors);
        
        common_neighs=intersect(myneighbors,node_set);
        numerator=numerator+(double)common_neighs.size();
        
    }//end of for
    
    double total_nodes=(double)node_set.size();
    denominator=total_nodes*(total_nodes-1);
    *cc=numerator/denominator;
    
    return;
}
//Gets the occurances of the level 2 nodes from all levels
void get_occurances(A_Network X, vector<int> level1_neighbors, vector<int> level2_neighbors, vector<int_int> &occurances)
{
	bool check;
	//First = # of occurances
	//Second = actual node
	int_int occur;
	//For each level 2 node...
	for(int i = 0; i < level2_neighbors.size(); i++)
	{
		check = false;

		//Find occurances
		for(int j = 0; j < occurances.size(); j++)
		{
			//Adds the occurances if node was found
			if(occurances[j].second == level2_neighbors[i])
			{
				check = true;
				occurances[j].first++;
				break;
			}
		}
		//If occurance wasn't found then adds that node to the vector
		if(!check)
		{
			occur.first = 1;
			occur.second = level2_neighbors[i];
			occurances.push_back(occur);
		}
	}
}

//Deletes Level 0 node from level 1 node list
void delete_level0_node(int node , vector<int> level1_neighbors)
{
	for(int i = 0; i < level1_neighbors.size(); i++)
	{
		if(level1_neighbors[i] == node)
		{
			level1_neighbors.erase(level1_neighbors.begin() + i);
			return;
		}
	}
}

//Create maximum chordal graph by adding edges to neighbors that have nonexistent Edges
//Picking node A is key to getting minimal edges added
//Three methods to picking node A
//1. Pick A by minimum degree
//2. Pick A by maximum clustering_coefficient
//3. Pick A by # of occurances/ # of level 1 nodes
void new_elim_game(A_Network X, vector<Edge> real_edges, int method, vector<int_int> D)
{
	vector<Edge> nonexist;
	float percent = .25;
	switch(method)
	{
		//Pick by minimum degree
		case 1:
		{
			//Sort degree in increasing order
			sort_min_degree(D);

			/*for(int i = 0; i < degreeC.size(); i++)
			{
				cout << degreeC[i].first << " " << degreeC[i].second << endl;
			}*/

			//Connect neighbors
			//Picks minimum degrees first
			for(int i = 0; i < (D.size()*percent); i++)
			{
				connect_neighbors(X, nonexist, D[i].first);
			}

			//print_detail(X);
		}
		break;

		//Pick by max cc
		case 2:
		{
			vector<double_int> cc_node;
			double cc;
			double_int cc_n;

			//Gets cc for every node
			for(int i = 0; i < X.size(); i++)
			{
				compute_CC(X, i, &cc, 0);
				if(isnan(cc))
				{
					cc = 0.0;
				}
				cc_n.first = cc;
				cc_n.second = i;
				cc_node.push_back(cc_n);
			}

			//Sort cc in decreasing order
			sort_max_cc_occurs(cc_node);

			/*for(int i = 0; i < X.size(); i++)
			{
					cout << "CC of " << i << "is: " << cc_node[i].first << endl;
			}*/

			//Connect neighbors
			//Picks highest clustering coe
			for(int i = 0; i < (cc_node.size()*percent); i++)
			{
				connect_neighbors(X, nonexist, cc_node[i].second);
			}
			//print_detail(X);

		}
		break;
		case 3:
		{
			vector<int> level1_neighbors;
			vector<int> level2_neighbors;
			//First int is number of occurances, second is the actual node
			vector<int_int> occurances;


			double_int t_n;
			vector<double_int> total;

			for(int i = 0; i < X.size(); i++)
			{
				t_n.first = 0;
				//First we find all level 1 nodes
				get_neighbors(i, X[i].ListW, &level1_neighbors, 0);
				//Make sure not to count Level 0 node
				delete_level0_node(X[i].Row , level1_neighbors);

				//Gets all level 2 nodes
				for(int j = 0; j < level1_neighbors.size(); j++)
				{
					get_neighbors(j, X[level1_neighbors[j]].ListW, &level2_neighbors, 0);

					get_occurances(X, level1_neighbors, level2_neighbors, occurances);
				}
				for(int j = 0; j < occurances.size(); j++)
				{
					//cout << "occurance: " << occurances[j].first << " " << occurances[j].second << endl;
					//# of occurances/# of level 1 nodes
					t_n.first = t_n.first + occurances[j].second;
				}
				t_n.first /= level1_neighbors.size();


				t_n.second = X[i].Row;

				total.push_back(t_n);

				//cout << "Total: " << t_n.first << " " << t_n.second << endl;
				occurances.clear();
			}

			sort_max_cc_occurs(total);

			//Connect neighbors
			for(int i = 0; i < (total.size()*percent); i++)
			{
				connect_neighbors(X, nonexist, total[i].second);
			}


		}
		break;

		default:
			break;
	}
	//compute_elim_precision_recall(X, nonexist, real_edges);
}

#endif
