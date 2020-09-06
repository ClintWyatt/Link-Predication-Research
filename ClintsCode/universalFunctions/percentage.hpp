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
   
    /*
    int indexCount =0; 
    for(int i =0; i < predictedEdges.size(); i++)
    {
        if(predictedEdges[i].first < threshold){indexCount++;}
        else{break;}
    }
    return indexCount;
    */
}

//method will be used to get the same predicted edges size of values for AA, RA, and katz as common neighbors

void setPredictedEdges(vector<double_string> & predictedEdges, int index)
{
    if(index >0 && index != predictedEdges.size())//if the threshold is not the lowest value bin and is not greater than the highest bin
    {
        vector<double_string> finalPredictedEdges;
        double_string _index;
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