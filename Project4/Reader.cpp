#include<fstream>
#include<iostream>
#include<cstdlib>
#include "Reader.hpp"
#include "Token.hpp"

using namespace std;

void Reader::initialize(const char *fName)
{
    _ins.open( fName );
    if( ! _ins.is_open() ) {  // not elegant!
        std::cout << "Unable to open " << fName << std::endl;
        exit(1);
    }

    _fileToReadFrom = fName;
    _currentInputLine = "";
    _inputIdx = 0;
    _inputBufferEmpty = true; 
    _readingCommandLine = false; 
    _readingDependencyLine = true;
}

Reader::Reader( const char *fName ) 
{
    initialize(fName);
}

Reader::Reader( const string fName ) 
{
    initialize( fName.c_str() );
}

std::string Reader::readCommandLine()
{
    char c;
    std::string command = "";
    while( _ins.get(c) && ! (c == '\n' || c == '#' ) )
        command += c;
    if( c == '#' )
        while( _ins.get(c) && c != '\n' )
            ;
    return command;
}

int Reader::isBlankOrComment(std::string &inputLine)
{
    const char *buffer = inputLine.c_str();
    for(buffer = inputLine.c_str(); *buffer && *buffer == ' '; ++buffer )
        ;
    return ! *buffer || *buffer == '#';
}

void Reader::readNextNonBlankAndCommentLine(std::string &currentInputLine)
{
    while( getline(_ins, currentInputLine) && isBlankOrComment(currentInputLine) )
        ;
    if(_ins.eof()) 
        _inputBufferEmpty = true; // This could very well discard the last line of the input-file
                                  // if it doesn't have a terminating new-line character.
    else {
        int pos = currentInputLine.find('#');
        if( pos > 0 ) // can not be zero!
            currentInputLine = currentInputLine.substr(0, pos);
    }
}

std::size_t Reader::idxOfFirstNonSpaceChar(std::string &line, std::size_t startIdx)
{
    while( startIdx < line.length() && (line[startIdx] == ' ' || line[startIdx] == '\t') )
        startIdx++;
    return startIdx;
}

bool isANameChar(char c)
{
    return c == '_' || c == '.' || isalnum(c);
}

std::size_t Reader::idxOfFirstNonNameChar(std::string &line, std::size_t startIdx) 
{
    while( startIdx < line.length() && isANameChar(line[startIdx] ) )
        startIdx++;
    return startIdx;
}

Token Reader::getToken() 
{
    Token token;
    if( ! _ins.is_open() || _ins.eof() || ! _ins.good() ) {
        token.isEOF(true);
        return token;
    }
    if( _inputBufferEmpty ) {
        readNextNonBlankAndCommentLine(_currentInputLine);
        if( _ins.eof() ) { 
            token.isEOF(true);
            return token;
        }
        _inputIdx = 0;
    }
    _inputBufferEmpty = false;
    if( _readingDependencyLine ) {
        _inputIdx = idxOfFirstNonSpaceChar( _currentInputLine, _inputIdx );
        if( _inputIdx == _currentInputLine.length() ) {
            token.isEOL(true);
            _readingDependencyLine = false;
            _inputBufferEmpty = true;
            return token;
        }
        if( _currentInputLine[_inputIdx] == ':' ) {
            token.isColon(true);
            _inputIdx++;
            return token;
        }
        int idx = idxOfFirstNonNameChar( _currentInputLine, _inputIdx );
        std::string name = _currentInputLine.substr(_inputIdx, idx - _inputIdx);
        token.setName( name );
        _inputIdx = idx;
        return token;
    }
    // must be reading a command 
    const char *buffer = _currentInputLine.c_str();
    if( *buffer != '\t' ) {
        std::cout << "Command lines should start with a tab-character. The following command-line doesn't\n";
        std::cout << _currentInputLine << std::endl;
        exit(1);
    } else {
        token.setCommand(buffer+1);
        _inputBufferEmpty = true;
        _readingDependencyLine = true;
    }
    return token;
}

Reader::~Reader()
{
    if( _ins.is_open() )
        _ins.close();
}
