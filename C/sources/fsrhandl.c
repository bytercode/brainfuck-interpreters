#include "defs.h"

struct fsrhandl fsrcreate()
{
    struct fsrhandl rslt;
    rslt.ttype = 0;
    rslt.index = 0;
    rslt.file = NULL;
    rslt.buf = NULL;
    return rslt;
}

_Bool fsrfopen(struct fsrhandl *fsr, const char *filename, _Bool is_bin)
{
    if (fsr->ttype != 0) return 0;
    fsr->ttype = 1;
    FILE *temp = fopen(filename, is_bin ? "rb" : "r");
    if (temp == NULL)
    {
        fsr->ttype = 0;
        return 0;
    }
    fsr->file = temp;
    return 1;
}

_Bool fsrsopen(struct fsrhandl *fsr, const char *str, _Bool copy)
{
    if (fsr->ttype != 0) return 0;
    fsr->ttype = 2;
    fsr->index = 0;
    if (copy)
    {
        fsr->buf = malloc(strlen(str));
        strcpy(fsr->buf, str);
        return 1;
    }
    fsr->buf = str;
    return 1;
}

long fsrtell(struct fsrhandl *fsr)
{
    switch (fsr->ttype)
    {
    case 1:
        return ftell(fsr->file);
    case 2:
        return fsr->index;
    }
    return 0;
}

_Bool fsrseek(struct fsrhandl *fsr, long index)
{
    switch (fsr->ttype)
    {
    case 1:
        fseek(fsr->file, index, SEEK_SET);
        return 1;
    case 2:
        fsr->index = index;
        return 1;
    }
    return 0;
}

int fsrgetc(struct fsrhandl *fsr)
{
    switch (fsr->ttype)
    {
    case 2:
        {
            char rslt = fsr->buf[fsr->index++];
            if (rslt == 0) return -1;
            return rslt;
        }
    case 1:
        return fgetc(fsr->file);
    }
    return '\x00';
}

_Bool fsrclose(struct fsrhandl *fsr)
{
    switch (fsr->ttype)
    {
    case 1:
        fclose(fsr->file);
        fsr->file = NULL;
        return 1;
    case 2:
        free(fsr->buf);
        return 1;
    }
    return 0;
}
