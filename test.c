#include "argument_parser.h"

int main() {
    char* line = "ls -abc -j -p -D";
    
    get_args(line);

    printf("%d\n", is_arg('d'));
    printf("%d\n", is_arg('b'));
    printf("%d\n", is_arg('D'));
}
