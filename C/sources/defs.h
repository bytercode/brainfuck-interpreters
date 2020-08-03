#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct fsrhandl
{
    short ttype;
    long index;
    FILE *file;
    char *buf;
};

struct fsrhandl fsrcreate();
_Bool fsrfopen(struct fsrhandl *fsr, const char *filename, _Bool is_bin);
_Bool fsrsopen(struct fsrhandl *fsr, const char *str, _Bool copy);
long fsrtell(struct fsrhandl *fsr);
_Bool fsrseek(struct fsrhandl *fsr, long index);
int fsrgetc(struct fsrhandl *fsr);
_Bool fsrclose(struct fsrhandl *fsr);

struct LiNode
{
    long val;
    struct LiNode *next;
    struct LiNode *prev;
};

struct LiStack
{
    struct LiNode *nbottom;
    struct LiNode *ntop;
    unsigned int size;
};

struct LiStack LScreate();
struct LiNode *LScreateNode(long val, struct LiNode *prev);
void LSdestroy(struct LiStack *ls);
long LStop(struct LiStack *ls);
void LSpush(struct LiStack *ls, long val);
long LSpop(struct LiStack *ls);

#endif // DEFS_H_INCLUDED
