#ifndef ST_H
#define ST_H

#include "cya.h"

struct st_symbol {
    int id;
    char* name;
    struct usr_st_data *data;
    struct st_symbol* next;
};

extern struct st_symbol *st_symbol_table;

struct usr_st_data* st_get_symbol(char *name);
struct usr_st_data* st_define_symbol(char* name);
struct usr_st_data* st_define_or_ignore_symbol(char* name);
struct usr_st_data* st_new_usr_data();
void st_print_symbols();

int st_line_number();
int st_newline();

int lexer_error(int line_number, char *lexem);
int syntax_error(int line_number, char *s);

#endif /* ST_H */