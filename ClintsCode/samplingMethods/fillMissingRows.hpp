#ifndef FILLMISSINGROWS_HPP
#define FILLMISSINGROWS_HPP
using namespace std;

void missingRows(A_Network *S, A_Network *X, int size, vector<Edge> *missing, vector<int> *missingNodes)
{
    int_double neighbor;//used to add neighbors to empty sample rows
    int index;//used to loop through each row of the origional network (A_Network *X)
    bool found; //used to represent whether a that is not in the sample graph is found.
    vector<int> missingEdgeNode;//represents a node (in a missing edge) that corresponds to a empty row for the sample network

    for(int i =0; i < missing->size(); i++)
    {
        if(S->at(i).ListW.size() == 0)
        {
            for(int j = 0; j < X->at(i).ListW.size(); j++)//going through the origional network and adding nodes to the empty row. The nodes that can be added are
            //green and red, not white. 
            {
                found = false;
                for(int a =0; a < missing->size(); a++)//finding the missing edges that correspond to this missing row
                {
                    if(missing->at(a).node1 == i){missingEdgeNode.push_back(missing->at(a).node2);}//if the missing row is part of a missing edge
                    else if (missing->at(a).node2 == i){missingEdgeNode.push_back(missing->at(a).node1);}
                }
                for(int k =0; k < missingNodes->size(); k++)//looping through all the white nodes and checking if they are in the origional networks' row.
                {
                    if(X->at(i).ListW[j].first == missingNodes->at(k))//if a white node is in the original networks row
                    {
                        found = true;
                        break;//go to the next node in the row of the origional network
                    }
                }
                if(found == false)
                {
                    for(int k =0; k < missingEdgeNode.size(); k++)
                    {
                        if(missingEdgeNode[k] == X->at(i).ListW[j].first)//if a white node is in the original networks row
                        {
                            found = true;
                            break;//go to the next node in the row of the origional network
                        }
                    }
                }
                if(found == false)
                {
                    neighbor.first = X->at(i).ListW[j].first;
                    neighbor.second = X->at(i).ListW[j].second;
                    S->at(i).ListW.push_back(neighbor);//adding a neighbor to the empty row in the sample network that was a green/red node from the snowball algorithm.
                } 
            }
            missingEdgeNode.clear();
        }
    }
}

#endif