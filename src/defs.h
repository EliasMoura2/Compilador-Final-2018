#ifndef DEFS_H
#define DEFS_H

#include "y.tab.h"

/**
 * Estructura de los elementos de la Tabla de Simbolos (ST)
 * 
 * Como mínimo debe tener un campo name (que no puede ser renombrado) en el que se
 * almacena el nombre del símbolo. Luego, los demás campos deben definirse conforme
 * a la necesidad de cada desarrollo.
 */
struct usr_st_data {//de la tabla de simbolos, los simbolos se buscan por nombre
    char* name;
    int type;
};

/**
 * Estructura de los nodos del Árbol de Análisis Sintáctico (AST)
 *
 * Los campos que se definen deben comprender los posibles valores que requieran
 * para conformar los diversos tipos de nodos del AST.
 */
union usr_ast_data {//datos del arbol sintactico
    struct ast_node* node;
    struct {
        char* id;
        int type;
    } id;
    char* string;
    double number;
    int boolean;
    int operand;//agrego una linea por cada tipo de dato que necesito
};

struct ast_node *ast;   //cabecera del arbol, usada para empezar el recorrido

#include "../lib/cya.h"

#endif /* DEFS_H */