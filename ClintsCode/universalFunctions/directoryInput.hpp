#ifndef DIRECTORYINPUT_HPP
#define DIRECTORYINPUT_HPP

#include <iostream>
#include <vector>
#include <filesystem>
#include <string.h>
#include <string>
#include <unistd.h>

using namespace std;

void readManyFiles(char *output, char *map)
{
    vector<int_string> predictedEdges;//used for the predicted edges for common neighbors
    vector<double_string> _predictedEdges;//used for the predicted edges for AA, RA, and katz
    vector<int> intScores;//represents the total number of scores for the common neighbors algorithm        
    vector<float> AAScores, RAScores, katzScores, cnScores, tmp; //represents the scores from the link prediction algorithms such as common neighbors, AA, Kantz, etc.
    vector<Edge> sampleMissing; //represents the missing edges for the sample network against itself. Represent the predicted edges. 
    vector<Edge> missing; //array representing missing edges that are in the origional network, but not the sample network
    namespace fs = std::filesystem;
    A_Network X, S;//sample and origional network
    int nodes;
    map_int_st revmap;
    clock_t q, q1, q2, t;
    int n, k, threshold;
    char buffer[200];//used to get the name of the file
    string path = "../test_networks/other";//path for the files to be read in
    bzero(buffer, 200);//zeroing out the buffer
    float precisionAvg, recallAvg, f1Avg;  
    AAScores.resize(3);
    RAScores.resize(3);
    cnScores.resize(3);
    katzScores.resize(3);
    ofstream outputFile("results/bigFile.csv");
    outputFile <<"NAME" <<" "<<"RA" <<" "<<"AA" <<" " <<"CN" <<" "<<"KATZ"<<endl;
    int numLoops = 5;
    threshold = 1;
    int avgEdges;//average number of verticies
    int numNodes;//the number of nodes for each graph
    for(const auto & entry : fs::directory_iterator(path))//going through each file in the directory
    {
        srand(time(NULL));
        AAScores.assign(3, 0.0);
        RAScores.assign(3, 0.0);
        cnScores.assign(3, 0.0);
        katzScores.assign(3, 0.0);
        nodes = -1;
        avgEdges = 0;
        //cout << entry.path() << endl;
        string path_string(entry.path());//using the string contructor to convert the path into a string
        n = path_string.length();//getting the length of the string
        memcpy(buffer, path_string.c_str(), n);
        cout << "running metric simulations for "<< buffer << endl;
        // Preprocess Nodes to Numbers
        //Stores file in argv[3]: store map in argv[4]
        //Vertices start from 0
        translate_input(buffer, 1, output, map);//from translate_from_input.hpp

        /***** Preprocessing to Graph (GUI) ***********/

        /******* Read Graph (GUI) and Create Reverse Map*****************/

        readin_network(&X, output, nodes);//from Core/basic_io/format/input/level2/input_to_network.hpp
        //Create Reversemap

        nodes = X.size();
        create_map(map, &revmap);//from translate_from_input.hpp
        set_opposite_index(&X);
        k = totalEdges(&X);//getting the total edges in the origional graph, which will be used for the forestfire algorithm
        //writeOneNetwork(X, "networks/origional.txt");//used to validate that each file has a different origional graph
        for(int i =0; i < numLoops; i++)
        {
             _predictedEdges.clear();
            predictedEdges.clear();
            missing.clear();//clearing the array for actual missing edges 
            sampleMissing.clear();//clearing the array representing the predicted missing edges
            forest_fire(&S, &X, k, &missing);//forestfire algorithm
            k = totalEdges(&S);//getting the total edges in the sample graph. This was used to see if there was a relationship between the number of edges and the f1 score of
            avgEdges+=k;
            missingEdges(&X, &S, &missing);//getting the real missing edges that are in the origional graph but not the sample graph
            writeSample(&S, "FF");//writing the sample network from the forestfire algorithm
            missingSample(&S, &sampleMissing);//getting the missing edges in the sample against itself
            intScores = commonNeighbors(&sampleMissing, &S, "FF-cn.txt", predictedEdges, threshold);//n is a threshold and all scores >=n will be written to the predictedEdges array
            k = getIndex(intScores, predictedEdges, threshold);//Gets the size up to the threshold for common neighbors. k will be used for katz, AA, and RA.
            tmp = twoMetrics(predictedEdges, missing);
            cnScores[0]+=tmp[0], cnScores[1]+=tmp[1];//adding the values togeather

            AA(&sampleMissing, _predictedEdges, &S);
            setPredictedEdges(_predictedEdges, k);
            tmp = twoMetrics(_predictedEdges, missing);
            AAScores[0]+=tmp[0], AAScores[1]+=tmp[1];//adding the values togeather
            _predictedEdges.clear();

            katz(&S, &sampleMissing, _predictedEdges, "FF-katz");
            setPredictedEdges(_predictedEdges, k);
            tmp = twoMetrics(_predictedEdges, missing);
            katzScores[0]+=tmp[0], katzScores[1]+=tmp[1];//adding the values togeather

            _predictedEdges.clear();

            RA(&sampleMissing, _predictedEdges, &S);
            setPredictedEdges(_predictedEdges, k);
            tmp = twoMetrics(_predictedEdges, missing);
            RAScores[0]+=tmp[0], RAScores[1]+=tmp[1];//adding the values togeather
            //usleep(1234567);
            sleep(1);
        }
        
        //cout <<"predicted size: " << _predictedEdges.size() << " missing size: " << missing.size() <<endl;
        numNodes = S.size();//getting the number of nodes in the graph
        avgEdges/=numLoops;//getting the average number of edges
        //cout << "total cn scores: " << cnScores[0] << " " << cnScores[1] <<endl;
        outputFile << buffer <<RAScores[0]/numLoops << "\t\t" <<AAScores[0]/numLoops << "\t"<<cnScores[0]/numLoops << "\t" << katzScores[0]/numLoops <<"\n";
        outputFile << "number of nodes: " << numNodes <<RAScores[1]/numLoops << "\t" <<AAScores[1]/numLoops << "\t"<<cnScores[1]/numLoops << "\t" << katzScores[1]/numLoops <<"\n";
        outputFile << "average edges: " << avgEdges <<"\t\t\t\t\t\t\t\t\t" <<"\t"<<f1Value(RAScores[0]/numLoops, RAScores[1]/numLoops) << "\t" <<
        f1Value(AAScores[0]/numLoops, AAScores[1]/numLoops)<<"\t"<< f1Value(cnScores[0]/numLoops, cnScores[1]/numLoops) << 
        "\t" << f1Value(katzScores[0]/numLoops, katzScores[1]/numLoops) <<"\n";
        outputFile << endl;
        X.clear();
        memset(buffer, 0, sizeof(buffer));//resseting the buffer
        
    }
    outputFile.close();
}

#endif