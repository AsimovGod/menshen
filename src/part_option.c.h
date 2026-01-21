// part_option.c.h



    SaOption*
FsOptionInit()
{
    SaOption* CsOption;
    int DiOption;

    CsOption = g_new0(SaOption, 1);
    CsOption->option = g_new0(GOptionEntry, CsOption->optionN +1);

    DiOption = 0;
    CsOption->optionN = 3;

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

    return CsOption;
}


    int
FdOptionGlib(SaMap* CsMap, int DiArgs, char** TcArgs)
{
    SaInfo* CsInfo;
    SaOption* CsOption;
    bool DbExit;
    int DiArgument;
    char** TcArgument;
    GOptionContext* EgOptioncontext;

    CsInfo = CsMap->Info;
    CsOption = CsMap->Option;

    DbExit = FALSE;
    DiArgument = DiArgs;
    TcArgument = g_strdupv((char**)TcArgs);
    EgOptioncontext = g_option_context_new(NULL);

    g_option_context_set_help_enabled(EgOptioncontext, FALSE);
    g_option_context_add_main_entries(EgOptioncontext, CsOption->option, NULL);
    g_option_context_parse(EgOptioncontext, &DiArgument, &TcArgument, NULL);

    if (CsOption->version) {
        printf("\n%s\n", CsInfo->version);
        DbExit = TRUE;
    }

    if (CsOption->mode && g_strcmp0(CsOption->mode, "0") == 0) {
        FvUriPrint(DiArgument, TcArgument);
        DbExit = TRUE;
    }

    g_strfreev(TcArgument);

    if (DbExit) {
        exit(EXIT_SUCCESS);
    }
    else {
        return EXIT_SUCCESS;
    }
}


    int
FdOptionGtk(GApplication* EgApplication,
        GApplicationCommandLine* EgCommandline, void* PvUserdata)
{
    SaMap* CsMap;
    SaInfo* CsInfo;
    SaOption* CsOption;
    int DiArgument;
    char** TcArgument;

    CsMap = PvUserdata;
    CsInfo = CsMap->Info;
    CsOption = CsMap->Option;

    TcArgument = g_application_command_line_get_arguments(EgCommandline,
            &DiArgument);

    if (CsOption->mode && g_strcmp0(CsOption->mode, "1") == 0) {
        FvGtkWindow(CsMap, DiArgument, TcArgument);
    }

    return EXIT_SUCCESS;
}


    void
FvOptionFree(void* PvFree)
{
    SaOption* CsOption;

    CsOption = PvFree;

    if (! CsOption) return;

    g_free(CsOption->mode);
    g_free(CsOption->option);
    g_free(CsOption);
}

