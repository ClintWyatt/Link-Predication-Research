#ifndef SAMPLING_HPP
#define SAMPLING_HPP
using namespace std;

//Initialization sample as empty network
void init_sample(A_Network *S, A_Network *X)
{
  ADJ_Bundle my_bundle;

  S->clear();
  
  //Add empty nodes to sample graph
  for(int i = 0; i < X->size(); i++)
  {
    my_bundle.Row = X->at(i).Row;
    S->push_back(my_bundle);
  }
}

//Add node to sample
void add_node_sample(A_Network *S, A_Network *X, int node)
{
  for(int i = 0; i < X->at(node).ListW.size(); i++)
  {
    S->at(node).ListW.push_back(X->at(node).ListW[i]);
    S->at(node).Ops.push_back(0);
  }
}

//|N(S) U S|
//Sample set S
//Edge neighbors of sample S_neighbors
//Neighbor nodes of sample from original network Vrow
int neighbor_sample_union_sample(A_Network *S, vector<int> *S_neighbors, vector<int_double> Vrow)
{
  int S_count = 0, V_count = 0;
  int n_union_s = 0;
  int V;

  //Check if the neighbors of V are in sample
  while (V_count < Vrow.size())
  {
    //Gets neughbors of V
    V = Vrow[V_count].first;

    //Check sample node with v neighbors
    if (S->at(V).ListW.size() != 0) //If sample has edges, then its a neighbor
    {
      n_union_s++;
    }
    
    //Increment V list
    V_count++;
  }

  V_count = 0;
  S_count = 0;

  //Check if the neighbors of V are in neighbors of sample
  while (V_count < Vrow.size() && S_count < S_neighbors->size())
  {
    //Check sample node with v neighbors
    if (Vrow[V_count].first == S_neighbors->at(S_count))
    {
      n_union_s++;
      V_count++;
      S_count++;
    }
    else if (Vrow[V_count].first > S_neighbors->at(S_count))
    {
      S_count++;
    }
    else if (Vrow[V_count].first < S_neighbors->at(S_count))
    {
      V_count++;
    }
  }

  //Return union result
  return n_union_s;
}
void writeNetwork(A_Network *X, A_Network *S, string alg)
{
    ofstream origional("origional.txt");
    ofstream sample(alg+"_sample.txt");

    for(int i =0; i < X->size(); i++)
    {
        origional << X->at(i).Row << ": ";
        sample << S->at(i).Row <<": ";
        for(int j =0; j < X->at(i).ListW.size(); j++)
        {
            origional <<X->at(i).ListW[j].first << " ";
        }
        origional <<endl;
        for(int j =0; j < S->at(i).ListW.size(); j++)
        {
            sample << S->at(i).ListW[j].first << " ";
        }
        sample << endl;
    }
    origional.close();
    sample.close();
}
//Snowball Expansion Sampler(XSN)
//Sample set S
//Max Sample size k
void XSN(A_Network *S, A_Network *X, int k)
{
  srand(time(NULL));
  ADJ_Bundle my_bundle;
  int S_size = 0;                //current sample size
  int X_neighbor;            //neighbor from original network
  vector<bool> visited;      //Checks if node as been visited
  vector<int> S_neighbors;   //Sample neighbors
  int current_v, max_EC = 0, count = 0;
  int max_v, EC;              //hold expansion contribution score

  //Pick random start node from network
  int v = rand() % X->size(); 

  //Initialize sample as empty network
  init_sample(S, X);

  cout << "\nRunning Snowball Expansion Sampler Algorithm\n";

  //Initialize containers
  visited.clear();
  visited.resize(X->size(), false);
  S_neighbors.clear();
  
  //Add first random node's edges to network
  add_node_sample(S, X, v);//line 21
  //cout << "here" << endl;
  //cout << "First random node: " << S->at(v).Row << endl << endl;
  
  //Select new node v in the set of N(S) based on maximization
  while (S_size <= k)
  {
    //Marks all the sample nodes as visited
    visited.at(S->at(count).Row) = true;
    //Clear neighbors for new calculation
    S_neighbors.clear();
    //cout << "here" << endl;
    //Get neighbors of sample
    for (int i = 0; i < S->size(); i++)
    {
      for (int j = 0; j < S->at(i).ListW.size(); j++)
      {
        if (visited.at(S->at(i).ListW[j].first) == false) //check if node was already in neighbors
        {
          //Use original network to get neighbors of sample network
          S_neighbors.push_back(S->at(i).ListW[j].first);
        }
      }
    }
    
    max_EC = 0;

    //For each v in sample neighbors
    //v in set N(S)
    for (int i = 0; i < S_neighbors.size(); i++)
    {
      //N({v})
      current_v = X->at(S_neighbors.at(i)).ListW.size();
      
      //|N({v}) - (N(S) U S)|
      EC = current_v - neighbor_sample_union_sample(S, &S_neighbors, X->at(S_neighbors.at(i)).ListW);
      //cout << "max EC: " << max_EC << " EC: " << EC << endl;

      //Check if expansion contribution is higher than preivous
      if (EC > max_EC)
      {
        //Change the new max EC
        max_EC = EC;
        max_v = X->at(S_neighbors.at(i)).Row;
      }
    }
  
    //Add max V node to sample
    add_node_sample(S, X, max_v);
    visited.at(max_v) = true;
    

    count = max_v;
    S_size++;  
  }
  //Add opposite edges to sample network
  add_opposite_edge(S);
  cout << "Sample Size: " << S->size() << endl;
  return;
}

//Random Walk Sampler
//Sample set S
//Sample size k
void random_walk(A_Network *S, A_Network *X, int k)
{
  srand(time(NULL));
  vector<bool> visited;                //Checks if node as been visited
  int p = 15, rando;                   //Probability to fly back to starting node
  int start_node = rand() % X->size(); //start at random node
  int current, preivous, index;
  int c = 0;
  int S_size = 1; //Sample size

  //Initialize sample as empty network
  init_sample(S, X);

  //cout << "Starting node: " << start_node << endl;

  visited.clear();
  visited.resize(X->size(), false);

  cout << "Running Random Walk\n";

  //Add startnode to sample
  add_node_sample(S, X, start_node);
  preivous = start_node;
  visited.at(start_node) = true;

  //Runs until k size has been reached
  while (S_size <= k)
  {
    rando = rand() % 100 + 1;
    if (rando <= p) //p probablility to jump back to start node
    {
      current = start_node; //Jump back toi start node
      //cout << "Roll back to start current: " << current << " prev: " << preivous << endl;
    }
    else
    {
      index = rand() % X->at(preivous).ListW.size(); //Pick random index from previous node
      current = X->at(preivous).ListW[index].first;  //Set the random node from the index
      //cout << "ListW size " << X->at(preivous).ListW.size() << " ";
      //cout << "current: " << current << " prev: " << preivous << endl;
    }

    //Check if node was already added
    if (visited.at(current) == false)
    {
      //Add node to sample
      add_node_sample(S, X, current);
      visited.at(current) = true;
      S_size++;
    }

    preivous = current;

    //If sampling is complete after many steps, choose a different start node
    if (c == 10000)
    {
      start_node = rand() % X->size();
      preivous = start_node;
    }

    c++;
  }

  //Add opoosite edges to sample network
  add_opposite_edge(S);//universal_func.hpp
}

//Random Node Sampler
void random_node(A_Network *S, A_Network *X, int k)
{
  srand(time(NULL));
  int rando; //random node
  int S_size = 0; //sample size
  vector<bool> visited;

  //Initialize sample as empty network
  init_sample(S, X);

  visited.clear();
  visited.resize(X->size(), false);

  cout << "Running Random Node\n";

  while (S_size <= k)
  {
    //Pick random node for original netowrk
    rando = rand() % X->size();

    //Check if random node was already added to sample network
    if (visited.at(rando) == false)
    {
      add_node_sample(S, X, rando);
      visited.at(rando) = true;
      S_size++;
    }
  }

  //Add opposite edges to sample network
  add_opposite_edge(S);
}

//Random Edge Sampler
void random_edge(A_Network *S, A_Network *X, int k)
{
  //Init random seed
  srand(time(NULL));

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
    node = rand() % X->size();
    edge_index = rand() % X->at(node).ListW.size();
    edge = X->at(node).ListW[edge_index].first;

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
      S->push_back(my_bundle);

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
}

//Forest Fire Sampler
//Sample set S
//Sample size k
void forest_fire(A_Network *S, A_Network *X, int k)
{
  //Initialize random seed
  srand(time(NULL));

  int pf = 70, pb;
  int seed_node; 
  int rando, S_edges = 0;
  queue<int> nodeQueue;
  vector<bool> visited;

  cout << "Running Forest Fire\n";

  //Initialize sample as empty network
  init_sample(S, X);

  visited.clear();
  visited.resize(X->size(), false);

  //Pick random seed node
  seed_node = rand() % S->size();
    
  //Initial queue 
  nodeQueue.push(seed_node);
  visited.at(seed_node) = true;

  while(S_edges < k)
  {
    nodeQueue.pop();
    
    //Go through each edge on the node
    for(int i = 0; i < X->at(seed_node).ListW.size(); i++)
    {
      //Burn node: Add node to queue if link was burned
      rando = rand() % 100 + 1; //Random number
      if (rando <= pf)          //Burn link with probability of pf
      { 
        //Check if node has already burned links
        if(visited.at(X->at(seed_node).ListW[i].first) == false)
        {
          //Add node to queue
          nodeQueue.push(X->at(seed_node).ListW[i].first);
          //visit node
          visited.at(X->at(seed_node).ListW[i].first) = true;
        }      
      }
      else //Add non-burned edge to sample
      {
        S->at(seed_node).ListW.push_back(X->at(seed_node).ListW[i]);
        S->at(seed_node).Ops.push_back(0);
        S_edges++;
      }
    }

    if(nodeQueue.empty())
    {
      break;
    }
    seed_node = nodeQueue.front();
    
  }
  
}

//Write scores to files
void write_output(string filename, vector<Edge> nonexist, vector<float> scores)
{
  ofstream os(filename);
  float prev, current, count = 0;

  if (!os)
  {
    cout << "Failed to open sample output file\n";
    exit(EXIT_FAILURE);
  }

  //Printing scores
  for (int i = 0; i < scores.size(); i++)
  {
    os << scores.at(i) << endl;
  }

  os.close();
  return;
}

//Tests nodes in the sample netowrk with nodes not in sample but in original network
void sample_scores(A_Network *S, A_Network *X, string SampleAlgor)//samples the score based off of the snowball or random walk...etc
{
  
  int common_count = 0;
  bool found;
  vector<bool> visited;
  vector<Edge> nonexist;
  vector<float> scores;
  vector<int_int> D;
  string filename;
  Edge mye;

  //Tracks sample nodes that are visited
  visited.clear();
  visited.resize(X->size(), false);//initializing all nodes representing visited for network X to false. 

  //Visit nodes in sample network
  for (int i = 0; i < S->size(); i++)
  {
    //If node on sample has edges
    if(S->at(i).ListW.size() != 0)
    {
      visited.at(S->at(i).Row) = true;//set the row to true in the visited vector
    }
  }

  //Getting edges that dont exist in sample, but in the origional
  for(int i = 0; i < X->size(); i++)
  {
    //If the node isnt in sample, then add all edges to nonexistent 
    if(visited.at(X->at(i).Row) == false)//if there are no edges for the row in the S network
    {
      //Add all edges in the same row in the X network to nonexistent list
      for(int j = 0; j < X->at(i).ListW.size(); j++)
      {
        mye.node1 = X->at(i).Row;//pushing back the node with neighbors to the edge mye
        mye.node2 = X->at(i).ListW[j].first;
        mye.edge_wt = 0;
  
        nonexist.push_back(mye);//adding the edge to the vector of edges
      }
    }
    else //else check the sample node and add edges that are not in sample
    {
      //For for said sample node
      for(int j = 0; j < S->size(); j++)
      {
        //The sample node was found
        if(S->at(j).Row == X->at(i).Row)//i is referring to the outermost for loop at line 535
        {
          //Check which nodes are in original but not in sample
          for(int k = 0; k < X->at(i).ListW.size(); k++)//this loop goes through the edges for the row in network x
          {
            found = false;
            for(int l = 0; l < S->at(j).ListW.size(); l++)//goes through the edges for the row in network s
            {
              
              //node was found
              if(S->at(j).ListW[l].first == X->at(i).ListW[k].first)//j refers to the loop at line 553
              {
                found = true;
                break;
              }
            }
            //Add node that is missing from sample network
            if(found == false)
            {
              mye.node1 = X->at(i).Row;
              mye.node2 = X->at(i).ListW[k].first;
              mye.edge_wt = 0;

              nonexist.push_back(mye);//pushing back the edge to the vector of edges
            }
          }
        }
      }
    }
  }
  /*
  ofstream origional("notInSample.txt");

  for(int i =0; i < nonexist.size(); i++)
  {
    origional << "(" << nonexist[i].node1 << ", " << nonexist[i].node2 << ")" << endl;
  }
  origional.close();
  */
  total_edges_degree(X, &D);//from detach_edges.hpp, may have to use S for score on sampled network

  //CN
  //ofstream output("commonNeighbors.txt");
  cout << "Getting CN score for " << SampleAlgor << endl;
  for (int i = 0; i < nonexist.size(); i++)
  {
    //Add the score to the scores List
    scores.push_back(common_neighbours(X, nonexist[i].node1, nonexist[i].node2));//method is in link_predication_algorithms.hpp
    nonexist[i].edge_wt = scores[i];//making the score the weight of the edge
  }
  //output.close();
  sort_scores(nonexist, scores);
  filename = "SampleScores/CN_sample_scores_" + SampleAlgor;
  write_output(filename, nonexist, scores);

  filename.clear();
  scores.clear();

  //AA
  cout << "Getting AA score for " << SampleAlgor << endl;
  for (int i = 0; i < nonexist.size(); i++)
  {
    //Add the score to the scores List
    scores.push_back(adamic_adar_index(X, D, nonexist[i].node1, nonexist[i].node2));//method is in link_predication_algorithms.hpp
  }
  sort_scores(nonexist, scores);
  filename = "SampleScores/AA_sample_scores_" + SampleAlgor;
  write_output(filename, nonexist, scores);

  filename.clear();
  scores.clear();

  cout << "Getting JC score for " << SampleAlgor << endl;
  //JC
  for (int i = 0; i < nonexist.size(); i++)
  {
    //Add the score to the scores List
    scores.push_back(jaccard_index(X, nonexist[i].edge_wt, nonexist[i].node1, nonexist[i].node2));
  }
  sort_scores(nonexist, scores);
  filename = "SampleScores/JC_sample_scores_" + SampleAlgor;
  write_output(filename, nonexist, scores);

  filename.clear();
  scores.clear();

  cout << "Getting KANTZ score for " << SampleAlgor << endl;
  //Katz
  for (int i = 0; i < nonexist.size(); i++)
  {
    //Add the score to the scores List
    scores.push_back(katz(X, .05, 2, nonexist[i].node1, nonexist[i].node2));
  }
  sort_scores(nonexist, scores);
  filename = "SampleScores/Katz_sample_scores_" + SampleAlgor;
  write_output(filename, nonexist, scores);

  filename.clear();
  scores.clear();
    
  return;
}

//algorithm for missing edges in the sample and origional comapred to the complete graph
void score(A_Network *S, A_Network *X, string SampleAlgor)
{
  vector<Edge> nonexist;
  vector<int_int> D;
  string filename;
  vector<float> scores;
  for(int i =0; i < X->size(); i++)//looping through the entire network
  {
    for(int j =0; j < X->at(i).missingSample_Origional.size(); j++)//looping through edges missing in the sample and origional
    {
      nonexist.push_back(X->at(i).missingSample_Origional[j]);//adding the edge to the nonexistent vector
    }
  }
  //total_edges_degree(X, &D);
  os_total_edges_degree(X, &D);
   //CN
  for (int i = 0; i < nonexist.size(); i++)
  {
    //Add the score to the scores List
    //scores.push_back(common_neighbours(X, nonexist[i].node1, nonexist[i].node2));//method is in link_predication_algorithms.hpp
    scores.push_back(Os_common_neighbours(X, nonexist[i].node1, nonexist[i].node2));//for non adjacent rows
    nonexist[i].edge_wt = scores[i];//making the score the weight of the edge
  }
  sort_scores(nonexist, scores);
  filename = "SampleScores/O_S-noadjacent-CN_sample_scores_" + SampleAlgor;
  write_output(filename, nonexist, scores);

  filename.clear();
  scores.clear();

  //AA
  for (int i = 0; i < nonexist.size(); i++)
  {
    //Add the score to the scores List
    scores.push_back(os_adamic_adar_index(X, D, nonexist[i].node1, nonexist[i].node2));//method is in link_predication_algorithms.hpp
  }
  sort_scores(nonexist, scores);
  filename = "SampleScores/O_S-noadjacent-AA_sample_scores_" + SampleAlgor;
  write_output(filename, nonexist, scores);

  filename.clear();
  scores.clear();

  //JC
  for (int i = 0; i < nonexist.size(); i++)
  {
    //Add the score to the scores List
    scores.push_back(jaccard_index(X, nonexist[i].edge_wt, nonexist[i].node1, nonexist[i].node2));
  }
  sort_scores(nonexist, scores);
  filename = "SampleScores/O_S-noadjacent-JC_sample_scores_" + SampleAlgor;
  write_output(filename, nonexist, scores);

  filename.clear();
  scores.clear();

  //Katz
  for (int i = 0; i < nonexist.size(); i++)
  {
    //Add the score to the scores List
    scores.push_back(katz(X, .05, 4, nonexist[i].node1, nonexist[i].node2));
  }
  sort_scores(nonexist, scores);
  filename = "SampleScores/O_S-noadjacent-Katz_sample_scores_" + SampleAlgor;
  write_output(filename, nonexist, scores);

  filename.clear();
  scores.clear();
  
  return;


}

//method for edges missing in the sample graph
void sample_nonexist_score(A_Network *S, A_Network *X, string SampleAlgor)
{
  vector<Edge> nonexist;
  vector<int_int> D;
  string filename;
  vector<float> scores;
  cout <<S->size() << endl;
  for(int i =0; i < S->size(); i++)//looping through the entire network
  {
    for(int j =0; j < S->at(i).missingEdges.size(); j++)//looping through edges missing in the sample
    {
      nonexist.push_back(S->at(i).missingEdges[j]);//adding the edge to the nonexistent vector
    }
  }

  sample_edges_degree(S, &D);
  //CN
  for (int i = 0; i < nonexist.size(); i++)
  {
    scores.push_back(sample_CN(S, nonexist[i].node1, nonexist[i].node2));//for non adjacent rows
    nonexist[i].edge_wt = scores[i];//making the score the weight of the edge
  }
  sort_scores(nonexist, scores);
  filename = "SampleScores/sample-noadjacent-CN_sample_scores_" + SampleAlgor;
  write_output(filename, nonexist, scores);

  filename.clear();
  scores.clear();

  //AA
  for (int i = 0; i < nonexist.size(); i++)
  {
    //Add the score to the scores List
    scores.push_back(sample_adamic_adar_index(S, D, nonexist[i].node1, nonexist[i].node2));//method is in link_predication_algorithms.hpp
  }
  sort_scores(nonexist, scores);
  filename = "SampleScores/sample-noadjacent-AA_sample_scores_" + SampleAlgor;
  write_output(filename, nonexist, scores);

  filename.clear();
  scores.clear();

  //JC
  for (int i = 0; i < nonexist.size(); i++)
  {
    //Add the score to the scores List
    scores.push_back(jaccard_index(X, nonexist[i].edge_wt, nonexist[i].node1, nonexist[i].node2));
  }
  sort_scores(nonexist, scores);
  filename = "SampleScores/O_S-noadjacent-JC_sample_scores_" + SampleAlgor;
  write_output(filename, nonexist, scores);

  filename.clear();
  scores.clear();

  //Katz
  for (int i = 0; i < nonexist.size(); i++)
  {
    //Add the score to the scores List
    scores.push_back(katz(X, .05, 4, nonexist[i].node1, nonexist[i].node2));
  }
  sort_scores(nonexist, scores);
  filename = "SampleScores/O_S-noadjacent-Katz_sample_scores_" + SampleAlgor;
  write_output(filename, nonexist, scores);

  filename.clear();
  scores.clear();
  
  return;
}

//used for a network that has edges only in its network and no other network
//This method is used for edges that are in the origional network that are not in the sample network. Same as network X minus the intersection of 
//network X and network S
void uniqueScore(A_Network *X, string SampleAlgor)
{
  int common_count = 0;
  bool found;
  vector<bool> visited;
  vector<Edge> exist;//represents unique edges to network X (could also be S)
  vector<float> scores;
  vector<int_int> D;
  string filename;
  Edge mye;

  for(int i =0; i < X->size(); i++)
  {
    for(int j =0; j < X->at(i).unique.size(); j++)
    {
      mye.node1 = X->at(i).Row;
      mye.node2 = X->at(i).unique[j].first;
      exist.push_back(mye);
    }
  }

  total_edges_unique(X, &D);//from detach_edges.hpp

  //CN
  for (int i = 0; i < exist.size(); i++)
  {
    //Add the score to the scores List
    scores.push_back(common_neighbours(X, exist[i].node1, exist[i].node2));//method is in link_predication_algorithms.hpp
    exist[i].edge_wt = scores[i];//making the score the weight of the edge
  }
  sort_scores(exist, scores);
  filename = "SampleScores/origional_scores_CN-" + SampleAlgor;
  write_output(filename, exist, scores);

  filename.clear();
  scores.clear();

  //AA
  for (int i = 0; i < exist.size(); i++)
  {
    //Add the score to the scores List
    scores.push_back(adamic_adar_index(X, D, exist[i].node1, exist[i].node2));//method is in link_predication_algorithms.hpp
  }
  sort_scores(exist, scores);
  filename = "SampleScores/origional_scores_AA-" + SampleAlgor;
  write_output(filename, exist, scores);

  filename.clear();
  scores.clear();

  //JC
  for (int i = 0; i < exist.size(); i++)
  {
    //Add the score to the scores List
    scores.push_back(jaccard_index(X, exist[i].edge_wt, exist[i].node1, exist[i].node2));
  }
  sort_scores(exist, scores);
  filename = "SampleScores/origional_scores_JC-" + SampleAlgor;
  write_output(filename, exist, scores);

  filename.clear();
  scores.clear();

  //Katz
  for (int i = 0; i < exist.size(); i++)
  {
    //Add the score to the scores List
    scores.push_back(katz(X, .05, 2, exist[i].node1, exist[i].node2));
  }
  sort_scores(exist, scores);
  filename = "SampleScores/origional_scores_KANTZ-" + SampleAlgor;
  write_output(filename, exist, scores);

  filename.clear();
  scores.clear();
    
  return;
 
}

#endif