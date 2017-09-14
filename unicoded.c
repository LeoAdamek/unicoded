#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

// ICU headers
#include <unicode/utypes.h>
#include <unicode/ustdio.h>

#define ARGUMENT_SPEC "hx:c:"


void show_usage(const int argc, const char** argv);
void print_codepoints();
void print_char_codepoint();

int main(const int argc, const char** argv) {
    int opt;

    while((opt = getopt(argc, (char* *const)argv, ARGUMENT_SPEC)) != -1) {
        switch(opt) {
        case 'x':
            print_codepoints();
            break;
        case 'c':
            print_char_codepoint();
            break;
        default:
            show_usage(argc, argv);
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}

/**
 * Show program usage
 */
void show_usage(const int argc, const char** argv) {
    fprintf(stderr,
            "Usage: %s [-x <CODEPOINT...>]\n",
            argv[0]
            );
}

/**
 * Read the given hex string as Unicode codepoints.
 * And print the corresponding unicode characters.
 *
 * Currently only supports UTF-16LE encoding.
 * 
 * @param codepoints Codepoint list.
 */
void print_codepoints() {
    size_t arg_len = strlen(optarg);
    size_t n_codepoints = arg_len>>2;
    size_t i;

    UFILE* u_stdout;

    UChar  c;
    UChar* message = (UChar*)calloc( n_codepoints+1 , sizeof(UChar));

    u_stdout = u_get_stdout();

    for (i = 0; i < n_codepoints; i++) {
        sscanf(optarg + (4*i), "%04hx", &message[i]);
    }

    u_fputs(message, u_stdout);

    free(message);
    free(u_stdout);
    
}


void print_char_codepoint() {
    // TODO
}
