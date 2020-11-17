#ifndef DIRECTORYINPUT_HPP
#define DIRECTORYINPUT_HPP

#include <iostream>
#include <vector>
#include <filesystem>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void changeDirectory(pid_t pid);
void runCommunity(pid_t pid);
void convert(pid_t pid);
void readManyFiles(char *output, char *map)
{
    /*vectors*/
    vector<int_string> predictedEdges;//used for the predicted edges for common neighbors
    vector<double_string> _predictedEdges;//used for the predicted edges for AA, RA, and katz
    vector<int> intScores;//represents the total number of scores for the common neighbors algorithm        
    vector<float> AAScores, RAScores, katzScores, cnScores, tmp; //represents the scores from the link prediction algorithms such as common neighbors, AA, Kantz, etc.
    vector<Edge> sampleMissing; //represents the missing edges for the sample network against itself. Represent the predicted edges. 
    vector<Edge> missing; //array representing missing edges that are in the origional network, but not the sample network
    A_Network X, S;//sample and origional network

    /*integers and floats */
    int nodes, n, k, threshold, avgEdges, numNodes;
    int numLoops = 10;
    float precisionAvg, recallAvg, f1Avg;  
    float lcs = 0.0; //local clustering score
    char buffer[200];//used to get the name of the file
    
    /*other variables */
    map_int_st revmap;
    namespace fs = std::filesystem;
    string path = "../test_networks/TINY_100K";//path for the files to be read in. Change this if you want to readin another directory
    ofstream outputFile("results/bigFile.txt");

    bzero(buffer, 200);//zeroing out the buffer
    AAScores.resize(3);
    RAScores.resize(3);
    cnScores.resize(3);
    katzScores.resize(3);
    tmp.resize(2);


    srand(time(NULL));
    threshold = 1;
    outputFile <<"NAME" <<" "<<"RA" <<" "<<"AA"<<" "<<"CN" <<" "<<"KATZ" << " "<<"Number-of-Nodes"<< " " << "Average-Edges" << " " << "lcs"<<endl;
    for(const auto & entry : fs::directory_iterator(path))//going through each file in the directory
    {
        AAScores.assign(3, 0.0);
        RAScores.assign(3, 0.0);
        cnScores.assign(3, 0.0);
        katzScores.assign(3, 0.0);
        nodes = -1;
        avgEdges = 0;

        string path_string(entry.path());//using the string contructor to convert the path into a string
        n = path_string.length();//getting the length of the string
        memcpy(buffer, path_string.c_str(), n);
        cout << "running metric simulations for "<< buffer << endl;

        // Preprocess Nodes to Numbers
        //Stores file in argv[3]: store map in argv[4]
        //Vertices start from 0
        translate_input(buffer, 1, output, map);//from translate_from_input.hpp. - this is where the file is opened

        /***** Preprocessing to Graph (GUI) ***********/

        /******* Read Graph (GUI) and Create Reverse Map*****************/

        readin_network(&X, output, nodes);//from Core/basic_io/format/input/level2/input_to_network.hpp
        //Create Reversemap

        nodes = X.size();
        create_map(map, &revmap);//from translate_from_input.hpp
        set_opposite_index(&X);
        removeDuplicateEdges(X);

        for(int i =0; i < numLoops; i++)
        {
            _predictedEdges.clear();
            predictedEdges.clear();
            missing.clear();//clearing the array for actual missing edges 
            sampleMissing.clear();//clearing the array representing the predicted missing edges
            k = totalEdges(&X);//getting the total edges in the origional graph, which will be used for the forestfire algorithm
            forest_fire(S, X, k, missing);//forestfire algorithm

            missingEdges(&X, &S, &missing);//getting the real missing edges that are in the origional graph but not the sample graph
            //writeBothNetworks(&X, &S, "FF");//writing the sample network from the forestfire algorithm
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
            lcs += local_clustering_score(S);
            //sleep(1);
            usleep(50000);
        }

        //cout <<"predicted size: " << _predictedEdges.size() << " missing size: " << missing.size() <<endl;
        numNodes = S.size();//getting the number of nodes in the graph
        avgEdges = totalEdges(&X) * 0.25;//getting the average number of edges. Multiplying by 0.25 since the forest fire algorithm will use 25% of the origional graph
        //cout <<"average edges: " << avgEdges << endl;
        outputFile << buffer << " " <<RAScores[0]/numLoops << " " <<AAScores[0]/numLoops << " "<<cnScores[0]/numLoops << " " << katzScores[0]/numLoops << " " <<numNodes<< " " 
        <<avgEdges << " " << lcs/numLoops << " " <<float(avgEdges/numNodes) <<"\n";
        outputFile << " " <<RAScores[1]/numLoops << " " <<AAScores[1]/numLoops << " "<<cnScores[1]/numLoops << " " << katzScores[1]/numLoops <<"\n";
        outputFile <<" "<<f1Value(RAScores[0]/numLoops, RAScores[1]/numLoops) << " " << f1Value(AAScores[0]/numLoops, AAScores[1]/numLoops)<<" "
        << f1Value(cnScores[0]/numLoops, cnScores[1]/numLoops) << " "<< f1Value(katzScores[0]/numLoops, katzScores[1]/numLoops) <<"\n";
        outputFile << endl;
        X.clear();
        memset(buffer, 0, sizeof(buffer));//resseting the buffer
        lcs = 0.0;
    }
    outputFile.close();
}


void changeDirectory(pid_t pid)
{
    int status;
    if((pid == fork()) == -1){cout << "fork error\n";}
    else if(pid == 0)//child process
    {
        execlp("cd", "../../..");//going to the directory with the community files
    }
    else
    {
        wait(&status);//wait for child to finish
    }
}

void runCommunity(pid_t pid)
{
    int status;
    if((pid == fork()) == -1){cout << "fork error\n";}
    else if(pid == 0)//child process
    {
        execlp("./community", "graph.bin", "-l", "-1", "-v", ">", "graph.tree");//going to the directory with the community files
    }
    else
    {
        wait(&status);//wait for child to finish
    }

}

void convert(pid_t pid)
{
    int status;
    if((pid == fork()) == -1){cout << "fork error\n";}
    else if(pid == 0)//child process
    {
        execlp("./convert", "-i", "graph.txt", "-o", "graph.bin");//going to the directory with the community files
    }
    else
    {
        wait(&status);//wait for child to finish
    }
}
#endif