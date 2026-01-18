// part_option.h



    SuOption*
FsOptionInit()
{
    int ViOption;
    SuOption* PsOption;

    ViOption = 0;
    PsOption = g_new0(SuOption, 1);
    PsOption->optionN = 3;
    PsOption->option = g_new0(GOptionEntry, PsOption->optionN +1);

    PsOption->version = FALSE;
    PsOption->option[ViOption].long_name = "version";
    PsOption->option[ViOption].short_name = 'v';
    PsOption->option[ViOption].arg = G_OPTION_ARG_NONE;
    PsOption->option[ViOption].arg_data = &PsOption->version;
    PsOption->option[ViOption].description = "Version";
    ViOption = ViOption + 1;

    PsOption->mode = g_strdup("1");
    PsOption->option[ViOption].long_name = "mode";
    PsOption->option[ViOption].short_name = 'm';
    PsOption->option[ViOption].arg = G_OPTION_ARG_STRING;
    PsOption->option[ViOption].arg_data = &PsOption->mode;
    PsOption->option[ViOption].description = "Mode";
    ViOption = ViOption + 1;

    return PsOption;
}


    void
FvOptionFree(void* PvFree)
{
    SuOption* PsOption;

    PsOption = PvFree;

    if (! PsOption) return;

    g_free(PsOption->mode);
    g_free(PsOption->option);
    g_free(PsOption);
}


    int
FiOptionGlib(int ViArgs, char** AcArgs,
        SuMap* PsMap, SuInfo* PsInfo, SuOption* PsOption)
{
    int ViLoop;
    int ViArgument;
    char** AcArgument;

    GOptionContext* UgOptioncontext;

    ViArgument = ViArgs;
    AcArgument = g_strdupv((char**)AcArgs);
    UgOptioncontext = g_option_context_new(NULL);

    g_option_context_set_help_enabled(UgOptioncontext, FALSE);
    g_option_context_add_main_entries(UgOptioncontext, PsOption->option, NULL);
    g_option_context_parse(UgOptioncontext, &ViArgument, &AcArgument, NULL);

    if (PsOption->version) {
        printf("\n%s\n", PsInfo->version);
        FvOptionFree(PsOption);
        exit(EXIT_SUCCESS);
    }

    if (PsOption->mode && g_strcmp0(PsOption->mode, "0") == 0)
    {
        for (ViLoop = 1; ViLoop < ViArgument; ViLoop++) {
            FvUriPrint(AcArgument[ViLoop]);
        }

        exit(EXIT_SUCCESS);
    }

    g_strfreev(AcArgument);

    return EXIT_SUCCESS;
}


    int
FiOptionGtk(GApplication* UgApplication,
        GApplicationCommandLine* UgCommandline, void* PvUserdata)
{
    int ViArgument;
    char** AcArgument;
    SuMap* PsMap;
    SuInfo* PsInfo;
    SuOption* PsOption;

    PsMap = PvUserdata;
    PsInfo = PsMap->info;
    PsOption = PsMap->option;

    AcArgument = g_application_command_line_get_arguments(UgCommandline,
            &ViArgument);

    if (PsOption->mode && g_strcmp0(PsOption->mode, "1") == 0)
    {
        FvGtkBase(GTK_APPLICATION(UgApplication), PsMap, AcArgument);
    }

    return EXIT_SUCCESS;
}

