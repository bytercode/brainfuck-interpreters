#ifndef DEFS_HPP_INCLUDED
#define DEFS_HPP_INCLUDED
#include <iostream>
#include <stack>
#include <conio.h>
#include <cstring>
#include <fstream>
#include <experimental/filesystem>

class fsrhandl
{
    short ttype;
    std::ifstream fs;
    char *buf;
    unsigned long strindx;
public:
    fsrhandl();
    short getach();
    short get_type();
    int openfile(const char *filename, bool bin);
    void openstring(const char *str);
    unsigned long tell();
    void seek(unsigned long index);
    void close();
};


#endif // DEFS_HPP_INCLUDED
