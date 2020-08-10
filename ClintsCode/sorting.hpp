#ifndef SORTING_HPP
#define SORTING_HPP
using namespace std;

template <class myType>
void sort_scores(vector<myType> *scores)
{
  int i, j;
  myType key;  
    for (i = 1; i < scores->size(); i++) 
    {  
        key = scores->at(i);  
        j = i - 1;  
  
        /* Move elements of arr[0..i-1], that are  
        greater than key, to one position ahead  
        of their current position */
        while (j >= 0 && scores->at(j) > key) 
        {  
            scores->at(j + 1) = scores->at(j);  
            j = j - 1;  
        }  
        scores->at(j + 1) = key;  
    }
}

#endif