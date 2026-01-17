// part_file.h



    void
FvFileRead(char* AcArgShow)
{
    char VcFileShow[2048];

    FILE* UpFileShow;

    UpFileShow = fopen(AcArgShow, "r");

    if (UpFileShow == NULL) {
        fprintf(stderr,
                "\n\033[31mError: File not open!\033[0m\n\n");

        exit(EXIT_FAILURE);
    }

    while (fgets(VcFileShow, sizeof(VcFileShow), UpFileShow)) {
        printf("%s", VcFileShow);
    }

    if (fclose(UpFileShow) != 0) {
        fprintf(stderr,
                "\n\033[31mError: File not close!\033[0m\n\n");
    }
}

