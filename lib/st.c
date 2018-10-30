#include "st.h"

struct st_symbol *st_symbol_table = NULL;
int line_number = 1;

struct usr_st_data* st_get_symbol(char *name)
{
    struct st_symbol* p = st_symbol_table;

    while (p != NULL) {
        if (!strcmp(name, p->name)) {
            return p->data;
        }
        p = p->next;
    }
    return NULL;
}

struct usr_st_data* st_define_or_ignore_symbol(char* name)
{
    struct usr_st_data* s = st_get_symbol(name);
    if (s == NULL) {
        s = st_define_symbol(name);
    }
    return s;
}

struct usr_st_data* st_define_symbol(char* name)
{
    struct st_symbol* symbol = (struct st_symbol*)malloc(sizeof(struct st_symbol));
    struct st_symbol* p;
    struct st_symbol* q;

    symbol->name = strdup(name);
    symbol->data = st_new_usr_data();
    symbol->data->name = symbol->name;
    symbol->id = 0;
    
    p = st_symbol_table;
    q = NULL;
    while (p != NULL) {
        q = p;
        p = p->next;
    }
    if (q == NULL) {
        st_symbol_table = symbol;
        symbol->id = 0;
    } else {
        q->next = symbol;
        symbol->id = q->id + 1;
    }

    return symbol->data;
}

struct usr_st_data* st_new_usr_data()
{
    return malloc(sizeof(struct usr_st_data));
}

void st_print_symbols(void (*f)(int id, struct usr_st_data* data))
{
    struct st_symbol* p = st_symbol_table;

    while (p != NULL) {
        f(p->id, p->data);
        p = p->next;
    }
}

int st_newline()
{
    return line_number++;
}

int st_line_number()
{
    return line_number;
}
