// part_app.h



    SaInfo*
FsInfoInit()
{
    SaInfo* CsInfo;

    CsInfo = g_new0(SaInfo, 1);

    CsInfo->name = "MenShen";
    CsInfo->id = "com.AsimovGod.menshen";
    CsInfo->version = "0.1.0";

    return CsInfo;
}


    void
FvInfoFree(void* PvFree)
{
    SaInfo* CsInfo;

    CsInfo = PvFree;

    if (! CsInfo) return;

    g_free(CsInfo);
}


    int
FdGtkApp(int DiArgs, char** TcArgs,
        SaMap* CsMap, SaInfo* CsInfo, SaOption* CsOption)
{
    int DiExit;
    GtkApplication* EgApplication;
    AdwStyleManager* UaStylemanager;

    if (CsOption->mode && g_strcmp0(CsOption->mode, "1") == 0) {
        adw_init();
        UaStylemanager = adw_style_manager_get_default();
        adw_style_manager_set_color_scheme(UaStylemanager,
                ADW_COLOR_SCHEME_PREFER_DARK);
    }

    EgApplication = gtk_application_new(NULL,
            G_APPLICATION_HANDLES_COMMAND_LINE);

    CsMap->application = EgApplication;

    g_application_add_main_option_entries(G_APPLICATION(EgApplication),
            CsOption->option);

    g_signal_connect(EgApplication,
            "command-line", G_CALLBACK(FdOptionGtk), CsMap);

    DiExit = g_application_run(G_APPLICATION(EgApplication), DiArgs, TcArgs);

    g_object_unref(EgApplication);

    return DiExit;
}

