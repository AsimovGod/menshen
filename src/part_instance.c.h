// part_instance.c.h



    int
FdGtkInstance(SaMap* CsMap, int DiArgs, char** TcArgs)
{
    SaInfo* CsInfo;
    SaOption* CsOption;
    int DiExit;
    GtkApplication* EgApplication;
    AdwStyleManager* UaStylemanager;

    CsInfo = CsMap->Info;
    CsOption = CsMap->Option;

    EgApplication = gtk_application_new(NULL,
            G_APPLICATION_HANDLES_COMMAND_LINE);

    CsMap->application = EgApplication;

    g_application_add_main_option_entries(G_APPLICATION(EgApplication),
            CsOption->option);

    g_signal_connect(EgApplication,
            "command-line", G_CALLBACK(FdOptionGtk), CsMap);

    if (CsOption->mode && g_strcmp0(CsOption->mode, "1") == 0) {
        adw_init();
        UaStylemanager = adw_style_manager_get_default();
        adw_style_manager_set_color_scheme(UaStylemanager,
                ADW_COLOR_SCHEME_PREFER_DARK);
    }

    DiExit = g_application_run(G_APPLICATION(EgApplication), DiArgs, TcArgs);

    g_object_unref(EgApplication);

    return DiExit;
}

