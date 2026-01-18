// part_option.h



    SaOption*
FsOptionInit()
{
    int DiOption;
    SaOption* CsOption;

    DiOption = 0;
    CsOption = g_new0(SaOption, 1);
    CsOption->optionN = 3;
    CsOption->option = g_new0(GOptionEntry, CsOption->optionN +1);

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


    int
FdOptionGlib(int DiArgs, char** TcArgs,
        SaMap* CsMap, SaInfo* CsInfo, SaOption* CsOption)
{
    int DiLoop;
    int DiArgument;
    char** TcArgument;

    GOptionContext* EgOptioncontext;

    DiArgument = DiArgs;
    TcArgument = g_strdupv((char**)TcArgs);
    EgOptioncontext = g_option_context_new(NULL);

    g_option_context_set_help_enabled(EgOptioncontext, FALSE);
    g_option_context_add_main_entries(EgOptioncontext, CsOption->option, NULL);
    g_option_context_parse(EgOptioncontext, &DiArgument, &TcArgument, NULL);

    if (CsOption->version) {
        printf("\n%s\n", CsInfo->version);
        FvOptionFree(CsOption);
        exit(EXIT_SUCCESS);
    }

    if (CsOption->mode && g_strcmp0(CsOption->mode, "0") != 0) {
        g_strfreev(TcArgument);
        return EXIT_SUCCESS;
    }

    for (DiLoop = 1; DiLoop < DiArgument; DiLoop++) {
        FvUriPrint(TcArgument[DiLoop]);
    }

    exit(EXIT_SUCCESS);
}


    int
FdOptionGtk(GApplication* EgApplication,
        GApplicationCommandLine* EgCommandline, void* PvUserdata)
{
    int DiLoop;
    int DiArgument;
    char** TcArgument;
    SaMap* CsMap;
    SaInfo* CsInfo;
    SaOption* CsOption;

    CsMap = PvUserdata;
    CsInfo = CsMap->Info;
    CsOption = CsMap->Option;

    TcArgument = g_application_command_line_get_arguments(EgCommandline,
            &DiArgument);

    if (CsOption->mode && g_strcmp0(CsOption->mode, "1") != 0) {
        return EXIT_SUCCESS;
    }

    if ((! TcArgument) || (DiArgument < 2)) {
        FvGtkBase(GTK_APPLICATION(EgApplication), CsMap, NULL);
    }

    for (DiLoop = 1; DiLoop < DiArgument; DiLoop++) {
        FvGtkBase(GTK_APPLICATION(EgApplication), CsMap, TcArgument[DiLoop]);
    }

    return EXIT_SUCCESS;
}

