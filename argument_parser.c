#include "argument_parser.h"

// allocates 7 bytes (56 bits) which is more than we need
// first 24 bits are for lower case, last 24 bits are for upper case
static uint64_t bitmap = 0;

static inline void bitmap_set(int idx) {
    bitmap |= (1 << idx);
}

static inline int bitmap_get(int idx) {
    return (bitmap & (1 << idx)) != 0;
}

void get_args_cstr(char* line) {
    char* args = malloc(strlen(line));
    strcpy(args, line);

    // first one should be a command so skip it
    char* arg = strtok(args, " ");
    arg = strtok(NULL, " ");

    do {
        // skip '-'
        arg++;
        
        for (int i = 0; i < strlen(arg); i++) {
            char c = arg[i];
            int idx;

            if (isupper(c)) {
                idx = 26 + c - 'A';
            } else if (islower(c)) {
                idx = c - 'a';
            } else {
                continue;
            }
            
            bitmap_set(idx);
        }

        arg = strtok(NULL, " ");
    } while (arg != NULL);

}

int is_arg(char arg) {
    int idx;

    if (isupper(arg)) {
        idx = 26 + arg - 'A';
    } else if (islower(arg)) {
        idx = arg - 'a';
    } else {
        return 0;
    }
    
    return bitmap_get(idx);
}

