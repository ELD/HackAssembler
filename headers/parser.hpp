#ifndef _PARSER_H_
#define _PARSER_H_

#include "headers.hpp"

namespace hack {

    class Parser
    {
    public:
        Parser (std::istream&);
        virtual ~Parser ();
        bool hasMoreCommands();
        void advance();
        COMMAND_TYPE commandType() const;
        std::string getCurrentCommand() const;
        std::string getSymbol();
        std::string getDestBits();
        std::string getCompBits();
        std::string getJumpBits();
        void rewind();

        // Accessor methods for testing
        void setCurrentCommand(std::string);
        int getPC() const;
    private:
        void trimCommand(std::string&);

        // std::unique_ptr<std::ifstream> _file;
        std::istream& _file;
        std::string _currentCommand;

        std::regex _lCommand;
        std::regex _aCommand;

        size_t _fileHead;

        int _pc;
    };
}

#endif
