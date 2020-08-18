#ifndef PERDICTEDSCORE_HPP
#define PERDICTEDSCORE_HPP

using namespace std;

void threeMetrics(vector<int_string> &predictedEdges, vector<Edge> &missing, string predMethod)
{
    ofstream results("results/correctMissingEdges/"+predMethod+".txt");//used to write the correct missing edges to a text file
    int pe = predictedEdges.size(); //perdicted missing edges
    int ce = 0; //correctly perdicted edges
    float precision;
    string edge;//used to represent the edge in for the real missing edges
    for(int i =0; i < missing.size(); i++)
    {
        edge += to_string(missing[i].node1) + " " + to_string(missing[i].node2);
        for(int j =0; j < predictedEdges.size(); j++)
        {
            if(edge == predictedEdges[j].second)//if the 
            {
                ce++;
                results << edge << endl;
                break;
            }
        }
        edge.clear();
    }
    precision = float(ce) / float(pe);
    cout << precision << endl;
    results.close();
}

void f1Value()
{

}

#endif