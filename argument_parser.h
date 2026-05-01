#ifndef ARGUMENT_PARSER_H_
#define ARGUMENT_PARSER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

void get_args(char* line);
int is_arg(char arg);

#endif // !ARGUMENT_PARSER_H_
