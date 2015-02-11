# Hack Assembler for CSCI 410

### README:
1. Eric Dattore
2. No one else assisted me with this project.
3. 10-12 hours, predominately from the learning how to write unit tests in the Boost Unit Test Framework (UTF)
4. I built and tested this project with the Boost.Test libraries and I also used
    the C++11 regex library that's available in GCC 4.9 and Clang 3.5. The project has a
    Makefile in the root directory that can be run by invoking the ```make``` command.
    Tests can be built using the ```make test``` target. All binaries are built in the
    ```target``` directory. The ```hackasm``` binary is the assembler and the ```tester```
    binary runs all unit tests from the ```test``` directory. Example usage for the
    assembler is as follows: ```./hackasm [file]```. If you fail to provide a file
    argument, the application will issue an error message and exit prematurely.
