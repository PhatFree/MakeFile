/*
 * Cs315
 * Project 4
 * MakeFile
 * Jeffrey Booher-Kaeding
 */
#include<iostream>
#include<cstdlib>
#include "DepGraph.hpp"

int main(int argc, const char *argv[] ) 
{
    if( argc != 2 ) {
        std::cout << "usage: " << argv[0] << " name-of-a-makefile\n";
        exit(1);
    }
    DepGraph *make = new DepGraph(argv[1]);
    make->parseDepGraph();
    if( make->isCyclic() )  {
        std::cerr << "Input graph has cycles.\n";
	make->cyclicPrint();
        exit(1);
    }
    make->runMake();
    return 0;
}
