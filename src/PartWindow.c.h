// PartWindow.c.h



struct SaGtkWindow {
    // link
    SaGtkWindowStack* Stack;
    GtkWidget* base;
    // declaration property
    int baseH;
    int baseW;
    const char* baseT;
    // gtk.h widget headerbar
    GtkWidget* headerbar;
    // gtk.h widget grid
    GtkWidget* grid;
};



    void
FvGtkWindow(SaMap* CsMap, int DiArgument, char** TcArgument)
{
    // declaration
    SaGtkWindow* CsGtkWindow;
    int DiLoop;
    GtkApplication* EgApplication;

    // inherit
    EgApplication = CsMap->application;

    // malloc
    CsGtkWindow = g_new0(SaGtkWindow, 1);

    // gtk.h new
    CsGtkWindow->base = gtk_application_window_new(EgApplication);
    CsGtkWindow->headerbar = gtk_header_bar_new();
    CsGtkWindow->grid = gtk_grid_new();

    // variable
    CsGtkWindow->baseT = CsMap->Info->name;
    CsGtkWindow->baseW = 960;
    CsGtkWindow->baseH = 540;

    // PartWindowStack.c.h
    CsGtkWindow->Stack = FsGtkWindowStack(CsMap, CsGtkWindow);

    // bequeath
    CsMap->GtkWindow = CsGtkWindow;

    // gobject.h data
    g_object_set_data_full(G_OBJECT(CsGtkWindow->base),
            "CsGtkWindow", CsGtkWindow, (GDestroyNotify)FvGtkWindowFree);

    // gtk.h layout
    gtk_window_set_titlebar(GTK_WINDOW(CsGtkWindow->base),
            CsGtkWindow->headerbar);
    gtk_window_set_child(GTK_WINDOW(CsGtkWindow->base),
            CsGtkWindow->grid);

    // gtk.h property
    gtk_window_set_title(GTK_WINDOW(CsGtkWindow->base),
            CsGtkWindow->baseT);
    gtk_window_set_default_size(GTK_WINDOW(CsGtkWindow->base),
            CsGtkWindow->baseW, CsGtkWindow->baseH);

    // PartMenu.c.h
    FvGtkMenu(CsMap);

    // PartTab.c.h
    if ((! TcArgument) || (DiArgument < 2)) {
        FvGtkTab(CsMap, NULL);
    }

    for (DiLoop = 1; DiLoop < DiArgument; DiLoop++) {
        FvGtkTab(CsMap, TcArgument[DiLoop]);
    }

    // gtk.h property window
    gtk_window_present(GTK_WINDOW(CsGtkWindow->base));
    gtk_window_set_focus(GTK_WINDOW(CsGtkWindow->base), NULL);
}


    void
FvGtkWindowFree(void* PvFree)
{
    // declaration
    SaGtkWindow* CsGtkWindow;

    // inherit
    CsGtkWindow = PvFree;

    if (! CsGtkWindow) return;

    // free
    g_free(CsGtkWindow->Stack);
    g_free(CsGtkWindow);
}

