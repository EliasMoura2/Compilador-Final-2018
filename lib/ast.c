#include "ast.h"

int ast_node_count = 0;

struct ast_node* ast_get_nth_child(struct ast_node* parent, int nth)
{
    struct ast_child_list* p;

    p = parent->children;

    while (nth > 0) {
        if (p == NULL) {
            return NULL;
        }
        p = p->next;
        nth--;
    }
    if (p != NULL) {
        return p->node;
    }
    return NULL;
}

struct ast_node* ast_add_child_first(struct ast_node* parent, struct ast_node* child)
{
    struct ast_child_list* list_item = malloc(sizeof(struct ast_child_list));
    struct ast_child_list* p = parent->children;
    struct ast_child_list* q = NULL;

    child->parent = parent;
    list_item->node = child;
    list_item->prev = NULL;
    list_item->next = parent->children;
    parent->children = list_item;
}

struct ast_node* ast_add_child(struct ast_node* parent, struct ast_node* child)
{
    struct ast_child_list* list_item = malloc(sizeof(struct ast_child_list));
    struct ast_child_list* p = parent->children;
    struct ast_child_list* q = NULL;

    child->parent = parent;
    list_item->node = child;
    list_item->prev = NULL;
    list_item->next = NULL;

    while (p != NULL) {
        q = p;
        p = p->next;
    }
    if (q == NULL) {
        parent->children = list_item;
    } else {
        list_item->prev = q;
        q->next = list_item;
    }
}

struct ast_node* ast_new_node(int type)
{
    struct ast_node* node = malloc(sizeof(struct ast_node));
    node->id = ++ast_node_count;
    node->type = type;
    node->children = NULL;
    node->level = 0;

    return node;
}

void ast_print_node(struct ast_node* node)
{
    printf("[node#%03d:%02d]", node->id, node->type);
}

void ast_print_tabs(int level)
{
    for (int i = level * 4; i > 0; i--) {
        printf(" ");
    }
}

void ast_print_tree(struct ast_node* node, int level, void (*fn)(int type, union usr_ast_data* data, int level))
{
    printf("1.");
    if (!node) {
        return;
    }
    ast_print_tabs(level);
    ast_print_node(node);
    printf("\n");
    fn(node->type, &node->data, level);
    printf("\n");

    struct ast_child_list *p = node->children;
    while (p != NULL) {
        ast_print_tree(p->node, level + 1, fn);
        p = p->next;
    }
}


void ast_walk_depth_first(struct ast_node* node, void (*fn)(int type, union usr_ast_data* data, int level))
{
    struct ast_child_list *child;

    (*fn)(node->type, &(node->data), node->level);

    child = node->children;
    while (child != NULL) {
        ast_walk_depth_first(child->node, fn);
        child = child->next;
    }
}

void tabs(int level)
{
    level--;
    while(level-- > 0) {
        printf("│  ");
    }
    printf("├─ ");
}



struct ast_node* n_block(struct ast_node* block)
{
    struct ast_node* node = ast_new_node(N_BLOCK);

    ast_add_child(node, block);
    
    return node;
}

struct ast_node* n_blocks(struct ast_node* block1, struct ast_node* block2)
{
    if (block1 == NULL && block2 != NULL) {
        block1 = block2;
        block2 = NULL;
    }

    struct ast_node* node = NULL;

    if (block1 != NULL && block1->type == N_BLOCKS) {
        node = block1;
        block1 = block2;
        block2 = NULL;
    } else {
        node = ast_new_node(N_BLOCKS);
    }

    if (block1 != NULL) {
        ast_add_child(node, block1);
    }
    if (block2 != NULL) {
        if (block2->type == N_BLOCKS) {
            int i = 0;
            while (NULL != (block1 = ast_get_nth_child(block2, i++))) {
                ast_add_child(node, block1);
            }
        } else {
            ast_add_child(node, block2);
        }
    }

    return node;
}

struct ast_node* n_id(char* id, int type)
{
    struct ast_node* node;
    
    node = ast_new_node(N_ID);
    node->data.id.id = strdup(id);
    node->data.id.type = type;

    st_define_or_ignore_symbol(id);

    return node;
}

struct ast_node* n_const_string(char* string)
{
    struct ast_node* node = ast_new_node(N_CONST_STRING);
    node->data.string = strdup(string);
    return node;
}

struct ast_node* n_const_number(double number)
{
    struct ast_node* node = ast_new_node(N_CONST_NUMBER);
    node->data.number = number;
    return node;
}

struct ast_node* n_const_boolean(int boolean)
{
    struct ast_node* node = ast_new_node(N_CONST_BOOLEAN);
    node->data.boolean = boolean;
    return node;
}

struct ast_node* n_operand(int operand)
{
    struct ast_node* node = ast_new_node(N_OPERAND);
    node->data.operand = operand;

    return node;
}

struct ast_node* n_expr(struct ast_node* node)
{
    struct ast_node* expr;
    if (node->type != N_EXPR) {
        expr = ast_new_node(N_EXPR);
        ast_add_child(expr, node);
    } else {
        expr = node;
    }
    return expr;
}


struct ast_node* n_operation(struct ast_node* operand, struct ast_node* expr1, struct ast_node* expr2)
{
    struct ast_node* expr;

    expr = ast_new_node(N_OPERATION);

    expr1 = n_expr(expr1);
    if (expr2 != NULL) {
        expr2 = n_expr(expr2);
    }

    ast_add_child(expr, operand);
    ast_add_child(expr, expr1);
    if (expr2 != NULL) {
        ast_add_child(expr, expr2);
    }

    return expr;
}
