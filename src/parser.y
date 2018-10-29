%{
	#include <stdio.h>
    #include "../lib/cya.h"
    #include "fn.h"
    #include <string.h>
	#include <math.h>
	#include <float.h>	// para DBL_MAX
	void yyerror(char *);
	int yylex(void);

	double getVal(char *);
	double setVal(char *, double);

	int numLinea = 1;

	struct entrada {
		char *id;
		double value;
	};

	#define TABLA_MAX_CUENTA 10
	struct entrada tabla[TABLA_MAX_CUENTA];
	int tabla_cuenta = 0;

%}
    /*DECLARACIONES DE YACC/BISON*/
%union {
	double  real;
    string    *string;
}
    /*TERMINALES*/
%token <real> NUM
%token <string> STRING NOMPROG NOMCONST NOMVAR
%token INICIO  FINPROG CONST  FINCONST VARIABLE FINVAR TIPO NUMERICO CADENA SENTENCIAS 
%token FINSENT SI ENTONCES SINO FINSI EVALUAR CASO OTRO FINEVALUAR  MIENTRAS HACER FINMIENTRAS 
%token ITERAR FINITERAR IMPRIMIR BITACORA LEER CARGARVEC AND OR SUMA RES MULT DIV PARIZQ PARDER 
%token IGUAL DISTINTO MENOR MAYOR MENOROIGUAL MAYOROIGUAL ASIG CORIZQ CORDER PUNYCOM NL

%type <real> expresion

    /*PRECEDENCIA Y ASOCIACION*/
%left ASIG
%left MAS MEN
%left POR DIV
%left POT

    /*SIMBOLO DE ARRANQUE*/
%start sigma

 /*REGLAS*/
%% 
sigma: lineas
     ;

lineas: linea lineas
      | /*lambda*/
      ;

linea: expresion NL { printf("El resultado es: %0.2f\n", $1); }
 	 | expresion error NL	{}
	 | error NL				{}

expresion: NUM                      { printf("El numero: %0.2f\n", $1); }
         | ID                       { $$ = getVal($1); printf("El id: %s\n",$1); }
         | MEN expresion            { $$ = -$2; printf("(-)\n");	}
         | expresion MAS expresion  { $$ = $1 + $3; printf("+\n");	}
         | expresion MEN expresion  { $$ = $1 - $3; printf("-\n"); }
         | expresion POR expresion  { $$ = $1 * $3; printf("*\n"); }
         | expresion DIV expresion  {
		 								if ($3 == 0) {
		 									if($1 < 0) {
		 										$$ = -INFINITY;
		 									} else {
		 										$$ = INFINITY;
		 									}
		 								} else {
			 								$$ = $1 / $3;
			 							}
                                        printf("/\n");
		 							}
         | expresion POT expresion  { $$ = pow($1,$3); printf("^\n"); }
         | LPAR expresion RPAR      { $$ = $2; printf("()n"); }
         | ID ASIG expresion	    { $$ = setVal($1, $3); printf("la variable %s\n",$1); }
         ;


sigma           :       INICIO NOMPROG T_DOSPUNTOS T_LLAVEAB/*llave abierta*/ T_CUERPO T_LLAVECE/*llave cerrada*/
T_CUERPO        :       i_const FINCONST i_variable FINVAR SENTENCIAS FINSENT
i_const         :       CONST TIPO NOMCONST
i_variable      :       VARIABLE TIPO NOMVAR
SENTENCIAS      :       lineas
lineas          :       linea lineas
linea           :       expresion           
                |       si //if
                |       mientras //while

si              :       SI expresion ENTONCES T_DOSPUNTOS lineas
sino            :       SINO ENTONCES T_DOSPUNTOS lineas
mientras        :       T_MIENTRAS expresion T_DOSPUNTOS
entonces        :       T_LLAVEAB lineas T_LLAVECE
expresion       :       expresion SUMA expresion
                |       expresion RES expresion
                |       expresion DIV expresion
                |       expresion MULT expresion
                |       expresion MENOR expresion
                |       expresion MENOROIGUAL expresion
                |       expresion MAYOR expresion
                |       expresion MAYOROIGUAL expresion
                |       expresion IGUAL expresion
                |       expresionDISTINTO expresion
                |       expresion T_AND expresion
                |       expresion T_OR expresion
                |       PARIZQ expresion PARDER

%%
 /*CODIGO DE USUARIO*/
void yyerror(char *s)
{
	printf("ERROR SINTACTICO en la linea %d\n", numLinea);
}

int main(void)
{
	printf("\nCALCULADORA VI\n");
	yyparse();
}

double getVal(char *id)
{
	int i;
	for (i = 0; i < tabla_cuenta; i++) {
		if (strcmp(tabla[i].id, id) == 0) {
			return tabla[i].value;
		}
	}
	printf("Advertencia: variable '%s' no definida. Se utiliza 0.\n", id);
	return 0;
}

double setVal(char *id, double value)
{
	int i;
	for (i = 0; i < tabla_cuenta; i++) {
		if (strcmp(tabla[i].id, id) == 0) {
			tabla[i].value = value;
			return value;
		}
	}
	if (tabla_cuenta >= TABLA_MAX_CUENTA) {
		printf("Advertencia: ya no se pueden definir variables.\n");
	} else {
		int p = tabla_cuenta;

		tabla[p].id = id;
		tabla[p].value = value;

		tabla_cuenta += 1;
	}
	return value;
}