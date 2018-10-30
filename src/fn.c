#include "fn.h"

struct ast_node* n_assign(char* id, struct ast_node* expr)
{
    struct ast_node* assign = ast_new_node(N_ASSIGN);
    ast_add_child(assign, n_id(id, 0));
    ast_add_child(assign, expr);

    return assign;
}