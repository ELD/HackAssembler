#ifndef _PARSER_H_
#define _PARSER_H_

#include "headers.hpp"

namespace hack {

    class Parser
    {
    public:
        Parser();
        Parser (const std::string);
        virtual ~Parser ();
        std::string nextLine() const;
        bool hasMoreCommands();
        void advance();
        COMMAND_TYPE commandType() const;
        std::string getCurrentCommand() const;
        std::string symbol();
        std::string dest();
        std::string comp();
        std::string jump();
        void rewind();

        // Accessor methods for testing
        void setCurrentCommand(std::string);
    private:
        void trimCommand(std::string&);

        std::unique_ptr<std::ifstream> _file;
        std::string _currentCommand;

        std::regex lCommand;
        std::regex aCommand;

        size_t _fileHead;
    };
}

#endif
