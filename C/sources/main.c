#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "defs.h"

const char allowedkeys[] = "`1234567890-=qwertyuiop[]\\asdfghjkl;\'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>? ";
const size_t aklen = strlen(allowedkeys);

u_char __getch()
{
    while (1)
    {
        u_char kp = _getch();
        for (int i = 0; i < aklen; i++)
        {
            if (allowedkeys[i] == kp) return kp;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        printf("brainfucker file [filepath]\n");
        printf("brainfucker string [code]\n");
        return 0;
    }
    if (argc == 2)
    {
        printf("There has to be atleast 2 arguments passed!\n");
        return -1;
    }
    struct fsrhandl fsr = fsrcreate();

    if (!strcmp(argv[1], "string"))
    {
        fsrsopen(&fsr, argv[2], 0);
    }
    else if (!strcmp(argv[1], "file"))
    {
        if (!fsrfopen(&fsr, argv[2], 0))
        {
            printf("Error while opening file.\n");
            return -2;
        }
    }
    else
    {
        printf("Unknown mode %s", argv[1]);
        return -4;
    }

    unsigned int ui = 100;
    u_char *cells = malloc(sizeof(u_char)*ui);
    u_char *cp = cells;
    u_char *cend = cells + ui;
    for (unsigned int i = 0; i < ui; i++) cells[i] = 0;

    struct LiStack ls = LScreate();
    int gc = fsrgetc(&fsr);
    while (gc != -1)
    {
        char ic = (char)gc;
        //printf("POS=\"START LOOP\", VAR=\"ic\" : %c | VAR=\"gc\" : %i | VAR=\"*cp\" : %i | VAR=\"cp\" : %p\n", ic, gc, *cp, (void*)cp);
        if (ic == '+')
        {
            (*cp)++;
        }
        else if (ic == '-')
        {
            (*cp)--;
        }
        else if (ic == '>')
        {
            cp++;
            if (cp > cend) cp = 0;
        }
        else if (ic == '<')
        {
            cp--;
            if (cp < cells) cp = cend;
        }
        else if (ic == '.')
        {
            printf("%c", *cp);
        }
        else if (ic == ',')
        {
            *cp = __getch();
        }
        else if (ic == '[')
        {
            if (*cp != 0)
            {
                //printf("POS=\"OB/CPZ\" VAR=\"*cp\" : %i\n", *cp);
                LSpush(&ls, fsrtell(&fsr));
            }
            else
            {
                long bcounter = 0;
                int gc = fsrgetc(&fsr);
                while (gc != -1)
                {
                    ic = (char)gc;
                    //printf("POS=\"START SKIP LOOP\", VAR=\"ic : %c | VAR=\"gc\" : %i \n", ic, gc);
                    if (ic == '[') bcounter++;
                    if (ic == ']')
                    {
                        if (bcounter > 0) bcounter--;
                        else break;
                    }
                    gc = fsrgetc(&fsr);
                }
            }
        }
        else if (ic == ']')
        {
            if (*cp != 0)
            {
                //printf("[DEBUG] POS=\"CBF/NZ\"\n");
                fsrseek(&fsr, LStop(&ls));
            }
            else
            {
                //printf("[DEBUG] POS=\"CBF/Z\"\n");
                LSpop(&ls);
            }
        }
        gc = fsrgetc(&fsr);
    }

    fsrclose(&fsr);
    return 0;
}
