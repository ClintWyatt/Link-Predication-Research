#ifndef PERCENTAGE_HPP
#define PERCENTAGE_HPP

using namespace std;

int getIndex(vector<int> &scores, vector<int_string> &predictedEdges, int threshold)
{
   int indexCount = 0;
   for(int i = predictedEdges.size() -1; i > -1; i--)
   {
       if(predictedEdges[i].first >= threshold){indexCount++;}//if we are not at the threshold yet
       else{break;}//break the loop
   }
   return indexCount;
}

//method will be used to get the same predicted edges size of values for AA, RA, and katz as common neighbors
template <class myType>
vector<myType> setPredictedEdges(vector<myType> & predictedEdges, int index)
{
    vector<myType> finalPredictedEdges;
    myType _index;
    for(int i = predictedEdges.size()-1; i > (predictedEdges.size()-1) - index; i--)
    {
        _index.first = predictedEdges[i].first;
        _index.second = predictedEdges[i].second;
        finalPredictedEdges.push_back(_index);
    }
    return finalPredictedEdges;
}

#endif