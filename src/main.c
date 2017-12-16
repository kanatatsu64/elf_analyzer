#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/elf.h>

#include "elf_analyzer.h"
#include "analy_ctrl.h"

int
load() {
    load_ehdr();
    load_ptbl();
    load_stbl();
    load_shstr();
    return 0;
}

int
release() {
    release_ehdr();
    release_ptbl();
    release_stbl();
    return 0;
}

int
main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "No input file\n");
        return -1;
    }

    char *fname = argv[1];
    if (elf_open(fname) == -1) {
        return -1;
    }

    load();
    if (argc == 2)
        repl();
    else {
        if (argc-2 > MAX_TOK_NUM)
            fprintf(stderr, "Too many arguments\n");
        char cmds[MAX_CMD_LEN][MAX_TOK_NUM] = {{0}};
        for (int i=0; i<argc-2; i++)
            strcpy(cmds[i], argv[i+2]); 
        eval(cmds);
    }

    release();

    close_elf();

    return 0;
}
