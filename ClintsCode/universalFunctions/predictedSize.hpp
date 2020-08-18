#ifndef PREDICTEDSIZE_HPP
#define PREDICTEDSIZE_HPP

using namespace std;

float getPercentage(vector<int> &scores, vector<int_string> &predictedEdges)
{
    float m1 = (float) predictedEdges.size();
    float m2 = (float) scores.size();
    float percentage = m1 / m2;
    return percentage;
}

#endif