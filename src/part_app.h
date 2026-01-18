// part_app.h



    SuInfo*
FsInfoInit()
{
    SuInfo* PsInfo;

    PsInfo = g_new0(SuInfo, 1);
    PsInfo->name = "MenShen";
    PsInfo->id = "com.AsimovGod.menshen";
    PsInfo->version = "0.1.0";

    return PsInfo;
}


    void
FvInfoFree(void* PvFree)
{
    SuInfo* PsInfo;

    PsInfo = PvFree;

    if (! PsInfo) return;

    g_free(PsInfo);
}


    int
FiGtkApp(int ViArgs, char** AcArgs,
        SuMap* PsMap, SuInfo* PsInfo, SuOption* PsOption)
{
    int ViExit;
    GtkApplication* UgApplication;
    AdwStyleManager* UaStylemanager;

    if (PsOption->mode && g_strcmp0(PsOption->mode, "1") == 0) {
        adw_init();
        UaStylemanager = adw_style_manager_get_default();
        adw_style_manager_set_color_scheme(UaStylemanager,
                ADW_COLOR_SCHEME_PREFER_DARK);
    }

    UgApplication = gtk_application_new(NULL,
            G_APPLICATION_HANDLES_COMMAND_LINE);

    PsMap->application = UgApplication;

    g_application_add_main_option_entries(G_APPLICATION(UgApplication),
            PsOption->option);

    g_signal_connect(UgApplication,
            "command-line", G_CALLBACK(FiOptionGtk), PsMap);

    ViExit = g_application_run(G_APPLICATION(UgApplication), ViArgs, AcArgs);

    g_object_unref(UgApplication);

    return ViExit;
}

