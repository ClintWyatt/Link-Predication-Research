//INPUT HEADERS
#include "translate_from_input.hpp"
#include "input_to_network.hpp"
#include "structure_defs.hpp"
#include "ADJ/set_opposite_index.hpp"

//OUTPUT HEADERS
#include "printout_network.hpp"
#include "printout_others.hpp"

//Header
#include "EliminationGame.hpp"

#include "ADJ/degree_centrality.hpp"

//Link Prediction
//No need to give directory since it is already linked::::SB
#include "detach_edges.hpp"
#include "nonexist_links.hpp"
#include "compute_precision_recall.hpp"
#include "universal_func.hpp"
#include "get_scores.hpp"
#include "calculate_and_print.hpp"
#include "sampling.hpp"

/*** All Headers Required From ESSENS **/

using namespace std;

int main(int argc, char *argv[])
{
    clock_t q, q1, q2, t;
    double startx, endx, startx1, endx1;

    /***** Preprocessing to Graph (GUI) ***********/
    q = clock();
    //Check if valid input is given
    if (argc < 3)
    {
        cout << "INPUT ERROR:: At least 2 inputs required. First: filename \n Second: Filetypes: 1:node_node_wt 2:node_wt_node 3:node_node 4:node_node (Only option 1 is active now) \n Third: Name of new file \n Fourth: Name of Map file\n";
        return 0;
    }
    //Check to see if file opening succeeded
    ifstream the_file(argv[1]);
    if (!the_file.is_open())
    {
        cout << "INPUT ERROR:: Could not open file\n";
    }

    A_Network X;//adjacency list. Template is from network_defs.hpp
    int nodes = -1;
    map_int_st revmap;

    //Proces File if Option Given by
    if (argc == 5)
    {
        // Preprocess Nodes to Numbers
        //Stores file in argv[3]: store map in argv[4]
        //Vertices start from 0
        int type = atoi(argv[2]);
        translate_input(argv[1], type, argv[3], argv[4]);//from translate_from_input.hpp

        //Remove Duplicate Edges and Self Loops; Create Undirected Graphs
        // process_to_simple_undirected();
        q = clock() - q;
        cout << "Total Time for Preprocessing: " << ((float)q) / CLOCKS_PER_SEC << "\n";

        /***** Preprocessing to Graph (GUI) ***********/

        /******* Read Graph (GUI) and Create Reverse Map*****************/
        //Obtain the list of edges.
        q = clock();
        readin_network(&X, argv[3], nodes);//from input_to_network.hpp

        //Create Reversemap

        nodes = X.size();
        create_map(argv[4], &revmap);//from translate_from_input.hpp

        q = clock() - q;
        cout << "Total Time for Reading Network: " << ((float)q) / CLOCKS_PER_SEC << "\n";
        /**** Read Graph (GUI) ***********/
    }
    else //no need to process the graph
    {
        /******* Read Graph (GUI) and Create Reverse Map*****************/
        //Obtain the list of edges.
        q = clock();
        readin_network(&X, argv[1], nodes);//from input_to_network.hpp

        nodes = (int)X.size();
        create_map(nodes, &revmap);//from translate_from_input.hpp
        q = clock() - q;
        cout << "Total Time for Reading Network: " << ((float)q) / CLOCKS_PER_SEC << "\n";
        /**** Read Graph (GUI) ***********/
    }
    //Mark index of reverse edges
    set_opposite_index(&X);
    //print_detail(X);
    //print_edgelist(X);
    int it = 1;
    int p;                  //percentage of edges removed
    int k_dist;             //distance between neighbors to be considered for missing edges
    vector<int_int> D;      //keeps track of degree of each vertex
    vector<Edge> nonexist;  //heap storing scores of missing edges
    vector<Edge> del_edges; //edges that were deleted
    //Run Link Predication algorithms

    A_Network S;           //sample network. Network_defs.hpp
    int k = X.size() / 10; //sample network size
    
    XSN(&S, &X, k);
    writeNetwork(&X, &S, "XSN");
    //write_network(&X, "origionalNetwork.txt");
    //write_network(&S, "sampleNetworkXSN.txt");
    //cout <<"Printing the sample network" << endl;
    //printGraph(&X);
    //printGraph(&S);
    //minusIntersection(&S, &X);//getting unique edges for network X
    //printUnique(&S);
    
    /*computing scores based off of vertex pairs in the sample graph!*/
    sample_scores(&S, &X, "XSN");

    //uniqueScore(&X, "XSN");
    //sample_scores(&S, &X, "XSN");//from sampling.hpp

    random_walk(&S, &X, k);
    //edgeComparison(&S, &X);
    //printGraph(&S);
    //completeGraph(&S);
    //minusIntersection(&S, &X);//getting unique edges for network X//cout << "printing missing edges of network s" << endl;
    //print_missingEdges(&S);//works
    //nonAdjacent(&S, &X);
    sample_scores(&S, &X, "RW");
    //printUnique(&X);
    //uniqueScore(&X, "RW");
    //cout << "printing missing edges from sample and origional network" << endl;
    //missing_orig_sample(&X);
    //sample_scores(&S, &X, "RW");

    random_node(&S, &X, k);
    //minusIntersection(&S, &X);//getting unique edges for network X
    //printUnique(&X);
    //uniqueScore(&X, "RN");
    sample_scores(&S, &X, "RN");
    //Get number of edges for k size of edges
    k = total_edges(&X)/2; //from detatach_edges.hpp    
    cout << "Total num edges: " << k << endl;

    random_edge(&S, &X, k);
    //edgeComparison(&S, &X);
    //minusIntersection(&S, &X);//getting unique edges for network X
    //printUnique(&X);

    //uniqueScore(&X, "RE");
    sample_scores(&S, &X, "RE"); 
    
    forest_fire(&S, &X, k);
    //edgeComparison(&S, &X);
    //minusIntersection(&S, &X);//getting unique edges for network X
    //uniqueScore(&X, "FF");
    //cout <<"here" << endl;
    sample_scores(&S, &X, "FF");
    //print_detail(S);

    //Always send containers as pointer:::::SB
    /*for(int i = 0; i < it; i++)
    {
        //remove p% of edges
        p=1;
        k_dist=2;
        detach_edges(&X,&D,&del_edges,p);
        cout << "Getting K-distance edges\n";
        find_k_dist_nonedge(&X, &nonexist, k_dist);
        //cout<< "Number of nonexistent edges: " << nonexist.size() << "\n";
        //print_heap(&nonexist);
        //print_edges(nonexist);
        //print_edges(del_edges);
        compute_first_precision_recall(X, nonexist, &del_edges);
        //AA_helper(X, nonexist, del_edges, D);
    }*/

    //histogram(&X, &nonexist);

    //    int add_edges=elimination_game_max_deg(&X);

    return 0;
} //end of main

//==========================================//
