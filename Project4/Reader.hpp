
#ifndef __Reader_hpp
#define __Reader_hpp

#include<fstream>
#include<string>
#include "Token.hpp"

class Reader
{
public:
    Reader( const char *fileToReadFrom );
    Reader( const std::string  fileToReadFrom );
    Token getToken();
    ~Reader();

private:
    void initialize(const char *fName);
    std::string readCommandLine();
    int isBlankOrComment(std::string &inputLine);
    void readNextNonBlankAndCommentLine(std::string &currentInputLine);
    std::size_t idxOfFirstNonSpaceChar(std::string &line, std::size_t startIdx);
    std::size_t idxOfFirstNonNameChar(std::string &line, std::size_t startIdx) ;

    bool _inputBufferEmpty, _readingCommandLine, _readingDependencyLine;
    const char *_fileToReadFrom;
    std::string _currentInputLine;
    std::size_t _inputIdx;  // index of the first unused character in currentInputLine.
    std::fstream _ins;
};

#endif
