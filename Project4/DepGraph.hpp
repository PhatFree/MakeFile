/*
 * Cs315
 * Project 4
 * MakeFile
 * Jeffrey Booher-Kaeding
 */
#ifndef _DepGraph_hpp
#define _DepGraph_hpp

#include<iostream>
#include<cstring>

#include "MakeTree.hpp"
#include "Token.hpp"
#include "Reader.hpp"
#include "GraphNode.hpp"
#include "systemInterface.hpp"

class DepGraph {
	public:
		DepGraph( std::string name );
		~DepGraph();

		void print();		// does nothing at the moment.
		void parseDepGraph();	// Read makefile
		void runMake(); 	//execute makefile
		bool isCyclic(); 	//Check for cycle in dependencies
		void cyclicPrint();	//Print Cyclic sequnce

	private:
		Token readAndProcessDependencyPair(Reader *);
		bool isCyclic(GraphNode *p);
		void cyclicRun(GraphNode *p);
		void runMake( GraphNode *p );

	private:
		std::string _fileToMake, _targetToMake;
		GraphNode *firstTarget;
		MakeTree *_tree;
		std::vector<GraphNode *> *_cyclicNodes;
};

#endif
