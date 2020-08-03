#include "defs.h"

struct LiStack LScreate()
{
    struct LiStack rslt = {NULL, NULL, 0};
    return rslt;
};

struct LiNode *LScreateNode(long val, struct LiNode *prev)
{
    struct LiNode *rslt = malloc(sizeof(struct LiNode));
    rslt->next = NULL;
    rslt->prev = prev;
    rslt->val = val;
    return rslt;
};

void LSdestroy(struct LiStack *ls)
{
    while (ls->size > 0) LSpop(ls);
}

long LStop(struct LiStack *ls)
{
    if (ls->size == 0) return 0;
    return ls->ntop->val;
}

void LSpush(struct LiStack *ls, long val)
{
    struct LiNode *rslt = LScreateNode(val, ls->ntop);
    if (ls->size++ == 0)
    {
        ls->ntop = rslt;
        ls->nbottom = rslt;
        return;
    }
    ls->ntop->next = rslt;
    ls->ntop = rslt;
}

long LSpop(struct LiStack *ls)
{
    if (ls->size == 0)
    {
        return 0;
    }
    long rv = ls->ntop->val;
    struct LiNode *prev = ls->ntop->prev;
    free(ls->ntop);
    ls->ntop = prev;
    ls->size--;
    if (prev == NULL) ls->nbottom = prev;
    else prev->next = NULL;
    return rv;
}
