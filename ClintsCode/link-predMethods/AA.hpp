#ifndef AA_HPP
#define AA_HPP



vector<float> AA(vector<Edge> *missing, vector<double_string> & predictedMissing, A_Network *X)
{
    float score;//represents the score of edge
    vector<float> AAscores;//represents AA scores
    double_string index; //used to add elements to the predictedMissing array
    string edge; //used to represent the edge of the score
    int n1, n2, k, l, cn;//k and l represent the indexes for the neighbors for node1 and node2. cn represents the common neighbors
    for(int i = 0; i < missing->size(); i++)
    {
        score = 0.0;//resetting the score
        cn =0; //resetting the number of common neighbors
        n1 = missing->at(i).node1, n2 = missing->at(i).node2;//getting the missing edges and doing a common neighbor count
        k =0, l =0;//represent the neighbors in n1's and n2's 
        while(k < X->at(n1).ListW.size() && l < X->at(n2).ListW.size())//while we are still in both lists for node1 and node2
        {
            if(X->at(n1).ListW[k].first < X->at(n2).ListW[l].first){k++;}//if the node in node1's list is less than the node in node2's list
            else if(X->at(n1).ListW[k].first > X->at(n2).ListW[l].first){l++;}//if the node in nodes2's list is less than the node in node1's list
            else//if there is a common neighbor
            {
                if(X->at(X->at(n1).ListW[k].first).ListW.size() >1)//if the common neighbors list is connected to more than 1 node (log(1) =0)
                {
                    //cout << "degree of node being added for: " <<X->at(n1).ListW[k].first <<" is " << X->at(X->at(n1).ListW[k].first).ListW.size();
                    score += 1.0/log(X->at(X->at(n1).ListW[k].first).ListW.size());//adding to the score
                    //cout <<" With value " << 1/log(X->at(X->at(n1).ListW[k].first).ListW.size()) << endl;
                }
                k++;//go to the next index for node1's list
                l++;//go to the next index for node2's list
                cn++;//increment the number of common neighbors
            }
        }
        AAscores.push_back(score);
        edge = to_string(n1) + " " + to_string(n2);
        index.first = score;
        index.second = edge;
        predictedMissing.push_back(index);
    }
    //insertionSort(&AAscores);//sort the scores for easier output for excell
    quicksort(predictedMissing, 0, predictedMissing.size()-1);
    //insertionSort(&predictedMissing);

    //count the number of different bins and multiply the total number of bins by the percentage. The result will be the number of bins to test

    return AAscores;
}
#endif