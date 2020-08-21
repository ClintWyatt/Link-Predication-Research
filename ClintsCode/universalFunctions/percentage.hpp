#ifndef PERCENTAGE_HPP
#define PERCENTAGE_HPP
#include "sorting.hpp"
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

void setPredictedEdges(vector<float_string> & predictedEdges, int index, int threshold)
{
    if(threshold > 0)//if the threshold is greater than zero
    {
        vector<float_string> finalPredictedEdges;
        float_string _index;
        for(int i = predictedEdges.size()-1; i > (predictedEdges.size()-1) - index; i--)
        {
            _index.first = predictedEdges[i].first;
            _index.second = predictedEdges[i].second;
            finalPredictedEdges.push_back(_index);
        }

        predictedEdges.clear();
        for(int i = finalPredictedEdges.size() -1; i > -1;  i--)
        {
            predictedEdges.push_back(finalPredictedEdges[i]);
        }
    }
}

#endif