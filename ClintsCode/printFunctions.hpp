#ifndef PRINTFUCNCTIONS_HPP
#define PRINTFUNCTIONS_HPP

void printNetwork(A_Network *X)
{
    
    for(int i =0; i < X->size(); i++)
    {
        cout <<"Row " << X->at(i).Row <<"->";
        for(int j =0; j < X->at(i).ListW.size(); j++)
        {
            cout << X->at(i).ListW[j].first << " ";
        }
        cout << endl;
    }
}

void writeBothNetworks(A_Network *X, A_Network *S, string alg)
{
    ofstream origional("networks/origional.txt");
    ofstream sample(alg+"_sample.txt");

    for(int i =0; i < X->size(); i++)
    {
        origional << X->at(i).Row << ": ";
        sample << S->at(i).Row <<": ";
        for(int j =0; j < X->at(i).ListW.size(); j++)
        {
            origional <<X->at(i).ListW[j].first << " ";
        }
        origional <<endl;
        for(int j =0; j < S->at(i).ListW.size(); j++)
        {
            sample << S->at(i).ListW[j].first << " ";
        }
        sample << endl;
    }
    origional.close();
    sample.close();
}

void writeSample(A_Network *S, string alg)
{
    ofstream sample("networks/"+alg+"_sample.txt");

    for(int i =0; i < S->size(); i++)
    {
        sample << S->at(i).Row <<": ";
        for(int j =0; j < S->at(i).ListW.size(); j++)
        {
            sample << S->at(i).ListW[j].first << " ";
        }
        sample << endl;
    }
    sample.close();
}

void writeMissing(vector<Edge> *missing, vector<Edge> *missing_S, string alg)
{
    ofstream missingE("results/missingEdges-" +alg + ".txt");//writting the missing edges that are in the origional graph, but missing in the sample graph to a text file
    ofstream missingS("results/sampleMissing-" + alg + ".txt");//writing the missing nodes in the sample graph to a text file
    for(int i =0; i < missing->size(); i++)
    {
        missingE << missing->at(i).node1 << " " << missing->at(i).node2 << endl;
    }
    for(int i =0; i < missing_S->size(); i++)
    {
        missingS << missing_S->at(i).node1 << " "<< missing_S->at(i).node2 <<endl;
    }
    missingE.close();
    missingS.close();
}
#endif