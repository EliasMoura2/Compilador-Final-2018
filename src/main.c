#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "main.h"
#include "../lib/ast.h"
#include "fn.h"

int yyparse (void);
void print_node(struct ast_node* node);

/**
 * Manejador de errores léxicos
 *
 * @param  line_number
 * @param  lexem
 * @return
 */
int lexer_error(int line_number, char *lexem)
{
    printf("\nError léxico en la línea %d: '%s'\n", line_number, lexem);
    return -1;
}

/**
 * Manejador de errores sinácticos
 *
 * @param  line_number
 * @param  s
 * @return
 */
int syntax_error(int line_number, char *s)
{
    printf("\nError sintáctico en la línea %d (%s).\n", line_number, s);
    return -2;
}

void st_print(int id, struct usr_st_data* data)
{
    printf("    double %s = 0;\n", data->name);
}


void print_assign(struct ast_node* assign)
{
    print_node(ast_get_nth_child(assign, 0));
    printf(" = ");
    print_node(ast_get_nth_child(assign, 1));
}

void print_id(struct ast_node* id)
{
    printf("%s", id->data.id.id);
}

void print_const_number(struct ast_node* const_number)
{
    printf("%.02f", const_number->data.number);
}

void print_operation(struct ast_node* operation)
{
    struct ast_node* operand = ast_get_nth_child(operation, 0);

    printf("(");
    if (operand->data.operand == '^') {
        printf("pow(");
        print_node(ast_get_nth_child(operation, 1));
        printf(", ");
        print_node(ast_get_nth_child(operation, 2));
        printf(")");
    } else {
        print_node(ast_get_nth_child(operation, 1));
        print_node(operand);
        print_node(ast_get_nth_child(operation, 2));
    }
    printf(")");
}

void print_operand(struct ast_node* operand)
{
    printf(" %c ", operand->data.operand);
}

void print_expr(struct ast_node* expr)
{
    print_node(ast_get_nth_child(expr, 0));
}

void print_block(struct ast_node* block)
{
    struct ast_node* node = ast_get_nth_child(block, 0);
    printf("    printf(\"%%.02f\\n\", ");
    print_node(node);
    printf(");\n");
}

void print_blocks(struct ast_node* blocks)
{
    struct ast_node* block;
    int i = 0;
    while (NULL != (block = ast_get_nth_child(blocks, i++))) {
        print_node(block);
    }
}

void print_ast(struct ast_node* ast)
{

    printf("#include <stdio.h>\n");
    printf("#include <math.h>\n");
    printf("\n");
    printf("void main() {\n");
    st_print_symbols(st_print);
    print_node(ast);
    printf("\n}\n");
}

void print_node(struct ast_node* node)
{
    if (node != NULL) {
        switch (node->type) {
            case N_BLOCKS:
                print_blocks(node);
                break;
            case N_BLOCK:
                print_block(node);
                break;
            case N_EXPR:
                print_expr(node);
                break;
            case N_OPERAND:
                print_operand(node);
                break;
            case N_OPERATION:
                print_operation(node);
                break;
            case N_CONST_NUMBER:
                print_const_number(node);
                break;
            case N_ID:
                print_id(node);
                break;
            case N_ASSIGN:
                print_assign(node);
                break;
        }
    }
}



int main(int argc, char **argv)
{
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
    }

    if (yyparse()) {
        return 1;
    }
    printf("\n\n");

    print_ast(ast);

    // printf("\n\n");
    // st_print_symbols(st_print);
    // printf("\n\n");

    return 0;
}
