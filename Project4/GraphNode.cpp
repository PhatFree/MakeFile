/*
 * Cs315
 * Project 4
 * MakeFile
 * Jeffrey Booher-Kaeding
 */
#include "systemInterface.hpp"
#include "GraphNode.hpp"

GraphNode::GraphNode( std::string name)
{
	_listOfDependentNodes = new std::vector<GraphNode *>();
	_name = name;
	_onPath = _isATarget = _wasMade = _cyclic = false;
	_timestamp = 0;
}

GraphNode::~GraphNode()
{
	delete _listOfDependentNodes;
}

//setters and getters are all single line below.

//name
std::string GraphNode::getName(){return _name;}
void GraphNode::setName(std::string name){_name = name;}

//timestamp
int GraphNode::getTimestamp(){return _timestamp;}
void GraphNode::setTimestamp(int ts){_timestamp = ts;}

//vector
int GraphNode::numDependentNodes(){return _listOfDependentNodes->size();}
std::vector<GraphNode *> *GraphNode::dependentNodes(){return _listOfDependentNodes;}
void GraphNode::addDependentNode(GraphNode *child){ _listOfDependentNodes->push_back(child);}

//command
void GraphNode::runCommand(){ executeCommand(_command.c_str());}
std::string GraphNode::getCommand(){ return _command;}
void GraphNode::setCommand(std::string cmnd){ _command = cmnd;}

//onPath
bool GraphNode::onPath(){ return _onPath;}
void GraphNode::onPath(bool v){_onPath = v;}

//wasMade
bool GraphNode::wasMade(){return _wasMade;}
void GraphNode::wasMade(bool v){ _wasMade = v;}

//isATarget
bool GraphNode::isATarget() {return _isATarget;}
void GraphNode::isATarget(bool v){ _isATarget = v;}

bool GraphNode::cyclic() {return _cyclic;}
void GraphNode::cyclic(bool v){ _cyclic = v;}

void GraphNode::print()
{//cout all info for 
	std::cout << "Name 	 :" << getName() << std::endl;
	std::cout << "Time Stamp :" << getTimestamp() << std::endl;
	std::cout << "Command	 :" << getCommand() << std::endl;
	std::cout << "On Path	 :" << onPath() << std::endl;
	std::cout << "Was Made	 :" << wasMade() << std::endl;
	std::cout << "Is A Target:" << isATarget() << std::endl;
	std::cout << "Num Depends:" << numDependentNodes() << std::endl;
	std::cout << "Depen Nodes:" << std::endl;
	for (int i = 0; i < numDependentNodes(); i++)
		std::cout << dependentNodes()->at(i)->getName()<< std::endl;
	std::cout << std::endl;
}
