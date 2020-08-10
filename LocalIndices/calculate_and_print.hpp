#ifndef CALCULATE_AND_PRINT
#define CALCULATE_AND_PRINT

//Prints all nonexist edges with their score
void histogram(A_Network *X, vector<Edge> *nonexist)
{
    cout << "Starting histogram\n";
    vector<float> score;
    vector<Edge> net;
    Edge mye;
    ofstream os("test.csv");
    int n = 0;

    
    //get all the edges
    for(int i = 0; i < X->size(); i++)
    {
        for(int j = 0; j < X->at(i).ListW.size(); j++)
        {
            if(X->at(i).ListW[j].first < X->at(i).Row)
            {
                mye.node1 = X->at(i).Row;
                mye.node2 = X->at(i).ListW[j].first;
                mye.edge_wt = 1;
                net.push_back(mye);   
            }
        }
    }

    score.clear();
    score.resize(net.size(), 0);

    //Get all network node CN
    for(int i = 0; i < net.size(); i++)
    {
        score[i] = common_neighbours(X, net.at(i).node1, net.at(i).node2);
    }

    sort_scores(net, score);

    for(int i = 0; i < net.size(); i++)
    {
        n++;
        if(i < net.size()-1 && score.at(i+1) != score.at(i) ) 
        {
            os << score.at(i) << "," << n << endl;
            n = 0;
        }
        
    }

    score.clear();
    net.clear();
    score.resize(nonexist->size(), 0);

    n = 0;
    //nonexistent nodes
    for(int i = 0; i < nonexist->size(); i++)
    {
        score[i] = common_neighbours(X, nonexist->at(i).node1, nonexist->at(i).node2);
    }

    sort_scores(*nonexist, score);

    for(int i = 0; i < nonexist->size(); i++)
    {
        n++;
        if(i < nonexist->size()-1 && score.at(i+1) != score.at(i) ) 
        {
            os << score.at(i) << "," << n << endl;
            n = 0;
        }
        
    }
    
}

#endif