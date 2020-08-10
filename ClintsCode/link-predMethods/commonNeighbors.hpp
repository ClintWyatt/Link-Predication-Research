#ifndef COMMONNEIGHBORS_HPP
#define COMMONNEIGHBORS_HPP

int commonNeighbors(int node1, int node2, A_Network *X)
{
    vector<int> commonN;
    int commonCount =0;
    for(int i =0; i < X->at(node1).ListW.size(); i++)
    {
        for(int j =0; j < X->at(node2).ListW.size(); j++)
        {
            if(X->at(node2).ListW[j].first == X->at(node1).ListW[i].first)
            {
                commonCount++;
                break;
                commonN.push_back(X->at(node2).ListW[j].first);
            }
        }
    }

    return commonCount;
}

#endif