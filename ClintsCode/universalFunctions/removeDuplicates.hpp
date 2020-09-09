#ifndef REMOVEDUPLICATES_HPP
#define REMOVEDUPLICATES_HPP

//method is used since some graphs have duplicate edges for some unknown reason
void removeDuplicateEdges(A_Network & S)
{
    vector<int_double> listWcopy;
    int_double edge;
    for(int i =0; i < S.size(); i++)
    {
        for(int j =0, k =1; j < S[i].ListW.size(); j++, k++)
        {
            if(k == S[i].ListW.size())//if we are the last index, see if we can add the last index
            {
                if(S[i].ListW[j-1].first != S[i].ListW[j].first)//if the last index and the second to last index are not the same
                {
                    edge.first = S[i].ListW[j].first;
                    edge.second = S[i].ListW[j].second;
                    listWcopy.push_back(edge);
                }
                break;
            }
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