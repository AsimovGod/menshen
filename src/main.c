#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <argtable2.h>

#include "part_show.h"
#include "part_gtk.h"



    int
main(int ViArgs, char *AcArgs[])
{
    int ViLoop;
    int ViArgtStat;
    int ViExitMain;
    int ViArgMinGtk;
    int ViArgGtk;
    char **AcArgGtk;

    struct arg_lit *SuArgtVersion;
    struct arg_lit *SuArgtHelp;
    struct arg_lit *SuArgtWindow;
    struct arg_str *SuArgtUrl;
    struct arg_str *SuArgtNull;
    struct arg_end *SuArgtEnd;

    void *TvArgtable[] = {
        SuArgtVersion   =   arg_lit0("v",   "version",
                "Version"),
        SuArgtHelp      =   arg_lit0("h",   "help",
                "Help"),
        SuArgtWindow    =   arg_lit0("w",   "window",
                "Window"),
        SuArgtUrl       =   arg_str0("u",   "url",
                "<string>",     "Url"),
        SuArgtNull      =   arg_strn(NULL,  NULL,
                NULL,     0,      ViArgs,     "NULL"),
        SuArgtEnd       =   arg_end(20)
    };

    ViExitMain = EXIT_SUCCESS;
    ViArgtStat = arg_parse(ViArgs, AcArgs, TvArgtable);

    ViArgMinGtk = ViArgs;
    ViArgGtk = 0;
    AcArgGtk = malloc(ViArgs * sizeof(char *));
    AcArgGtk[0] = AcArgs[0];

    if (SuArgtVersion->count >0) {
        printf("Version");
        return ViExitMain;
    }

    if (SuArgtUrl->count > 0) {
        printf("Url: %s\n", SuArgtUrl->sval[0]);
    }

    if (SuArgtHelp->count >0){
        AcArgGtk[1] = "--help";
        ViArgMinGtk = 2;
    }
    else if (SuArgtWindow->count >0) {
        ViArgMinGtk = 1;
    }

    ViArgGtk = ViArgMinGtk;

    for (ViLoop = 0; ViLoop < SuArgtNull->count; ViLoop++) {
        AcArgGtk[ViArgGtk] = strdup(SuArgtNull->sval[ViLoop]);
        ViArgGtk++;
    }

    if (ViArgGtk > 0) {
        ViExitMain = FiGtk(ViArgGtk, AcArgGtk);
    }

    for (ViLoop = ViArgMinGtk; ViLoop < SuArgtNull->count; ViLoop++) {
        free(AcArgGtk[ViLoop]);
    }

    return ViExitMain;
}
