Link Predication Research Code

HOW TO COMPILE:
    All files are compiled using a Makefile. In order to use the Makefile:
        1) Change the ESSENS path to the path your code is located. 
        2) Change the LOCAL_INDICES path to the path your code is located.
        *For Windows Users, make sure to keep the beginning part of the path location (/mnt/c/Users/YOUR_PATH_HERE)
        3) Command "make" will compile all files
        4) Command "./a.out YOUR_NETWORK_FILE 1 output.txt map.txt" 

File Locations
    LocalIndices Folder holds all Link Predication & Sample Algorithms created
        IMPORTANT FILES:
            sampling.hpp 
                -Holds all sampling algorithms and calculates scores 
                between edges in Original graph that are missing from Sample

            local_indices_algorithms.hpp 
                -Holds all link predication Algorithms

            universal_func.hpp
                -Holds common functions used throughout the code

        FILES NOT CURRENTLY IN USE:
            detach_edges.hpp & nonexist_links.hpp 
                -This sampling detached edges at random across a netowrk and 
                selected edges that where k distance apart 

            get_scores.hpp
                -These functions were helper functions to get the scores of 
                the detach_edges scores

            compute_precision_recall.hpp
                -Calculated the precision and recall of the top scored nodes
                with the nonexist_links found  

        FILES THAT DO NOT WORK:
            new_elim_game.hpp
            crawl_netowrk.hpp
            
How to run the research project:
To run a individual file, go to the ClintsCode directory and type make to compile.
After compiling, you have 2 options for testing files:
    1. To run a individual file, type ./a.out ../test_networks/DYNAMIC_NET/<directoryName> 1 output.txt map.txt, where the directory name is a sub directory of test_networks 
    2. To run all files in a directory, type ./a.out output.txt map.txt ../test_networks/<directoryName> 1 directory, where the directory name is a sub directory of test_networks

The results are written in the results directory.

If you decide to do option 2 for testing files, you can write all the files to a excel file by going to the python directory and typing python toExcell.py. The
format (columns) of the excell sheet created by the python script can be seen in the metricResults.csv file in the results directory. 
            
