

bin:
	gcc test.c argument_parser.c string_t.c vector.c -o test 

run: bin
	./test

all: bin
