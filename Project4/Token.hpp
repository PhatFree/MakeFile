/*
 * Cs315
 * Project 4
 * MakeFile
 * Jeffrey Booher-Kaeding
 */
#include<iostream>
#include<string>

#ifndef Token_hpp
#define Token_hpp

class Token {
	public:
		Token( std::string name ) { 
			initialize(); 
			_name = name;
		}
		Token() { initialize(); }

		void print();
		bool isName()				{ return _isName;             		}
		std::string getName()			{ return _name;               		}
		void setName(std::string s)     	{ _name = s; _isName = true;  		}
		bool isColon()                  	{ return _isAColon;           		}
		void isColon(bool colon)        	{  _isAColon = colon;         		}
		bool isEOL()		                { return _eol;                		}
		void isEOL(bool eol)    	        { _eol = eol;                 		}
		bool isEOF()                    	{ return _eof;                		}
		void isEOF(bool eof)            	{  _eof = eof;                		}
		void isUnknow(bool v)           	{  _unknown = v;              		}
		bool isUnknow()                 	{  return _unknown;           		}
		void setUnknownChar(char c)     	{ _unknownChar = c;           		}
		char getUnknownChar()           	{ return _unknownChar;        		}
		std::string getCommand()        	{ return _command;            		}
		void setCommand(std::string command) { _command = command;  _isCommand = true;  }
		bool isCommand()                	{ return _isCommand;          		}

	private:
		void initialize();

		std::string _name, _text, _command;
		bool _isAColon, _eol, _eof, _unknown, _isCommand, _isName;
		char _unknownChar;
};

inline void Token::initialize() 
{
	_isCommand = _unknown = _eol = _eof = _isAColon = _isName = false;
	_name = _text = "";
	_unknownChar = ' ';
	_command = "";
}

#endif
