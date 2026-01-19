// part_window.h



    void
FvGtkBaseFree(void* PvFree)
{
    SaGtkBase* CsGtkBase;

    CsGtkBase = PvFree;

    if (! CsGtkBase) return;

    g_free(CsGtkBase->window);
    g_free(CsGtkBase->headerbar);
    g_free(CsGtkBase->control);
    g_free(CsGtkBase->paned);
    g_free(CsGtkBase->grid);
    g_free(CsGtkBase->scroll);
    g_free(CsGtkBase);
}


    void
FvGtkBase(GtkApplication* EgApplication, SaMap* CsMap, char* AcUri)
{
    SaGtkBase* CsGtkBase;

    CsGtkBase = g_new0(SaGtkBase, 1);
    CsGtkBase->application = CsMap->application;
    CsGtkBase->window = g_new0(SaGtkWindow, 1);
    CsGtkBase->headerbar = g_new0(SaGtkHeaderbar, 1);
    CsGtkBase->control = g_new0(SaGtkControl, 1);
    CsGtkBase->paned = g_new0(SaGtkPaned, 1);
    CsGtkBase->grid = g_new0(SaGtkGrid, 1);
    CsGtkBase->scroll = g_new0(SaGtkScroll, 1);

    CsGtkBase->window->base = gtk_application_window_new(EgApplication);
    CsGtkBase->headerbar->base = gtk_header_bar_new();
    CsGtkBase->control->base = gtk_window_controls_new(GTK_PACK_END);
    CsGtkBase->paned->base = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    CsGtkBase->paned->baseLeft = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    CsGtkBase->paned->baseRight = gtk_paned_new(GTK_ORIENTATION_VERTICAL);

    CsMap->GtkBase = CsGtkBase;
    CsGtkBase->Info = CsMap->Info;
    CsGtkBase->Option = CsMap->Option;

    g_object_set_data_full(G_OBJECT(CsGtkBase->window->base),
            "CsGtkBase", CsGtkBase, (GDestroyNotify)FvGtkBaseFree);

    gtk_window_set_titlebar(GTK_WINDOW(CsGtkBase->window->base),
            CsGtkBase->headerbar->base);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(CsGtkBase->headerbar->base),
            CsGtkBase->control->base);
    gtk_window_set_child(GTK_WINDOW(CsGtkBase->window->base),
            CsGtkBase->paned->base);
    gtk_paned_set_start_child(GTK_PANED(CsGtkBase->paned->base),
            CsGtkBase->paned->baseLeft);
    gtk_paned_set_end_child(GTK_PANED(CsGtkBase->paned->base),
            CsGtkBase->paned->baseRight);

    CsGtkBase->window->baseT = CsMap->Info->name;
    CsGtkBase->window->baseW = 960;
    CsGtkBase->window->baseH = 540;
    CsGtkBase->paned->baseR = 0.8;
    CsGtkBase->paned->baseLeftR = 0.2;
    CsGtkBase->paned->baseRightR = 0.7;

    gtk_window_controls_set_decoration_layout(
            GTK_WINDOW_CONTROLS(CsGtkBase->control->base),
            "minimize,maximize");
    gtk_window_set_title(GTK_WINDOW(CsGtkBase->window->base),
            CsGtkBase->window->baseT);
    gtk_window_set_default_size(GTK_WINDOW(CsGtkBase->window->base),
            CsGtkBase->window->baseW, CsGtkBase->window->baseH);

    gtk_paned_set_position(GTK_PANED(CsGtkBase->paned->base),
            CsGtkBase->paned->baseR * CsGtkBase->window->baseW);
    gtk_paned_set_position(GTK_PANED(CsGtkBase->paned->baseLeft),
            CsGtkBase->paned->baseLeftR * CsGtkBase->window->baseH);
    gtk_paned_set_position(GTK_PANED(CsGtkBase->paned->baseRight),
            CsGtkBase->paned->baseRightR * CsGtkBase->window->baseH);

    gtk_widget_set_valign(CsGtkBase->paned->base, GTK_ALIGN_FILL);
    gtk_widget_set_halign(CsGtkBase->paned->base, GTK_ALIGN_FILL);
    gtk_widget_set_valign(CsGtkBase->paned->baseLeft, GTK_ALIGN_FILL);
    gtk_widget_set_halign(CsGtkBase->paned->baseLeft, GTK_ALIGN_FILL);
    gtk_widget_set_valign(CsGtkBase->paned->baseRight, GTK_ALIGN_FILL);
    gtk_widget_set_halign(CsGtkBase->paned->baseRight, GTK_ALIGN_FILL);

    FvGtkMenu(CsMap, CsGtkBase);
    FvGtkUri(CsGtkBase, AcUri);
    FvGtkMime(CsGtkBase);

    gtk_window_present(GTK_WINDOW(CsGtkBase->window->base));
    gtk_window_set_focus(GTK_WINDOW(CsGtkBase->window->base), NULL);
}

