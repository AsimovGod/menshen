// part_window.c.h



struct SaGtkWindow {
    SaGtkStack* Stack;
    GtkWidget* base;
    char* baseT;
    int baseH;
    int baseW;
    GtkWidget* headerbar;
    GtkWidget* control;
    GtkWidget* grid;
};


struct SaGtkStack {
    GtkWidget* base;
    GtkWidget* tabbar;
    GtkWidget* newtab;
    GtkWidget* separator;
    GtkWidget* frame;
    int counter;
};



    void
FvGtkWindow(SaMap* CsMap, int DiArgument, char** TcArgument)
{
    SaGtkWindow* CsGtkWindow;
    int DiLoop;
    GtkApplication* EgApplication;

    EgApplication = CsMap->application;

    CsGtkWindow = g_new0(SaGtkWindow, 1);
    CsGtkWindow->Stack = g_new0(SaGtkStack, 1);

    CsGtkWindow->base = gtk_application_window_new(EgApplication);
    CsGtkWindow->headerbar = gtk_header_bar_new();
    CsGtkWindow->control = gtk_window_controls_new(GTK_PACK_END);
    CsGtkWindow->grid = gtk_grid_new();
    CsGtkWindow->Stack->base = gtk_stack_new();
    CsGtkWindow->Stack->tabbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
    CsGtkWindow->Stack->newtab = gtk_button_new_from_icon_name("list-add");
    CsGtkWindow->Stack->frame = gtk_frame_new(NULL);
    CsGtkWindow->Stack->separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

    CsGtkWindow->baseT = CsMap->Info->name;
    CsGtkWindow->baseW = 960;
    CsGtkWindow->baseH = 540;
    CsGtkWindow->Stack->counter = 0;

    CsMap->GtkWindow = CsGtkWindow;

    g_object_set_data_full(G_OBJECT(CsGtkWindow->base),
            "CsGtkWindow", CsGtkWindow, (GDestroyNotify)FvGtkWindowFree);

    gtk_window_set_titlebar(GTK_WINDOW(CsGtkWindow->base),
            CsGtkWindow->headerbar);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(CsGtkWindow->headerbar),
            CsGtkWindow->control);
    gtk_window_set_child(GTK_WINDOW(CsGtkWindow->base),
            CsGtkWindow->grid);
    gtk_frame_set_child(GTK_FRAME(CsGtkWindow->Stack->frame),
            CsGtkWindow->Stack->tabbar);
    gtk_box_append(GTK_BOX(CsGtkWindow->Stack->tabbar),
            CsGtkWindow->Stack->newtab);
    gtk_grid_attach(GTK_GRID(CsGtkWindow->grid), CsGtkWindow->Stack->frame,
            0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(CsGtkWindow->grid), CsGtkWindow->Stack->base,
            0, 1, 1, 1);

    g_signal_connect(CsGtkWindow->Stack->newtab,
            "clicked", G_CALLBACK(FvGtkTabNew), CsMap);

    gtk_window_controls_set_decoration_layout(
            GTK_WINDOW_CONTROLS(CsGtkWindow->control),
            "minimize,maximize");
    gtk_window_set_title(GTK_WINDOW(CsGtkWindow->base),
            CsGtkWindow->baseT);
    gtk_window_set_default_size(GTK_WINDOW(CsGtkWindow->base),
            CsGtkWindow->baseW, CsGtkWindow->baseH);

    FvGtkMenu(CsMap);

    if ((! TcArgument) || (DiArgument < 2)) {
        FvGtkTab(CsMap, NULL);
    }

    for (DiLoop = 1; DiLoop < DiArgument; DiLoop++) {
        FvGtkTab(CsMap, TcArgument[DiLoop]);
    }

    gtk_window_present(GTK_WINDOW(CsGtkWindow->base));
    gtk_window_set_focus(GTK_WINDOW(CsGtkWindow->base), NULL);
}


    void
FvGtkWindowFree(void* PvFree)
{
    SaGtkWindow* CsGtkWindow;

    CsGtkWindow = PvFree;

    if (! CsGtkWindow) return;

    g_free(CsGtkWindow->Stack);
    g_free(CsGtkWindow);
}

