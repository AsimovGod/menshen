// PartWindow.c.h



struct SaGtkWindow {
    // link
    SaGtkWindowStack* Stack;
    GtkWidget* base;
    // declaration property
    char* baseT;
    int baseH;
    int baseW;
    // gtk.h widget headerbar
    GtkWidget* headerbar;
    // gtk.h widget controls
    GtkWidget* control;
    // gtk.h widget grid
    GtkWidget* grid;
};


struct SaGtkWindowStack {
    // gtk.h widget stack
    GtkWidget* base;
    // gtk.h widget scroll
    GtkWidget* scroll;
    // gtk.h widget separator
    GtkWidget* hsep;
    GtkWidget* vsep;
    // gtk.h widget box
    GtkWidget* tabbar;
    // gtk.h widget button
    GtkWidget* newtab;
    // declaration property
    int counter;
};



    void
FvGtkWindow(SaMap* CsMap, int DiArgument, char** TcArgument)
{
    // declaration
    SaGtkWindow* CsGtkWindow;
    int DiLoop;
    GtkApplication* EgApplication;
    GtkWidget* EgFirstGrid;
    GtkWidget* EgFirstButton;

    // inherit
    EgApplication = CsMap->application;

    // malloc
    CsGtkWindow = g_new0(SaGtkWindow, 1);
    CsGtkWindow->Stack = g_new0(SaGtkWindowStack, 1);

    // gtk.h new
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

    // variable
    CsGtkWindow->baseT = CsMap->Info->name;
    CsGtkWindow->baseW = 960;
    CsGtkWindow->baseH = 540;
    CsGtkWindow->Stack->counter = 0;

    // bequeath
    CsMap->GtkWindow = CsGtkWindow;

    // gobject.h data
    g_object_set_data_full(G_OBJECT(CsGtkWindow->base),
            "CsGtkWindow", CsGtkWindow, (GDestroyNotify)FvGtkWindowFree);

    // gtk.h layout
    gtk_window_set_titlebar(GTK_WINDOW(CsGtkWindow->base),
            CsGtkWindow->headerbar);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(CsGtkWindow->headerbar),
            CsGtkWindow->control);
    gtk_window_set_child(GTK_WINDOW(CsGtkWindow->base),
            CsGtkWindow->grid);
    gtk_grid_attach(GTK_GRID(CsGtkWindow->grid), CsGtkWindow->Stack->base,
            0, 0, 3, 1);
    gtk_grid_attach(GTK_GRID(CsGtkWindow->grid), CsGtkWindow->Stack->hsep,
            0, 1, 3, 1);
    gtk_grid_attach(GTK_GRID(CsGtkWindow->grid), CsGtkWindow->Stack->scroll,
            0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(CsGtkWindow->grid), CsGtkWindow->Stack->vsep,
            1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(CsGtkWindow->grid), CsGtkWindow->Stack->newtab,
            2, 2, 1, 1);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                CsGtkWindow->Stack->scroll), CsGtkWindow->Stack->tabbar);

    // gobject.h signal
    g_signal_connect(CsGtkWindow->Stack->newtab,
            "clicked", G_CALLBACK(FvGtkTabNew), CsMap);

    // gtk.h property
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
    gtk_widget_set_margin_start(CsGtkWindow->Stack->tabbar, 8);
    gtk_widget_set_margin_end(CsGtkWindow->Stack->tabbar, 8);
    gtk_widget_set_margin_top(CsGtkWindow->Stack->tabbar, 8);
    gtk_widget_set_margin_bottom(CsGtkWindow->Stack->tabbar, 8);
    gtk_widget_set_margin_start(CsGtkWindow->Stack->newtab, 8);
    gtk_widget_set_margin_end(CsGtkWindow->Stack->newtab, 8);
    gtk_widget_set_margin_top(CsGtkWindow->Stack->newtab, 8);
    gtk_widget_set_margin_bottom(CsGtkWindow->Stack->newtab, 8);

    gtk_button_set_has_frame(GTK_BUTTON(CsGtkWindow->Stack->newtab), FALSE);

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

