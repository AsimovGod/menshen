// PartInstance.c.h



    int
FdGtkInstance(SaMap* CsMap, int DiArgs, char** TcArgs)
{
    // declaration
    SaInfo* CsInfo;
    SaOption* CsOption;
    int DiExit;
    GtkApplication* EgApplication;
    AdwStyleManager* UaStylemanager;

    // inherit
    CsInfo = CsMap->Info;
    CsOption = CsMap->Option;

    // gio.h application new
    EgApplication = gtk_application_new(NULL,
            G_APPLICATION_HANDLES_COMMAND_LINE);

    // bequeath
    CsMap->application = EgApplication;

    // gobject.h data
    g_object_set_data_full(G_OBJECT(EgApplication),
            "CsOption", CsOption, (GDestroyNotify)FvOptionFree);
    g_object_set_data_full(G_OBJECT(EgApplication),
            "CsInfo", CsInfo, (GDestroyNotify)FvInfoFree);
    g_object_set_data_full(G_OBJECT(EgApplication),
            "CsMap", CsMap, (GDestroyNotify)FvMapFree);

    // gtk.h option
    g_application_add_main_option_entries(G_APPLICATION(EgApplication),
            CsOption->option);

    // gobject.h signal
    g_signal_connect(EgApplication,
            "command-line", G_CALLBACK(FdOptionGtk), CsMap);

    // if option
    if (CsOption->mode && g_strcmp0(CsOption->mode, "1") == 0) {
        // block adawaita.h init
        adw_init();
        // block adwaita.h style dark
        UaStylemanager = adw_style_manager_get_default();
        adw_style_manager_set_color_scheme(UaStylemanager,
                ADW_COLOR_SCHEME_PREFER_DARK);
    }

    // gio.h application run
    DiExit = g_application_run(G_APPLICATION(EgApplication), DiArgs, TcArgs);

    // free
    g_object_unref(EgApplication);

    // return
    return DiExit;
}

