/*
 * Cs315
 * Project 4
 * MakeFile
 * Jeffrey Booher-Kaeding
 */
#include "DepGraph.hpp"

DepGraph::DepGraph( std::string name)
{//inti
	_fileToMake = name;
	_tree = new MakeTree();
	_cyclicNodes = new std::vector<GraphNode *>;
}

DepGraph::~DepGraph()
{
	delete _tree;
	delete _cyclicNodes;
}
void DepGraph::print()
{// calls upon the MakeTree to print all information
	_tree->print();
}

void DepGraph::parseDepGraph()
{// public call that iterates through the make targets
	
	//pass file name
	Reader *reader = new Reader(_fileToMake);
	// check to see if empty
	Token token = readAndProcessDependencyPair(reader);
	// while file isn't empty call private
	while( !token.isEOF())
	{
		token = readAndProcessDependencyPair(reader);
	}
	// the defualt dependency is gaurnteed to be the first file in the make tree BST
	firstTarget = _tree -> getRoot() -> graphNode();
}

void DepGraph::runMake()
{// call private
	runMake(firstTarget);
}

bool DepGraph::isCyclic()
{// call private
	return isCyclic(firstTarget);
}


Token DepGraph::readAndProcessDependencyPair(Reader *n)
{
	//if we see EOF return
	Token target = n -> getToken();
	if (target.isEOF())
		return target;
	//check 4 name
	if( ! target.isName() ) {
		std::cout << "first token of dependency should be a name-token.\n";
		exit(1);
	}

	// look for name, if we get a nullptr we need to make the node
	GraphNode *targetNode = _tree->find(target.getName());
	if(targetNode == nullptr )
	{
		targetNode = new GraphNode(target.getName());
		_tree -> insert( targetNode); 
	}
	
	// since this is a target, lable it as such.
	targetNode -> isATarget(true);

	//std::cout << "Target is: " << target.getName() << std::endl;

	//colon starts depenecy vector
	Token colon = n->getToken();
	if( ! colon.isColon() ) {
		std::cout << "Missing colon character on the dependency line.\n";
		exit(1);
	}

	//std::cout << "The following file-names depend on the above target.\n";
	Token token;
	token = n->getToken();
	while (token.isName())
	{// while we have names, add them to the target's dependency vector

		//	std::cout << token.getName() << std::endl;
		
		//same as above, if it isn't in the make tree, make it
		//but don't set its target!
		GraphNode *dependentNode = _tree->find( token.getName());
		if(dependentNode == nullptr)
		{	
			dependentNode = new GraphNode(token.getName());
			_tree->insert( dependentNode);
		}
		targetNode -> addDependentNode( dependentNode);
		token = n->getToken();	
	}
	//this would be two EOL's
	if( ! token.isEOL() ) {
		std::cout << "Dependency line contains a non-name token.\n";
		exit(1);
	}

	// find commaned
	token = n->getToken();
	if ( ! token.isCommand() ) {
		std::cout << "No command found after dependency line.\n";
		exit(1);
	}
	//std::cout << "The command is: " << token.getCommand() << std::endl;
	targetNode->setCommand(token.getCommand());
	return target;

}

bool DepGraph::isCyclic(GraphNode *p)
{
	//if nullptr is good for us.
	if (p == nullptr)
		return false;
	// onPath means we have visited the node, so we check this next
	// return true if we've been here before
	if (p -> onPath() == true)
		return true;
	//set on path saying we've been here
	p -> onPath(true);
	//recursivley check our dependt nodes
	for (int i = 0; i < p -> numDependentNodes(); i++)
		if (isCyclic(p -> dependentNodes()->at(i) ))
		{
			_targetToMake = p->dependentNodes()->at(i)->getName();
			cyclicRun(p->dependentNodes()->at(i));
			return true;
		}
	//set on bath back to false before we leave
	p -> onPath(false);
	return false;
}

void DepGraph::runMake (GraphNode *p)
{
	//pretty sure my wasMade check is redundent...
	if (p->wasMade())
		return;

	
	bool make = false;
	long target_ts;

	//if we can get a time stamp, set it
	if(timestamp( p->getName().c_str(), &target_ts))
		p->setTimestamp(target_ts);

	//check dependt node's time stamps
	for (int i = 0; i < p->numDependentNodes(); i++)
	{	
		//time stamp the depndent node fix later				//this could be cause of double make issue
		GraphNode *tempNode = p -> dependentNodes()->at(i);			//#
		// This is ineficent, fix later,					
		if (tempNode->isATarget())						
			runMake(p-> dependentNodes()-> at(i));				
	//	else 									
		long dependent_ts;							//#
		if(timestamp(tempNode->getName().c_str(), &dependent_ts))	
			tempNode->setTimestamp(dependent_ts);			

		//if the dependent time stamp is newer, we need to make the target
		if (tempNode->getTimestamp() > p->getTimestamp()){
		make = true;
		}
		//debug couts
	//	std::cout << "dependt Node is: "<< tempNode->getName() << " Target Node is: " << p->getName()<< std::endl;
	//	std::cout <<"dependent ts: "<< tempNode->getTimestamp() <<" Target ts: "<<p->getTimestamp() << std::endl;
	//	std::cout << "diff is: " << tempNode->getTimestamp() - p->getTimestamp() << std::endl;
	}
	if (make)
	{
		p->runCommand();
		p->wasMade(true);
	//	timestamp( p->getName().c_str(), &target_ts);			//this is the fix for the possible issue above.
	//	p->setTimestamp(target_ts);					//#
	}
	else //let the user know the top file is already been made.
		if( p->getName() == firstTarget->getName())
		std::cout<< "make: '"<< p->getName() << "' is up to date.\n";

}

void DepGraph::cyclicPrint()
{
	std::cout<< "The following node '" << _targetToMake << "' dependencies run in a circle, shown below:\n";
	for (int i = 0; i < _cyclicNodes->size() - 1;i++)
	{
		std::cout<< _cyclicNodes->at(i)->getName() << " -> ";
	}
	std::cout<< _cyclicNodes->at(_cyclicNodes->size()-1)->getName() << std::endl;

}

void DepGraph::cyclicRun(GraphNode *p)
{// if there is nothing return.
	if (p == nullptr)
		return;
	// if we've been here before we should return.
	if (p-> cyclic())
		return;
	
	//else loop to find the cyclic
	p->cyclic(true);
		for (int i = 0; i < p-> numDependentNodes(); i++)
			if (p->dependentNodes()->at(i)->onPath())
				cyclicRun(p->dependentNodes()->at(i));
	//and when were done looping push this one back.
	_cyclicNodes->push_back(p);

}
