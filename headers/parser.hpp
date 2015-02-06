#ifndef _PARSER_H_
#define _PARSER_H_

#include "headers.hpp"

namespace hack {

    class Parser
    {
    public:
        Parser (const std::string);
        virtual ~Parser ();
        std::string nextLine() const;
        bool hasMoreCommands();
        void advance();
        COMMAND_TYPE commandType() const;
        std::string getCurrentCommand() const;
        void rewind();

        // Accessor methods for testing
        void setCurrentCommand(std::string);
    private:
        void trimCommand(std::string&);

        std::unique_ptr<std::ifstream> _file;
        std::string _currentCommand;

        size_t _fileHead;
    };
}

#endif
