#ifndef AA_HPP
#define AA_HPP


//1/log Kz means that 

vector<float> AA(vector<Edge> *missing, string alg, A_Network *X)
{
    ofstream output("results/"+ alg + "AA.txt");
    ofstream predicted("results/predicated/" + alg + "AA.txt");
    float score;//represents the 
    vector<float> AAscores;//represents AA scores
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
                    score += 1/log(X->at(X->at(n1).ListW[k].first).ListW.size());//adding to the score
                    //cout <<" With value " << 1/log(X->at(X->at(n1).ListW[k].first).ListW.size()) << endl;
                }
                k++;//go to the next index for node1's list
                l++;//go to the next index for node2's list
                cn++;//increment the number of common neighbors
            }
        }
        AAscores.push_back(score);
    }
    insertionSort(&AAscores);//sort the scores for easier output for excell
    for(int i = AAscores.size() -1; i > -1; i--)
    {
        if(AAscores[i] > 6.22)//if the score is in the higher bins
        {
            predicted << AAscores[i] <<endl;
        }
        output << AAscores[i] << endl;//write the scores to a file
    }
    output.close();//close the file
    predicted.close();//close the file
    return AAscores;
}
#endif