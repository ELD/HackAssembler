#ifndef _PARSER_H_
#define _PARSER_H_

#include "headers.hpp"

namespace hack {

    class Parser
    {
    public:
        Parser (std::istream&);
        bool hasMoreCommands();
        bool advance();
        COMMAND_TYPE commandType() const;
        std::string getCurrentCommand() const;
        std::string getSymbol();
        std::string getDestBits();
        std::string getCompBits();
        std::string getJumpBits();
        std::string translateACode(int);
        void rewind();
        void collectLabels();
        void translateAssembly(std::ostream&);

        // Accessor methods for testing
        void setCurrentCommand(std::string);
        int getPC() const;
        SymbolTable getSymbolTable() const;
    private:
        void trimCommand(std::string&);
        void trimComments(std::string&);
        bool isWhitespace(std::string&);

        std::istream& _file;
        std::string _currentCommand;

        std::regex _lCommand;
        std::regex _aCommand;

        size_t _fileHead;

        int _pc;
        int _mem;

        SymbolTable _symbols;
    };
}

#endif
