#ifndef SETUPSAMPLE_HPP
#define SETUPSAMPLE_HPP

void setUpSample(A_Network &S, int size)
{
    
    for(int i =0; i < size; i++)
    {
        S[i].Row = i;
    }
}

#endif