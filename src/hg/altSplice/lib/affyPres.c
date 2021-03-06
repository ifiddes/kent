/* affyPres.c was originally generated by the autoSql program, which also 
 * generated affyPres.h and affyPres.sql.  This module links the database and
 * the RAM representation of objects. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "affyPres.h"


struct affyPres *affyPresLoad(char **row)
/* Load a affyPres from row fetched with select * from affyPres
 * from database.  Dispose of this with affyPresFree(). */
{
struct affyPres *ret;
int sizeOne,i;
char *s;

AllocVar(ret);
ret->valCount = sqlSigned(row[2]);
ret->callCount = sqlSigned(row[4]);
ret->probeId = cloneString(row[0]);
ret->info = cloneString(row[1]);
sqlFloatDynamicArray(row[3], &ret->vals, &sizeOne);
assert(sizeOne == ret->valCount);
sqlStringDynamicArray(row[5], &ret->calls, &sizeOne);
assert(sizeOne == ret->callCount);
return ret;
}

struct affyPres *affyPresLoadAll(char *fileName) 
/* Load all affyPres from a tab-separated file.
 * Dispose of this with affyPresFreeList(). */
{
struct affyPres *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[6];

while (lineFileRow(lf, row))
    {
    el = affyPresLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct affyPres *affyPresCommaIn(char **pS, struct affyPres *ret)
/* Create a affyPres out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new affyPres */
{
char *s = *pS;
int i;

if (ret == NULL)
    AllocVar(ret);
ret->probeId = sqlStringComma(&s);
ret->info = sqlStringComma(&s);
ret->valCount = sqlSignedComma(&s);
s = sqlEatChar(s, '{');
AllocArray(ret->vals, ret->valCount);
for (i=0; i<ret->valCount; ++i)
    {
    ret->vals[i] = sqlFloatComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
ret->callCount = sqlSignedComma(&s);
s = sqlEatChar(s, '{');
AllocArray(ret->calls, ret->callCount);
for (i=0; i<ret->callCount; ++i)
    {
    ret->calls[i] = sqlStringComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
*pS = s;
return ret;
}

void affyPresFree(struct affyPres **pEl)
/* Free a single dynamically allocated affyPres such as created
 * with affyPresLoad(). */
{
struct affyPres *el;

if ((el = *pEl) == NULL) return;
freeMem(el->probeId);
freeMem(el->info);
freeMem(el->vals);
/* All strings in calls are allocated at once, so only need to free first. */
if (el->calls != NULL)
    freeMem(el->calls[0]);
freeMem(el->calls);
freez(pEl);
}

void affyPresFreeList(struct affyPres **pList)
/* Free a list of dynamically allocated affyPres's */
{
struct affyPres *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    affyPresFree(&el);
    }
*pList = NULL;
}

void affyPresOutput(struct affyPres *el, FILE *f, char sep, char lastSep) 
/* Print out affyPres.  Separate fields with sep. Follow last field with lastSep. */
{
int i;
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->probeId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->info);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->valCount);
fputc(sep,f);
if (sep == ',') fputc('{',f);
for (i=0; i<el->valCount; ++i)
    {
    fprintf(f, "%f", el->vals[i]);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
fputc(sep,f);
fprintf(f, "%d", el->callCount);
fputc(sep,f);
if (sep == ',') fputc('{',f);
for (i=0; i<el->callCount; ++i)
    {
    if (sep == ',') fputc('"',f);
    fprintf(f, "%s", el->calls[i]);
    if (sep == ',') fputc('"',f);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

