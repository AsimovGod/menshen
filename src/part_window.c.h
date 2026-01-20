// part_window.h



    void
FvGtkWindow(SaMap* CsMap, int DiArgument, char** TcArgument)
{
    SaGtkWindow* CsGtkWindow;
    int DiLoop;
    GtkApplication* EgApplication;

    EgApplication = CsMap->application;

    CsGtkWindow = g_new0(SaGtkWindow, 1);

    CsGtkWindow->base = gtk_application_window_new(EgApplication);
    CsGtkWindow->headerbar = gtk_header_bar_new();
    CsGtkWindow->control = gtk_window_controls_new(GTK_PACK_END);

    CsMap->GtkWindow = CsGtkWindow;

    g_object_set_data_full(G_OBJECT(CsGtkWindow->base),
            "CsGtkWindow", CsGtkWindow, (GDestroyNotify)g_free);

    gtk_window_set_titlebar(GTK_WINDOW(CsGtkWindow->base),
            CsGtkWindow->headerbar);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(CsGtkWindow->headerbar),
            CsGtkWindow->control);

    CsGtkWindow->baseT = CsMap->Info->name;
    CsGtkWindow->baseW = 960;
    CsGtkWindow->baseH = 540;

    FvGtkMenu(CsMap);

    if ((! TcArgument) || (DiArgument < 2)) {
        FvGtkStack(CsMap, NULL);
    }

    for (DiLoop = 1; DiLoop < DiArgument; DiLoop++) {
        FvGtkStack(CsMap, TcArgument[DiLoop]);
    }

    gtk_window_present(GTK_WINDOW(CsGtkWindow->base));
    gtk_window_set_focus(GTK_WINDOW(CsGtkWindow->base), NULL);
}

