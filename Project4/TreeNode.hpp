/*
 * Cs315
 * Project 4
 * MakeFile
 * Jeffrey Booher-Kaeding
 */
#ifndef _TreeNode_hpp
#define _TreeNode_hpp

#include <iostream>
#include <string>
#include "GraphNode.hpp"

class GraphNode;

class TreeNode {
	public:
		TreeNode( GraphNode *nNode );
		~TreeNode();

		TreeNode *left();                // getter
		void left( TreeNode *leftPtr );  // setter

		TreeNode *right();		 // getter
		void right( TreeNode *rightPtr );// setter
		
		void print();   // print the value of this node
		GraphNode *graphNode(); //grab our graph node

	private:
		GraphNode *makeNode;
		TreeNode *leftSubtree, *rightSubtree;
};

#endif
