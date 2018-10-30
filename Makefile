.PHONY: tests all build flex bison clean

all: build clean

build: flex bison
	gcc -o bin/calc \
	 	lib/ast.c \
	 	lib/st.c \
	 	lib/array.c \
	 	src/fn.c \
	 	src/y.tab.c \
	 	src/lex.yy.c \
	 	src/main.c 

flex:
	flex -o src/lex.yy.c src/scanner.l

bison:
	bison -v -y -d src/parser.y -o src/y.tab.c

clean:
	rm src/lex.yy.c src/y.tab.c src/y.tab.h src/y.output
