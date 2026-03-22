// PartOption.cpp


// MainInclude.hpp
#include "MainInclude.hpp"



struct SaOption {
    // glib.h option
    GOptionEntry* option;
    // declaration
    int optionN;
    bool version;
    char* mode;
};



    SaOption*
FsOptionInit()
{
    // declaration
    SaOption* CsOption;
    int DiOption;

    // variable
    DiOption = 0;

    // malloc
    CsOption = g_new0(SaOption, 1);
    CsOption->optionN = 3;
    CsOption->option = g_new0(GOptionEntry, CsOption->optionN + 1);

    // glab.h option
    CsOption->version = FALSE;
    CsOption->option[DiOption].long_name = "version";
    CsOption->option[DiOption].short_name = 'v';
    CsOption->option[DiOption].arg = G_OPTION_ARG_NONE;
    CsOption->option[DiOption].arg_data = &CsOption->version;
    CsOption->option[DiOption].description = "Version";
    DiOption = DiOption + 1;

    CsOption->mode = g_strdup("1");
    CsOption->option[DiOption].long_name = "mode";
    CsOption->option[DiOption].short_name = 'm';
    CsOption->option[DiOption].arg = G_OPTION_ARG_STRING;
    CsOption->option[DiOption].arg_data = &CsOption->mode;
    CsOption->option[DiOption].description = "Mode";
    DiOption = DiOption + 1;

    CsOption->option[DiOption].long_name = NULL;

    // return
    return CsOption;
}


    int
FdOptionGlib(SaMap* CsMap, int DiArgs, char** TcArgs)
{
    // declaration
    SaInfo* CsInfo;
    SaOption* CsOption;
    bool DbExit;
    int DiArgument;
    char** TcArgument;
    GOptionContext* EgOptioncontext;

    // inherit
    CsInfo = CsMap->Info;
    CsOption = CsMap->Option;

    // variable
    DbExit = FALSE;
    DiArgument = DiArgs;

    // malloc
    TcArgument = g_strdupv((char**)TcArgs);
    EgOptioncontext = g_option_context_new(NULL);

    // glib.h option
    g_option_context_set_help_enabled(EgOptioncontext, FALSE);
    g_option_context_add_main_entries(EgOptioncontext, CsOption->option, NULL);
    g_option_context_parse(EgOptioncontext, &DiArgument, &TcArgument, NULL);

    // if glib.h option
    if (CsOption->version) {
        // block stdio.h printf
        printf("\n%s\n", CsInfo->version);
        DbExit = TRUE;
    }

    if (CsOption->mode && g_strcmp0(CsOption->mode, "0") == 0) {
        // block PartGuri.cpp
        FvUriPrint(DiArgument, TcArgument);
        DbExit = TRUE;
    }

    // free
    g_option_context_free(EgOptioncontext);
    g_strfreev(TcArgument);

    // if exit
    if (DbExit) {
        // block free
        FvOptionFree(CsOption);
        FvInfoFree(CsInfo);
        FvMapFree(CsMap);
        // block exit
        exit(EXIT_SUCCESS);
    }
    else {
        // block return
        return EXIT_SUCCESS;
    }
}


    int
FdOptionGtk(GApplication* EgApplication,
        GApplicationCommandLine* EgCommandline, void* PvUserdata)
{
    // declaration
    SaMap* CsMap;
    SaOption* CsOption;
    int DiArgument;
    char** TcArgument;

    // inherit
    CsMap = PvUserdata;
    CsOption = CsMap->Option;

    // gio.h application
    TcArgument = g_application_command_line_get_arguments(EgCommandline,
            &DiArgument);

    // if glib.h option
    if (CsOption->mode && g_strcmp0(CsOption->mode, "1") == 0) {
        // block PartWindow.cpp
        FvGtkWindow(CsMap, DiArgument, TcArgument);
    }

    // return
    return EXIT_SUCCESS;
}


    void
FvOptionFree(void* PvFree)
{
    // declaration
    SaOption* CsOption;

    // inherit
    CsOption = PvFree;

    if (! CsOption) return;

    // free
    g_free(CsOption->mode);
    g_free(CsOption->option);
    g_free(CsOption);
}

