#ifndef FN_H
#define FN_H

#include "../lib/ast.h"

#define N_ASSIGN                1


struct ast_node* n_assign(char* id, struct ast_node* expr);

#endif /* FN_H */