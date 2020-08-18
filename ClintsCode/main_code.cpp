//INPUT HEADERS
#include "translate_from_input.hpp"
#include "input_to_network.hpp"
#include "structure_defs.hpp"
#include "ADJ/set_opposite_index.hpp"

//OUTPUT HEADERS
#include "printout_network.hpp"
#include "printout_others.hpp"

//Header

#include "ADJ/degree_centrality.hpp"

//Link Prediction
//No need to give directory since it is already linked::::SB
#include "universalFunctions/totalEdges.hpp"
#include "printFunctions.hpp"
#include "samplingMethods/missingEdges.hpp"
#include "sorting.hpp"
#include "samplingMethods/xsn.hpp"
#include "link-predMethods/commonNeighbors.hpp"
#include "link-predMethods/AA.hpp"
#include "link-predMethods/katz.hpp"
#include "samplingMethods/randomEdge.hpp"
#include "samplingMethods/randomEdge.hpp"
#include "samplingMethods/forestFire.hpp"
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
   
    set_opposite_index(&X);
    //print_detail(X);
    //print_edgelist(X);
    string alg; //represents the algorithm that is used for writing the sample network graphs
    int it = 1;
    int p;                  //percentage of edges removed
    int k_dist;             //distance between neighbors to be considered for missing edges
    vector<int> scores;     //represents the scores from the link prediction algorithms such as common neighbors, AA, Kantz, etc.
    vector<Edge> sampleMissing; //represents the missing edges for the sample network against itself. Represent the predicted edges. 
    vector<Edge> missing; //array representing missing edges that are in the origional network, but not the sample network
    A_Network S;           //sample network. Network_defs.hpp
    int k = X.size() / 20; //sample network size
    cout <<"running snowball" <<endl;
    snowball(&X, &S, k, &missing);//snowball algorithm
    missingEdges(&X, &S, &missing);//getting the edges that are in the origional network, but not the sample network
    writeBothNetworks(&X, &S, "networks/XSN");//writing networks X and S to output files
    missingSample(&S, &sampleMissing);//getting the edges that are missing in the sample against the sample graph
    writeMissing(&missing, &sampleMissing, "xsn");//writing the actual missing edges and predicted missing edges to text files
    cout << "running common neighbors" << endl;
    commonNeighbors(&sampleMissing, &S, "xsn-cn.txt");

    cout <<"running AA" <<endl;
    AA(&missing, "xsn", &S);
    cout << "running katz"<<endl;
    katz(&S, &missing, "XSN");
    missing.clear();//clearing the array for actual missing edges 
    sampleMissing.clear();//clearing the array representing the predicted missing edges
    k = totalEdges(&X);
    //k += k * (1/4);
    forest_fire(&S, &X, k, &missing);
    missingEdges(&X, &S, &missing);
    writeSample(&S, "FF");
    missingSample(&S, &sampleMissing);
    writeMissing(&missing, &sampleMissing, "FF");

    return 0;   
}