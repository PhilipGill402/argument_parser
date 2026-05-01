

bin:
	gcc test.c argument_parser.c -o test 

run: bin
	./test

all: bin
