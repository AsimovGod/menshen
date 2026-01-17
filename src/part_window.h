// part_window.h



    void
FvGtkLayoutFree(void* PvFree)
{
    SuGtkLayout* PsGtkLayout;

    PsGtkLayout = PvFree;

    if (! PsGtkLayout) return;

    g_free(PsGtkLayout->window);
    g_free(PsGtkLayout->headerbar);
    g_free(PsGtkLayout->control);
    g_free(PsGtkLayout->paned);
    g_free(PsGtkLayout->grid);
    g_free(PsGtkLayout->scroll);
    g_free(PsGtkLayout);
}


    void
FvGtkActivate(GtkApplication* UgApplication, char** AcArgsGtkActivate)
{
    SuGtkLayout* PsGtkLayout;

    PsGtkLayout = g_new0(SuGtkLayout, 1);
    PsGtkLayout->window = g_new0(SuGtkWindow, 1);
    PsGtkLayout->headerbar = g_new0(SuGtkHeaderbar, 1);
    PsGtkLayout->control = g_new0(SuGtkControl, 1);
    PsGtkLayout->paned = g_new0(SuGtkPaned, 1);
    PsGtkLayout->grid = g_new0(SuGtkGrid, 1);
    PsGtkLayout->scroll = g_new0(SuGtkScroll, 1);

    PsGtkLayout->window->main = gtk_application_window_new(UgApplication);
    PsGtkLayout->headerbar->main = gtk_header_bar_new();
    PsGtkLayout->control->main = gtk_window_controls_new(GTK_PACK_END);
    PsGtkLayout->paned->main = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    PsGtkLayout->paned->mainLeft = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    PsGtkLayout->paned->mainRight = gtk_paned_new(GTK_ORIENTATION_VERTICAL);

    PsGtkLayout->window->mainT = "MenShen";
    PsGtkLayout->window->mainW = 960;
    PsGtkLayout->window->mainH = 540;
    PsGtkLayout->paned->mainR = 0.7;
    PsGtkLayout->paned->mainLeftR = 0.2;
    PsGtkLayout->paned->mainRightR = 0.2;

    g_object_set_data_full(G_OBJECT(PsGtkLayout->window->main),
            "PsGtkLayout", PsGtkLayout, (GDestroyNotify)FvGtkLayoutFree);

    gtk_window_set_titlebar(GTK_WINDOW(PsGtkLayout->window->main),
            PsGtkLayout->headerbar->main);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(PsGtkLayout->headerbar->main),
            PsGtkLayout->control->main);
    gtk_window_set_child(GTK_WINDOW(PsGtkLayout->window->main),
            PsGtkLayout->paned->main);
    gtk_paned_set_start_child(GTK_PANED(PsGtkLayout->paned->main),
            PsGtkLayout->paned->mainLeft);
    gtk_paned_set_end_child(GTK_PANED(PsGtkLayout->paned->main),
            PsGtkLayout->paned->mainRight);

    gtk_window_controls_set_decoration_layout(
            GTK_WINDOW_CONTROLS(PsGtkLayout->control->main),
            "minimize,maximize");
    gtk_window_set_title(GTK_WINDOW(PsGtkLayout->window->main),
            PsGtkLayout->window->mainT);
    gtk_window_set_default_size(GTK_WINDOW(PsGtkLayout->window->main),
            PsGtkLayout->window->mainW, PsGtkLayout->window->mainH);

    gtk_paned_set_position(GTK_PANED(PsGtkLayout->paned->main),
            PsGtkLayout->paned->mainR * PsGtkLayout->window->mainW);
    gtk_paned_set_position(GTK_PANED(PsGtkLayout->paned->mainLeft),
            PsGtkLayout->paned->mainLeftR * PsGtkLayout->window->mainH);
    gtk_paned_set_position(GTK_PANED(PsGtkLayout->paned->mainRight),
            PsGtkLayout->paned->mainRightR * PsGtkLayout->window->mainH);

    gtk_widget_set_valign(PsGtkLayout->paned->main, GTK_ALIGN_FILL);
    gtk_widget_set_halign(PsGtkLayout->paned->main, GTK_ALIGN_FILL);
    gtk_widget_set_valign(PsGtkLayout->paned->mainLeft, GTK_ALIGN_FILL);
    gtk_widget_set_halign(PsGtkLayout->paned->mainLeft, GTK_ALIGN_FILL);
    gtk_widget_set_valign(PsGtkLayout->paned->mainRight, GTK_ALIGN_FILL);
    gtk_widget_set_halign(PsGtkLayout->paned->mainRight, GTK_ALIGN_FILL);

    FvGtkUri(PsGtkLayout, AcArgsGtkActivate[1]);

    gtk_window_present(GTK_WINDOW(PsGtkLayout->window->main));
    gtk_window_set_focus(GTK_WINDOW(PsGtkLayout->window->main), NULL);
}

