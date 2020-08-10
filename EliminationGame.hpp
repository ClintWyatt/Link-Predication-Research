//
//
//
//
//  Created by Sanjukta Bhowmick on 7/19/19.
//
/*
#ifndef EliminationGame_hpp
#define EliminationGame_hpp

#include "ADJ/degree_centrality.hpp"
#include "order_elements.hpp"
#include "unary_set_operations.hpp"
#include "binary_set_operations.hpp"
#include "ADJ/find_neighbors.hpp"

//Vertex with highest degree eliminated first

int elimination_game_max_deg(A_Network *X, vector<Edge> *addedE)
{
    addedE->clear();


    vector<int_int> degreeC;

    //Compute degree of X
    degree_centrality(X,&degreeC);

    //First remove vertices with degree 1
    for(int i=0;i<X->size();i++)
    {
        int v=degreeC[i].first;
        int deg=degreeC[i].second;

        //Delete node if degree is 1
        if(deg==1)
        {
            int n=X->at(i).ListW[0].first;
            int index=X->at(i).Ops[0];

            //Delete the edge
            X->at(i).ListW[0].second=-1;
            degreeC[i].second=0;

            //Delete opposite edge
            X->at(n).ListW[index].second=-1;
            degreeC[n].second=degreeC[n].second--;
        }//end of if
    }//end of for

    make_heap(&degreeC,inc_second);
    print_vector(degreeC);

    //Remove vertices in order and connect neighbor
    vector<bool> done;
    done.resize(X->size(),false);

    while(degreeC.size()>0) //continue until all nodes are eliminated
    {
        int_int x= degreeC.front();
        int v=x.first;
        int deg=x.second;
        //Take out of heap;
        pop_heap(&degreeC,inc_second);

       if(done[v]){continue;} //continue if vertex processed

        //Connect the neighbors of v, and push them to heap;
        //Get set of neighbors of v
        vector<int> neighbors;
        neighbors.clear();
        for(int i=0;i<X->at(v).ListW.size();i++)
        {
            int n=X->at(v).ListW[i].first;
            int w=X->at(v).ListW[i].second;

            if(w==-1){continue;}//continue if edge deleted
            if(done[n]){continue;} //continue if this neighbor has been processed
            neighbors.push_back(n);
        }
      sort(&neighbors);


        //For each neighbor of v;
        int sum=0;
        for(int i=0;i<X->at(v).ListW.size();i++)
        {
            int n=X->at(v).ListW[i].first;
            int w=X->at(v).ListW[i].second;

            if(w==-1){continue;}//continue if edge deleted
            if(done[n]){continue;} //continue if this neighbor has been processed

            //Get neighbors of n
            vector<int> neighborsX;
            neighborsX.clear();

            for(int j=0;j<X->at(n).ListW.size();j++)
            {
                int m=X->at(n).ListW[j].first;
                int w=X->at(n).ListW[j].second;

                if(w==-1){continue;}//continue if edge deleted
                if(done[m]){continue;} //continue if this neighbor has been processed
             neighborsX.push_back(m);
            }
            sort(&neighborsX);

            //Find the difference to see which neighbors missing
            vector<int> diff;
            diff=difference(neighbors, neighborsX);
            printf("%d--\n",n);
          //  print_vector(neighborsX);
            print_vector(diff);
            sum=sum+diff.size()-1;

             int_int dummy;
            Edge mye;
            mye.edge_wt=1;
            for(int j=0;j<diff.size();j++)
            {
                int m=diff[j];
                if(m==n) {continue;} //no need to add with self
                if(m<n) {continue;} //this edge is added when m is processed

                dummy.first=m;
                dummy.second=1;
                X->at(n).ListW.push_back(dummy);

                //Add the edge
                mye.node1=n;
                mye.node2=m;
                addedE->push_back(mye);
            }//end of for j

            //Update degree and push to heap
            if(diff.size()>1)
            {
                dummy.first=n;
                dummy.second=X->at(n).ListW.size()-1;
                push_heap(&degreeC,dummy,inc_second);
            }
        }//end of for i

        //Set v to done
        done[v]=true;
        sum=sum/2;
       printf("%d --%d--%d--%d \n",v, deg,sum,degreeC.size());
    }//end of while







    return;
}


#endif  EliminationGame_hpp */
