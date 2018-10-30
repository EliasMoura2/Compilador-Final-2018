#ifndef AST_H
#define AST_H

#include "cya.h"

#define N_BLOCK                 1001
#define N_BLOCKS                1002
#define N_ID                    1003
#define N_CONST_STRING          1004
#define N_CONST_NUMBER          1005
#define N_CONST_BOOLEAN         1006
#define N_OPERAND               1007
#define N_OPERATION             1008
#define N_EXPR                  1009


struct ast_child_list {
    struct ast_node* node;

    struct ast_child_list* prev;
    struct ast_child_list* next;
};

struct ast_node {
    int id;
    int type;
    int level;

    union usr_ast_data data;

    struct ast_node* parent;
    struct ast_child_list* children;
} ;

extern int ast_node_count;


struct ast_node* ast_get_nth_child(struct ast_node* parent, int nth);
struct ast_node* ast_new_node(int type);
struct ast_node* ast_add_child_first(struct ast_node* parent, struct ast_node* child);
struct ast_node* ast_add_child(struct ast_node* parent, struct ast_node* child);
void ast_print_node(struct ast_node* node);
void ast_print_tabs(int level);
void ast_print_tree(struct ast_node* node, int level, void (*fn)(int type, union usr_ast_data* data, int level));
void ast_walk_depth_first(struct ast_node* node, void (*f)(int type, union usr_ast_data* data, int level));

void tabs(int level);

/**
 * Crea un nodo para un bloque
 */
struct ast_node* n_block(struct ast_node* block);

/**
 * Crea un nodo para mantener una sucesion de bloques
 */
struct ast_node* n_blocks(struct ast_node* block1, struct ast_node* block2);

/**
 * Crea un nodo para un identificador
 */
struct ast_node* n_id(char* id, int type);

/**
 * Nodo de constante de cadena de caracteres
 */
struct ast_node* n_const_string(char* string);

/**
 * Node de constante numérica
 */
struct ast_node* n_const_number(double number);
//recibe un numero y devuelve un puntero a nodo que se pasa al padre en el a.lexico 
/**
 * Nodo de constante booleana
 */
struct ast_node* n_const_boolean(int boolean);

/**
 * Nodo de operando
 */
struct ast_node* n_operand(int operand);

/**
 * Nodo de operación
 */
struct ast_node* n_operation(struct ast_node* operand, struct ast_node* expr1, struct ast_node* expr2);

/**
 * Nodo de expresion
 */
struct ast_node* n_expr(struct ast_node* node);

#endif /* AST_H */