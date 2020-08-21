#ifndef REMOVEDUPLICATES_HPP
#define REMOVEDUPLICATES_HPP

//method is used since some graphs have duplicate edges for some unknown reason
void removeDuplicateEdges(A_Network & S)
{
    vector<int_double> listWcopy;
    int_double edge;
    for(int i =0; i < S.size(); i++)
    {
        for(int j =0, k =1; k < S[i].ListW.size() -1; j++, k++)
        {
            if(S[i].ListW[j].first != S[i].ListW[k].first)//if both nodes are not equal to each other
            {
                edge.first = S[i].ListW[j].first;
                edge.second = S[i].ListW[j].second;
                listWcopy.push_back(edge);
            }
        }
        S[i].ListW = listWcopy;
        listWcopy.clear();
    }
}
#endif