#ifndef XSN_HPP
#define XSN_HPP
#include "fillMissingRows.hpp"
#include "missingEdges.hpp"
using namespace std;

void snowball(A_Network *X, A_Network *S, int size, vector<Edge> *missing)
{
    /*data structures */

    /*bit vectors*/
    vector<int> green;//represents a set of nodes from the X network that are the sample nodes. Is represented as "green" nodes in the paper
    vector<int> red;//neighbors of the sample nodes (green nodes). Represented as "red" nodes in the paper. 
    vector<int> marked; //used to prevent duplicates in the red array
    vector<int> missingNodes; //used to represent the nodes thar were not added to the sample
    /*int_int vector*/
    vector<int_int> white;//nodes that are adjacent to the red nodes, but not the green nodes. They are unknown nodes and are
    //"white" nodes in the paper. 
    
    /*variables*/
    int max;//used for the maximum unknown nodes a red nodes has
    int maxIndex =0;//used when trying to determine which red node is next to the most white nodes
    int maxNeighbors;//represents the number of white nodes that are next to a red node, not a green node.
    int_int visitedNode;//represents a red node with the number of white nodes next to it.
    int index =0; //used to help get the index of the red array 

    /*snowball algorithm satart */
    S->clear();//erasing all contents of the S network
    red.resize(X->size(), 0);//creating a array that represents the neighbors green nodes,
    //initializing them all to zero. 
    marked.resize(X->size(), 0);
    srand(time(NULL));//starting random number generator
    int node = rand() % X->size(); //picking a random node to start from in the X network
    green.push_back(node); //adding the first random node to the sample nodes
    marked[node] = 1;//setting the index of the new added node to the sample nodes to 1
    //setting all the neighbors of the first green node to red nodes.
    for(int i =0; i < X->at(node).ListW.size(); i++)
    {
        red[X->at(node).ListW[i].first] = 1;//making the nodes that are adjacent to the green node red
    }

    while(green.size() <= size)
    {
        //from the sample neighbors (red neighbors), find a red neighbor that has the most nodes that are not in the red array
        for(int i =0; i < red.size(); i++)
        {
            maxNeighbors =0;//intiializing the maxNeighbors variable to 0. This represents white nodes adjacent to the red nodes
            if(red[i] == 1 && marked[i] == 0)//if the current node is a red node and not a green node itself
            {
                
                for(int j = 0; j < X->at(i).ListW.size(); j++)//Checking how many unkown nodes there are for the current red node
                {
                    index = X->at(i).ListW[j].first;
                    if(red[index] == 0 && marked[index] == 0)//if the neighbor has not been visited yet (white neighbor) and is not a green node
                    {
                        //cout << marked[index] << endl;
                        maxNeighbors++;
                    }
                }

                visitedNode.first = i;//setting neighbor of the sample to first 
                visitedNode.second = maxNeighbors;//setting the number of unknown nodes that are not adjacent to the sample neighbors set to second
                white.push_back(visitedNode);//adding a white node to the white vector
            }
        }
       
        max = -1; //setting the max 
        maxIndex = -1;//represents the node with the maximum unknown neighbors
        //finding out which node from the white set that has the most neighbors not in the sample. 
        for(int i =0; i < white.size(); i++)
        {
            if(white[i].second > max)
            {
                max = white[i].second;
                maxIndex = white[i].first;//setting the max index to the node with the most unknown neighbors
            }
        }

        if(maxIndex == 0){break;}//if the remaining white nodes cannot be found

        //add sample's neighbor with the most unknown nodes to the sample
        green.push_back(maxIndex);//adding the node with the most white neighbors to the sample nodes
        marked[maxIndex] = 1; //marking the green node that was added
        red[maxIndex] =0; //removing the new green node from the array of red nodes

        //set all of the white nodes that are adjacent to the new green node to red
        for(int i =0; i < X->at(maxIndex).ListW.size(); i++)
        {
            if(marked[X->at(maxIndex).ListW[i].first] == 0)//if the node is not green
            {
                red[X->at(maxIndex).ListW[i].first] = 1;
            }
        }
        white.clear();//resetting the white vector
    }

    /*
    cout<<"green nodes: "<< endl;
    for(int i=0; i < green.size(); i++)
    {
        cout << green[i]<< endl;
    }
    cout <<"Red nodes: " << endl;
    for(int i =0; i < red.size(); i++)
    {
        if(red[i] == 1){cout<<i<<endl;}
    }
    */
    //adding the red nodes to the green nodes list to make putting the sample graph togeather more simple. 
    
    for(int i =0; i < red.size(); i++)
    {
        if((red[i] == 1 /*|| red[i] == 2) && (marked[i] == 0)*/))//if the nodes are red/white and not green. 
            green.push_back(i);
        else if(red[i] == 0 && marked[i] == 0)
            missingNodes.push_back(i);//putting the node that is not in the sample into another array
        
    }
    
    sort(&green);
    ofstream whiteMissing("results/whiteNodes.txt");
    for(int i =0; i < missingNodes.size(); i++)
    {
        whiteMissing << missingNodes[i] << endl;
    }
    whiteMissing.close();
    /*
    int current = red.size();
    //now getting the unknown nodes that are 
    for(int i=0; i < current; i++)
    {
        if(red[i] == 1 && marked[i] == 0)//if the node is a neighbor of the green and not in the sample itself
        {
            for(int j =0; j < X->at(i).ListW.size(); j++)//going through the sampleNeighbor's nodes to see if any of them are unknown
            {
                if(red[X->at(i).ListW[j].first] == 0 && marked[X->at(i).ListW[j].first] == 0)
                {
                    green.push_back(X->at(i).ListW[j].first);//adding the unknown neighbor to green
                }
            }
        }
    }
    */
    //adding the sample nodes to the S network
    S->resize(X->size());//making the sample graph have as many rows as the origional graph
    for(int i =0; i < S->size(); i++)
    {
        S->at(i).Row = i;
    }

    //for adding nodes to the sample graph, add all nodes that are connected to red and green nodes. Create a induced subgraph of the sample nodes
    int_double neighbor;//used to add neighbors to the sample network

    int listw_index;//used to loop through the rows of the X network
    int greenIndex;//used to loop through the nodes from the result of the snowball algorithm

    //Try to prevent empty rows
    for(int i =0, j =0; i < X->size(); i++)
    {
        listw_index = 0;
        greenIndex = 0;
        if(i == green[j])//if the node in the snowball array is the same as the row in the x network
        {        
            j++;
            while(listw_index < X->at(i).ListW.size() && greenIndex < green.size())//comparing the nodes from the snowball algorithm with a row of the x network
            {
                if(green[greenIndex] < X->at(i).ListW[listw_index].first){greenIndex++;}
                else if(green[greenIndex] > X->at(i).ListW[listw_index].first){listw_index++;}
                else
                {
                    if(green[greenIndex] != i)//if the node in the snowball array is not the same as the row we are on in the s network
                    {
                        neighbor.first = X->at(i).ListW[listw_index].first;//neighbor.first is the node
                        neighbor.second = X->at(i).ListW[listw_index].second;//neighbor.second is the edge weight
                        S->at(i).ListW.push_back(neighbor);//adding the neighbor to the row on the sample network
                    }
                    greenIndex++;
                    listw_index++;
                }
                
            }
        }
   }
}

#endif