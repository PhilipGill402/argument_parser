#ifndef ARGUMENT_PARSER_H_
#define ARGUMENT_PARSER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include "string_t.h"

#define get_args(line) _Generic((line), \
        char *: get_args_cstr, \
        string_t *: get_args_str, \
        default: get_args_cstr \
    )(line)

void get_args_str(string_t* line);
void get_args_cstr(char* line);
int is_arg(char arg);

#endif // !ARGUMENT_PARSER_H_
