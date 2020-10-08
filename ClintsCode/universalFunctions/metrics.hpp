#ifndef PERDICTEDSCORE_HPP
#define PERDICTEDSCORE_HPP

using namespace std;
float f1Value(float precision, float recall);

template <class myType>
void threeMetrics(vector<myType> &predictedEdges, vector<Edge> &missing, string predMethod)
{
    ofstream results("results/correctMissingEdges/"+predMethod+".txt");//used to write the correct missing edges to a text file
    ofstream metrics;
    metrics.open("results/metricScores/"+predMethod+".txt", ofstream::out | ofstream::app);
    int pe = predictedEdges.size(); //perdicted missing edges
    int ce = 0; //correctly perdicted edges
    int oe = missing.size();//oe represents the actual missing edges.
    float precision;// ce divided by pe
    float recall; // ce diviede by oe
    float f1;
    string edge;//used to represent the edge in for the real missing edges
    //cout << predictedEdges.size() << endl;
    for(int i =0; i < missing.size(); i++)
    {
        edge += to_string(missing[i].node1) + " " + to_string(missing[i].node2);//represents the true missing edge
        for(int j =0; j < predictedEdges.size(); j++)
        {
            if(edge == predictedEdges[j].second)//if the predicted missing edge is the same as the true missing edge
            {
                ce++;
                results << edge << endl;
                break;
            }
        }
        edge.clear();
    }
    results.close();
    precision = float(ce) / float(pe);
    recall = float(ce) / float(oe);
    metrics << "Precision: "<< precision <<endl;
    metrics << "Recall " <<recall <<endl;
    metrics << "F1Value: "<<f1Value(precision, recall) <<endl;
    metrics <<endl;
    metrics.close();
}



float f1Value(float precision, float recall)
{
    return 2.0 * (precision * recall) / (precision + recall);
}

#endif