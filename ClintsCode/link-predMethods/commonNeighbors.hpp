#ifndef COMMONNEIGHBORS_HPP
#define COMMONNEIGHBORS_HPP
using namespace std;

template<class myType>
vector<int> commonNeighbors(vector<Edge> *missing, A_Network *X, string alg, vector<myType> &predictedEdges, int threshold)
{
    int_string edgeScore;//used to add edges to the edgescore array
    vector<int_string> edgeScores;//used to write the predicted edges to a file
    string edgeSet;//used with the edgeScore variable
    ofstream output("results/predicated/" + alg);//used to write the predicted missing edges for a threshold
    int score = 0;
    vector<int> scores;
    int n1, n2, k, l, cn;//k and l represent the indexes for the neighbors for node1 and node2. cn represents the common neighbors
    for(int i = 0; i < missing->size(); i++){
        score = 0;//resetting the score, which represents the number of common neighbors
        n1 = missing->at(i).node1, n2 = missing->at(i).node2;//getting the missing edges and doing a common neighbor count
        k =0, l =0;//represent the neighbors in n1's and n2's 
        while(k < X->at(n1).ListW.size() && l < X->at(n2).ListW.size())//while we are still in both lists for node1 and node2
        {
            if(X->at(n1).ListW[k].first < X->at(n2).ListW[l].first){k++;}//if the node in node1's list is less than the node in node2's list
            else if(X->at(n1).ListW[k].first > X->at(n2).ListW[l].first){l++;}//if the node in nodes2's list is less than the node in node1's list
            else{//common neighbor
                score ++;
                k++;//go to the next index for node1's list
                l++;//go to the next index for node2's list
            }
        }
        edgeSet = to_string(missing->at(i).node1) + " " + to_string(missing->at(i).node2);//adding the string representation of the edge to edgeSet
        edgeScore.first = score;//getting the common neighbor count
        edgeScore.second = edgeSet;//getting the string of the edge
        edgeScores.push_back(edgeScore);//adding the edge score, which contains the number of common neighbors and the edge
        scores.push_back(score);//pushing back the score
        if(score >=threshold){predictedEdges.push_back(edgeScore);}//add the desired score to the predictedEdges array
    }
    //cout <<"number of predicted edges from common neighbors: " << predictedEdges.size() << endl;
    //insertionSort(&edgeScores);//sorting the scores
    quicksort(predictedEdges, 0, predictedEdges.size()-1);
    //insertionSort(&predictedEdges);
    //radixsort(&predictedEdges);
    //cout << "last index for common neighbors " << predictedEdges[predictedEdges.size()-1].first << endl;
    for(int i =predictedEdges.size() -1; i > -1; i--){
        output << predictedEdges[i].first <<" "<<predictedEdges[i].second <<endl;//writing the sorted scores to a file
    }
    output.close();
    return scores;
}

#endif