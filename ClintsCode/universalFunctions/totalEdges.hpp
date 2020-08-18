#ifndef TOTALEDGES_HPP
#define TOTALEDGES_HPP

int totalEdges(A_Network *X)
{
    int count;
    for(int i =0; i < X->size(); i++)
    {
        count += X->at(i).ListW.size();
    }
    return count /2;
}

#endif