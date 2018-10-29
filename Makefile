all: unclean clean

unclean: flex bison
	gcc y.tab.c lex.yy.c -o ejecutable -lm

flex:
	flex scanner.l

bison:
	bison -y -d parser.y

clean:
	rm lex.yy.c y.tab.c y.tab.h
