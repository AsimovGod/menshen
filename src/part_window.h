// part_window.h



    void
FvGtkBaseFree(void* PvFree)
{
    SuGtkBase* PsGtkBase;

    PsGtkBase = PvFree;

    if (! PsGtkBase) return;

    g_free(PsGtkBase->window);
    g_free(PsGtkBase->headerbar);
    g_free(PsGtkBase->control);
    g_free(PsGtkBase->paned);
    g_free(PsGtkBase->grid);
    g_free(PsGtkBase->scroll);
    g_free(PsGtkBase);
}


    void
FvGtkBase(GtkApplication* UgApplication, SuMap* PsMap, char** AcArgument)
{
    SuGtkBase* PsGtkBase;

    PsMap->gtkBase = PsGtkBase;
    PsGtkBase = g_new0(SuGtkBase, 1);
    PsGtkBase->window = g_new0(SuGtkWindow, 1);
    PsGtkBase->headerbar = g_new0(SuGtkHeaderbar, 1);
    PsGtkBase->control = g_new0(SuGtkControl, 1);
    PsGtkBase->paned = g_new0(SuGtkPaned, 1);
    PsGtkBase->grid = g_new0(SuGtkGrid, 1);
    PsGtkBase->scroll = g_new0(SuGtkScroll, 1);
    PsGtkBase->GtkUri = g_new0(SuGtkUri, 1);
    PsGtkBase->GtkMime = g_new0(SuGtkMime, 1);
    PsGtkBase->Info = PsMap->info;
    PsGtkBase->Option = PsMap->option;

    PsGtkBase->window->main = gtk_application_window_new(UgApplication);
    PsGtkBase->headerbar->main = gtk_header_bar_new();
    PsGtkBase->control->main = gtk_window_controls_new(GTK_PACK_END);
    PsGtkBase->paned->main = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    PsGtkBase->paned->mainLeft = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    PsGtkBase->paned->mainRight = gtk_paned_new(GTK_ORIENTATION_VERTICAL);

    PsGtkBase->window->mainT = "MenShen";
    PsGtkBase->window->mainW = 960;
    PsGtkBase->window->mainH = 540;
    PsGtkBase->paned->mainR = 0.8;
    PsGtkBase->paned->mainLeftR = 0.2;
    PsGtkBase->paned->mainRightR = 0.7;

    g_object_set_data_full(G_OBJECT(PsGtkBase->window->main),
            "PsGtkBase", PsGtkBase, (GDestroyNotify)FvGtkBaseFree);

    gtk_window_set_titlebar(GTK_WINDOW(PsGtkBase->window->main),
            PsGtkBase->headerbar->main);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(PsGtkBase->headerbar->main),
            PsGtkBase->control->main);
    gtk_window_set_child(GTK_WINDOW(PsGtkBase->window->main),
            PsGtkBase->paned->main);
    gtk_paned_set_start_child(GTK_PANED(PsGtkBase->paned->main),
            PsGtkBase->paned->mainLeft);
    gtk_paned_set_end_child(GTK_PANED(PsGtkBase->paned->main),
            PsGtkBase->paned->mainRight);

    gtk_window_controls_set_decoration_layout(
            GTK_WINDOW_CONTROLS(PsGtkBase->control->main),
            "minimize,maximize");
    gtk_window_set_title(GTK_WINDOW(PsGtkBase->window->main),
            PsGtkBase->window->mainT);
    gtk_window_set_default_size(GTK_WINDOW(PsGtkBase->window->main),
            PsGtkBase->window->mainW, PsGtkBase->window->mainH);

    gtk_paned_set_position(GTK_PANED(PsGtkBase->paned->main),
            PsGtkBase->paned->mainR * PsGtkBase->window->mainW);
    gtk_paned_set_position(GTK_PANED(PsGtkBase->paned->mainLeft),
            PsGtkBase->paned->mainLeftR * PsGtkBase->window->mainH);
    gtk_paned_set_position(GTK_PANED(PsGtkBase->paned->mainRight),
            PsGtkBase->paned->mainRightR * PsGtkBase->window->mainH);

    gtk_widget_set_valign(PsGtkBase->paned->main, GTK_ALIGN_FILL);
    gtk_widget_set_halign(PsGtkBase->paned->main, GTK_ALIGN_FILL);
    gtk_widget_set_valign(PsGtkBase->paned->mainLeft, GTK_ALIGN_FILL);
    gtk_widget_set_halign(PsGtkBase->paned->mainLeft, GTK_ALIGN_FILL);
    gtk_widget_set_valign(PsGtkBase->paned->mainRight, GTK_ALIGN_FILL);
    gtk_widget_set_halign(PsGtkBase->paned->mainRight, GTK_ALIGN_FILL);

    FvGtkUri(PsGtkBase, AcArgument[1]);
    FvGtkMime(PsGtkBase);

    gtk_window_present(GTK_WINDOW(PsGtkBase->window->main));
    gtk_window_set_focus(GTK_WINDOW(PsGtkBase->window->main), NULL);
}

