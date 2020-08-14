#ifndef COMMONNEIGHBORS_HPP
#define COMMONNEIGHBORS_HPP

void commonNeighbors(vector<Edge> *missing, A_Network *X, string alg){
    int_string edgeScore;
    vector<int_string> edgeScores;
    string edgeSet;
    ofstream output("results/" + alg);
    int score = 0;
    vector<int> scores;
    int n1, n2, k, l, cn;//k and l represent the indexes for the neighbors for node1 and node2. cn represents the common neighbors
    for(int i = 0; i < missing->size(); i++){
        score = 0;//resetting the score, which represents the number of common neighbors
        n1 = missing->at(i).node1, n2 = missing->at(i).node2;//getting the missing edges and doing a common neighbor count
        k =0, l =0;//represent the neighbors in n1's and n2's 
        while(k < X->at(n1).ListW.size() && l < X->at(n2).ListW.size()){//while we are still in both lists for node1 and node2
            if(X->at(n1).ListW[k].first < X->at(n2).ListW[l].first){k++;}//if the node in node1's list is less than the node in node2's list
            else if(X->at(n1).ListW[k].first > X->at(n2).ListW[l].first){l++;}//if the node in nodes2's list is less than the node in node1's list
            else{//common neighbor
                score ++;
                k++;//go to the next index for node1's list
                l++;//go to the next index for node2's list
            }
        }
        edgeSet = to_string(missing->at(i).node1) + "-" + to_string(missing->at(i).node2);
        edgeScore.first = score;
        edgeScore.second = edgeSet;
        edgeScores.push_back(edgeScore);
        scores.push_back(score);
    }

    insertionSort(&edgeScores);//sorting the scores
    for(int i =scores.size() -1; i > -1; i--){
        output << edgeScores[i].first <<" "<<edgeScores[i].second <<endl;//writing the sorted scores to a file
    }
    output.close();
}

#endif