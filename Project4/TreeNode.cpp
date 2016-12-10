/*
 * Cs315
 * Project 4
 * MakeFile
 * Jeffrey Booher-Kaeding
 */
#include "TreeNode.hpp"


TreeNode::TreeNode( GraphNode *nNode)
{
	makeNode = nNode;
	leftSubtree = rightSubtree = nullptr;
	
}

TreeNode::~TreeNode()
{
	delete makeNode;
	delete leftSubtree;
	delete rightSubtree;
}

//LEFT
//getter
TreeNode *TreeNode::left(){return leftSubtree;}
//setter
void TreeNode::left( TreeNode *leftPtr){leftSubtree = leftPtr;}

//RIGHT
//getter
TreeNode *TreeNode::right(){return rightSubtree;}
//setter
void TreeNode::right( TreeNode *rightPtr){rightSubtree = rightPtr;}

//call nodes print
void TreeNode::print()
{
 	graphNode()->print();
}
//return node
GraphNode *TreeNode::graphNode()
{
	return makeNode;
}
