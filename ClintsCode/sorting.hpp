#ifndef SORTING_HPP
#define SORTING_HPP
using namespace std;

template <class myType>
void insertionSort(vector<myType> *scores){
    int i, j;
    myType key;  
    for (i = 1; i < scores->size(); i++) {  
        key = scores->at(i);  
        j = i - 1;  
  
        /* Move elements of arr[0..i-1], that are  
        greater than key, to one position ahead  
        of their current position */
        while (j >= 0 && scores->at(j) > key) {  
            scores->at(j + 1) = scores->at(j);  
            j = j - 1;  
        }  
        scores->at(j + 1) = key;  
    }
}



void insertionSort(vector<int_string> *scores){
    int i, j;
    int key;
    string str;  
    for (i = 1; i < scores->size(); i++) {  
        key = scores->at(i).first;  
        str = scores->at(i).second;
        j = i - 1;  
        while (j >= 0 && scores->at(j).first > key) {  
            scores->at(j + 1) = scores->at(j);  
            j = j - 1;  
        }  
        scores->at(j + 1).first = key;  
        scores->at(j + 1).second = str;
    }
}

#endif