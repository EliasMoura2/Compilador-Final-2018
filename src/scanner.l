                /*----------------COMPILADOR DRAGON----------------*/
                             /*ANALIZADOR LEXICO*/
 /*DECLARACIONES*/
%{
    /*CODIGO DE USUARIO*/
    #include "y.tab.h"
    #include <stdio.h>
    #include <stdlib.h>
    void yyerror(char *);

    int st_newline();
    int lexer_error(int line_number, char *lexem);
    extern int line_number;
%}

    /*DEFINICIONES: definicion de clases a expandir en los patrones*/
/*Para la definicion del programa*/
inicio          [iI][nN][iI][cC][iI][oO]
nom_programa    ([A-Z]{1}[a-zA-Z0-9_]*)
finprograma     [fF][iI][nN][pP][rR][oO][gG][rR][gG][rR][aA][mM][aA]
/*Para la definicion de las constantes*/
constantes		[cC][oO][nN][sS][tT][aA][nN][tT][eE][sS]
nom_const        ([A-Z]+[A-Z0-9_]*)
finconstantes	[fF][iI][nN][cC][oO][nN][sS][tT][aA][nN][tT][eE][sS]
/*Para la definicion de las variables*/
variables		[vV][aA][rR][iI][aA][bB][lL][eE][sS]
nom_var         ([a-z]+[a-zA-Z0-9_]*)
finvariables	[fF][iI][nN][vV][aA][rR][iI][aA][bB][lL][eE][sS]
/*Tipos de variables*/
tipo			[tT][iI][pP][oO]
numerico		[nN][uU][mM][eE][rR][iI][cC][oO]
cadena			[cC][aA][dD][eE][nN][aA]
/*Para la definicion de las sentencias*/
sentencias      [sS][eE][nN][tT][eE][nN][cC][iI][aA][sS]
finsentencias   [fF][iI][nN][sS][eE][nN][tT][eE][nN][cC][iI][aA][sS]
/*Estructura condicional*/
si		    	[sS][iI]
entonces        [eE][nN][tT][oO][nN][cC][eE][sS]
sino            [sS][iI][nN][oO]
finsi	    	[fF][iI][nN][sS][iI]
/*Estructura condicional switch*/
evaluar	    	[eE][vV][aA][lL][uU][aA][rR]
caso	    	[cC][aA][sS][oO]
otro	    	[oO][tT][rR][oO]
finevaluar  	[fF][iI][nN][eE][vV][aA][lL][uU][aA][rR]
/*Estructuras de ciclos*/
/*while*/
mientras    	[mM][iI][eE][nN][tT][rR][aA][sS]
finmientras 	[fF][iI][nN][mM][iI][eE][nN][tT][rR][aA][sS]
/*for*/
iterar	    	[iI][tT][eE][rR][aA][rR]
finiterar	    [fF][iI][nN][iI][tT][eE][rR][aA][rR]
/*imprime un mensaje por pantalla*/
imprimir		[iI][mM][pP][rR][iI][mM][iI][rR] 
/*imprime un mensaje del estado de la aplicación en el log del sistema o del runtime*/
bitacora		[bB][iI][tT][aA][cC][oO][rR][aA]
/*pide un valor al usuario y lo guarda en variable*/
leer			[lL][eE][eE][rR]
/*lee desde un archivo con formato valor1, valor2, valor3,.....,valorn y lo almacena en variable como un vector*/
cargar_vector	[cC][aA][rR][gG][aA][rR]_[vV][eE][cC][tT][oO][rR]

/* and y or*/
and			[aA][nN][dD]
or			[oO][rR]
/*numero entero o real con dos decimales*/
numero          (([+-][0-9]+\.[0-9]{2})|([0-9]+\.[0-9]{2})|([+-][0-9]+)|([0-9]+))
/*cadena*/
string          (\"[a-za-Z0-9]+\")
    /*CONDICIONES DE ARRANQUE*/


    /*DIRECTIVAS*/    
%option noyywrap

%%
 /*REGLAS*/
{numero}            {
                        yylval.numero = atof(yytext);
                        return NUM;
                    }
{string}            {
				        yylval.string = strdup(yytext);
				        return STRING;
                    }
{inicio}            {       return INICIO;         }
{nom_programa}      {       return NOMPROG;        }
{finprograma}       {       return FINPROG         }
{constantes}        {       return CONST;          }
{nom_const}         {
				        yylval.string = strdup(yytext);
				        return NOMCOST;
                    }
{finconstantes}     {       return FINCONST;       }
{variables}         {       return VARIABLE;       }
{nom_var}           {
				        yylval.string = strdup(yytext);
				        return NOMVAR;
                    }
{finvariables}      {        return FINVAR;        }	
{tipo}			    {        return TIPO;          }
{numerico}		    {        return NUMERICO;      }
{cadena}			{        return CADENA;        }
{sentencias}        {        return SENTENCIAS;    }
{finsentencias}     {        return FINSENT;       }
{si}                {        return SI;            }
{entonces}          {        return ENTONCES;      }
{sino}              {        return SINO;          }
{finsi}             {        return FINSI;         }    	
{evaluar}	    	{        return EVALUAR;       } 
{caso}	    	    {        return CASO;          } 
{otro}	    	    {        return OTRO;          } 
{finevaluar}  	    {        return FINEVALUAR;    } 
{mientras}    	    {        return MIENTRAS;      } 
{hacer}             {        return HACER;         } 
{finmientras}       {        return FINMIENTRAS;   }  	
{iterar}	        {        return ITERAR;        }             	
{finiterar}	        {        return FINITERAR;     }   
{imprimir}		    {        return IMPRIMIR;      } 
{bitacora}		    {        return BITACORA;      } 
{leer}			    {        return LEER;          } 
{cargar_vector}	    {        return CARGARVEC;     }
{AND}               {        return AND;           }
{OR}                {        return OR;            }  
"+"                 {        return SUMA;          }
"-"                 {        return RES;           }
"*"                 {        return MULT;          }
"/"                 {        return DIV;           }
"("                 {        return PARIZQ;        }
")"                 {        return PARDER;        }
"=="                {        return IGUAL;         }
"!="                {        return DISTINTO;      }
"<"                 {        return MENOR;         } 
">"                 {        return MAYOR;         } 
"<="                {        return MENOROIGUAL;   } 
">="                {        return MAYOROIGUAL;   }
":="                {        return ASIG;          }
"["                 {        return CORIZQ;        }
"]"                 {        return CORDER;        }
";"                 {        return PUNYCOM;       }
\n                  {
                        st_newline();
                        return NL;
                    }
[ \t]               ;
.                   {   return lexer_error(line_number, yytext);  }

%%
/*CODIGO DE USUARIO*/