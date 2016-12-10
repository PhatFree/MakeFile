/*
 * Cs315
 * Project 4
 * MakeFile
 * Jeffrey Booher-Kaeding
 */
#ifndef _GraphNode_hpp
#define _GraphNode_hpp
#include<iostream>
#include<string>
#include<vector>

class GraphNode {
	public:
		GraphNode( std::string name );
		~GraphNode();

		//Name
		std::string getName();
		void setName( std::string name );
		//Time stamp
		void setTimestamp(int ts);
		int getTimestamp();
		//vector
		std::vector<GraphNode *> *dependentNodes();
		void addDependentNode(GraphNode *child);
		int numDependentNodes();
		//command
		void setCommand(std::string cmnd);
		std::string getCommand();
		void runCommand();  // execute the command associated with this node.
		//on path
		bool onPath();
		void onPath(bool v);
		// was made
		bool wasMade();
		void wasMade(bool v);
		// is target
		bool isATarget();
		void isATarget(bool v);
		//cyclic trace
		bool cyclic();
		void cyclic(bool v);
		// debug print
		void print();

	private:
		std::string _name, _command;
		int _timestamp;
		std::vector<GraphNode *> *_listOfDependentNodes;

		bool _onPath, _isATarget, _wasMade, _cyclic;
};
#endif
