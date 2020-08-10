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

void writeNetwork(A_Network *X, A_Network *S, string alg)
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
#endif