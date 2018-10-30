#ifndef CYA_H
#define CYA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

#ifdef TEST
    #include "../tests/defs.h"
#else
    #include "../src/defs.h"
#endif

#include "st.h"
#include "ast.h"
#include "array.h"


void yyerror(char *);
int yylex();

#endif /* CYA_H */