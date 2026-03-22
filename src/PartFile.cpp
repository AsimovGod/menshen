// PartFile.cpp


// MainInclude.hpp
#include "MainInclude.hpp"



    void
FvFileRead(char* TcArgs)
{
    // declaration
    FILE* PfRead;

    // malloc
    char AcRead[2048];

    // stdio.h file
    PfRead = fopen(TcArgs, "r");

    if (PfRead == NULL) {
        fprintf(stderr, "\n\033[31mError: File not open!\033[0m\n\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(AcRead, sizeof(AcRead), PfRead)) {
        printf("%s", AcRead);
    }

    if (fclose(PfRead) != 0) {
        fprintf(stderr, "\n\033[31mError: File not close!\033[0m\n\n");
    }
}

