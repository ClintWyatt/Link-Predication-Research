#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

//this program is used for calculating the avarages of precision, recall, and f1 value
int main(int args, char * argv[])
{

    if(args !=2){
        cout <<"usage: ./a.out filename\n";
        return 0;
    }
    string line, str1, str2;
    fstream input;
    stringstream linestream;
    input.open(argv[1], fstream::in);//specifying the 
    if(!input){cout <<"ERROR: file does not exist" <<endl; return -1;}
    regex p ("Precision:");
    regex r ("Recall");
    regex f ("F1Value:");
    vector<float> precisionAverage;
    vector<float> recallAverage;
    vector<float> f1Average;
    float value; 
    while(getline(input, line))
    {
        if(line.length() >0)
        {
            linestream << line;
            linestream >> str1 >> str2;
            if(regex_match(str1, p))
            {
                value = stof(str2);
                precisionAverage.push_back(value);
            }
            else if(regex_match(str1, r))
            {
                value = stof(str2);
                recallAverage.push_back(value);
            }
            else if(regex_match(str1, f))
            {
                value = stof(str2);
                f1Average.push_back(value);
            }
            linestream.clear();
            
        }
    }
    input.close();
    value = 0.0;
    float graphValue = 0.0;
    for(int i =0, j=0; i < precisionAverage.size(); i++)
    {
        if(i > 0 && i%5 ==0)
        {
            
        }
        value+=precisionAverage[i];
        
    }
    value = value / precisionAverage.size();
    cout << "Precision average is: " << value <<endl;

    value = 0.0;
    for(int i =0, j=0; i < recallAverage.size(); i++)
    {
        value+=recallAverage[i];
    }
    value = value / recallAverage.size();
    cout << "Recall average is: " << value <<endl;

    value = 0.0;
    for(int i =0, j =0; i < f1Average.size(); i++)
    {
        value+=f1Average[i];
    }
    value = value / f1Average.size();
    cout << "F1 value average is: " << value <<endl;
    return 0;
}