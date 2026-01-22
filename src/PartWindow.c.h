// PartWindow.c.h



struct SaGtkWindow {
    SaGtkWindowStack* Stack;
    GtkWidget* base;
    char* baseT;
    int baseH;
    int baseW;
    GtkWidget* headerbar;
    GtkWidget* control;
    GtkWidget* grid;
};


struct SaGtkWindowStack {
    GtkWidget* base;
    GtkWidget* scroll;
    GtkWidget* hsep;
    GtkWidget* vsep;
    GtkWidget* tabbar;
    GtkWidget* newtab;
    int counter;
};



    void
FvGtkWindow(SaMap* CsMap, int DiArgument, char** TcArgument)
{
    SaGtkWindow* CsGtkWindow;
    int DiLoop;
    GtkApplication* EgApplication;
    GtkWidget* EgFirstGrid;
    GtkWidget* EgFirstButton;

    EgApplication = CsMap->application;

    CsGtkWindow = g_new0(SaGtkWindow, 1);
    CsGtkWindow->Stack = g_new0(SaGtkWindowStack, 1);

    CsGtkWindow->base = gtk_application_window_new(EgApplication);
    CsGtkWindow->headerbar = gtk_header_bar_new();
    CsGtkWindow->control = gtk_window_controls_new(GTK_PACK_END);
    CsGtkWindow->grid = gtk_grid_new();
    CsGtkWindow->Stack->base = gtk_stack_new();
    CsGtkWindow->Stack->scroll = gtk_scrolled_window_new();
    CsGtkWindow->Stack->hsep = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    CsGtkWindow->Stack->vsep = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
    CsGtkWindow->Stack->tabbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
    CsGtkWindow->Stack->newtab = gtk_button_new_from_icon_name("list-add");

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
    gtk_grid_attach(GTK_GRID(CsGtkWindow->grid), CsGtkWindow->Stack->newtab,
            0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(CsGtkWindow->grid), CsGtkWindow->Stack->vsep,
            1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(CsGtkWindow->grid), CsGtkWindow->Stack->scroll,
            2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(CsGtkWindow->grid), CsGtkWindow->Stack->hsep,
            0, 1, 3, 1);
    gtk_grid_attach(GTK_GRID(CsGtkWindow->grid), CsGtkWindow->Stack->base,
            0, 2, 3, 1);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                CsGtkWindow->Stack->scroll), CsGtkWindow->Stack->tabbar);

    g_signal_connect(CsGtkWindow->Stack->newtab,
            "clicked", G_CALLBACK(FvGtkTabNew), CsMap);

    gtk_window_controls_set_decoration_layout(
            GTK_WINDOW_CONTROLS(CsGtkWindow->control),
            "minimize,maximize");
    gtk_window_set_title(GTK_WINDOW(CsGtkWindow->base),
            CsGtkWindow->baseT);
    gtk_window_set_default_size(GTK_WINDOW(CsGtkWindow->base),
            CsGtkWindow->baseW, CsGtkWindow->baseH);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                CsGtkWindow->Stack->scroll),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);

    gtk_widget_set_hexpand(CsGtkWindow->Stack->tabbar, TRUE);
    gtk_widget_set_valign(CsGtkWindow->Stack->tabbar, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_start(CsGtkWindow->Stack->vsep, 4);
    gtk_widget_set_margin_end(CsGtkWindow->Stack->vsep, 4);

    FvGtkMenu(CsMap);

    if ((! TcArgument) || (DiArgument < 2)) {
        FvGtkTab(CsMap, NULL);
    }

    for (DiLoop = 1; DiLoop < DiArgument; DiLoop++) {
        FvGtkTab(CsMap, TcArgument[DiLoop]);
    }

    EgFirstGrid = gtk_widget_get_first_child(CsGtkWindow->Stack->tabbar);
    EgFirstButton = gtk_grid_get_child_at(GTK_GRID(EgFirstGrid), 0, 0);
    FvGtkTabSwitch(EgFirstButton, CsMap);

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

