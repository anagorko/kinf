#ifndef Error_H
#define Error_H

#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class Error
{
public:

    virtual ~Error() {}

    Error(string _file, int _line, string _statement = "lack")
    : file(_file), line(_line), statement(_statement)
    {
        cerr << "ERROR: " << file << ":" << line << " " << statement << endl;
    }

    const string file;
    const int line;
    const string statement;
};

#endif // Error_H
