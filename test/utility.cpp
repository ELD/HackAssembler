std::string getCommandString(int commandType)
{
    switch (commandType) {
        case 0:
            return "L_COMMAND";
        break;
        case 1:
            return "A_COMMAND";
        break;
        case 2:
            return "C_COMMAND";
        break;
    }

    return "NO_COMMAND";
}
