#include "defs.hpp"
#include <conio.h>

const char ak[] = "`1234567890-=qwertyuiop[]\\asdfghjkl;\'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>? ";
const size_t aklen = strlen(ak);

unsigned char __getch()
{
    while (1)
    {
        int kp = _getch();
        for (size_t i = 0; i < aklen; i++)
            if (kp == ak[i])
                return kp;
    }
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cout << "brainfuck file [filepath]" << std::endl;
        std::cout << "brainfuck string [bfcode]" << std::endl;
        return 0;
    }
    if (argc < 3)
    {
        std::cout << "There has to be atleast 2 arguments passed!" << std::endl;
        return -1;
    }

    fsrhandl handl;
    if (!strcmp(argv[1], "file"))
    {
        int rslt = handl.openfile(argv[2], 0);
        if (rslt == -1)
        {
            std::cout << "That file does not exists." << std::endl;
            return -1;
        }
        if (!rslt)
        {
            std::cout << "Error while opening file." << std::endl;
            return -1;
        }
    }
    else if (!strcmp(argv[1], "string"))
    {
        handl.openstring(argv[2]);
    }

    size_t cellssize = 100;
    unsigned char *cells = new unsigned char[cellssize];
    unsigned char *cend = cells + cellssize;
    unsigned char *cp = cells;
    for (size_t i = 0; i < cellssize; i++)
    {
        cells[i] = 0;
    }
    std::stack<unsigned long> sloop;

    short gc = handl.getach();
    while (gc != -1)
    {
        char ac = gc;
        //std::cout << "[DEBUG ON SL] " << ac << " TELL = " << handl.tell() << " CODE = " << gc << "*CP = " << static_cast<short>(*cp) << std::endl;
        switch (ac)
        {
        case '+':
            (*cp)++;
            break;
        case '-':
            (*cp)--;
            break;
        case '>':
            cp++;
            if (cp > cend) cp = cells;
            break;
        case '<':
            cp--;
            if (cp < cells) cp = cend;
            break;
        case '.':
            std::cout << *cp;
            break;
        case ',':
            *cp = __getch();
            break;
        case '[':
            {
                if (*cp != 0) sloop.push(handl.tell());
                else
                {
                    gc = handl.getach();
                    unsigned int bc = 0;
                    while (1)
                    {
                        ac = gc;
                        //std::cout << "[DEBUG ON SSL] " << ac << " TELL = " << handl.tell() << std::endl;
                        if (ac == '[') bc++;
                        if (ac == ']')
                        {
                            if (bc > 0) bc--;
                            else break;
                        }
                        gc = handl.getach();
                        if (gc != -1) goto ee;
                    }
                }
            }
            break;
        case ']':
            if (*cp != 0)
            {
                if (sloop.size() > 0) handl.seek(sloop.top());
            }
            else sloop.pop();
            break;
        }
        gc = handl.getach();
    }
    ee:;

    handl.close();
    return 0;
}
