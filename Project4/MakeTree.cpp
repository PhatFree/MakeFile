/*
 * Cs315
 * Project 4
 * MakeFile
 * Jeffrey Booher-Kaeding
 */
#include "MakeTree.hpp"

MakeTree::MakeTree()
{
 _root == nullptr;
}

MakeTree::~MakeTree()
{
	delete _root;
}

GraphNode *MakeTree::find (TreeNode *root, std::string name)
{// recurisve look for File name
	//if null return null
	if (root == nullptr)
		return nullptr;
	//if we found the node return it
	if (root -> graphNode() -> getName() == name)
		return root->graphNode();
	//if the name is larger than go left
	if (root -> graphNode() -> getName() > name)
		return find(root -> left(), name);
	//else go right
	else
		return find(root -> right(),name); 
}

GraphNode *MakeTree::find( std::string name)
{//  call private
	return find(_root,name);
}


TreeNode *MakeTree::insert(TreeNode *tNode, GraphNode *nNode)
{// recursive insert
	if (tNode == nullptr)
		return new TreeNode(nNode);
	if(tNode -> graphNode() -> getName() < nNode -> getName())
		tNode->right( insert( tNode->right(),nNode));
	else 
		tNode->left( insert( tNode->left(),nNode));
	return tNode;
	
}

void MakeTree::print(TreeNode *root)
{ // if we have the node, print it.
	if (root == nullptr)
		return;
	print(root->left());
	root->print();
	print(root->right());
}
