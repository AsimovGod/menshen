// part_window.h



    void
FvGtkBaseFree(void* PvFree)
{
    SuGtkBase* PsGtkBase;

    PsGtkBase = PvFree;

    if (! PsGtkBase) return;

    g_free(PsGtkBase->window);
    g_free(PsGtkBase->overlay);
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
    PsGtkBase->application = PsMap->application;
    PsGtkBase->window = g_new0(SuGtkWindow, 1);
    PsGtkBase->overlay = g_new0(SuGtkOverlay, 1);
    PsGtkBase->headerbar = g_new0(SuGtkHeaderbar, 1);
    PsGtkBase->control = g_new0(SuGtkControl, 1);
    PsGtkBase->paned = g_new0(SuGtkPaned, 1);
    PsGtkBase->grid = g_new0(SuGtkGrid, 1);
    PsGtkBase->scroll = g_new0(SuGtkScroll, 1);
    PsGtkBase->GtkMenu = g_new0(SuGtkMenu, 1);
    PsGtkBase->GtkUri = g_new0(SuGtkUri, 1);
    PsGtkBase->GtkMime = g_new0(SuGtkMime, 1);
    PsGtkBase->Info = PsMap->info;
    PsGtkBase->Option = PsMap->option;

    g_object_set_data_full(G_OBJECT(PsGtkBase->application),
            "PsGtkBase", PsGtkBase, (GDestroyNotify)FvGtkBaseFree);

    PsGtkBase->window->base = gtk_application_window_new(UgApplication);
    PsGtkBase->overlay->base = gtk_overlay_new();
    PsGtkBase->headerbar->base = gtk_header_bar_new();
    PsGtkBase->control->base = gtk_window_controls_new(GTK_PACK_END);
    PsGtkBase->paned->base = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    PsGtkBase->paned->baseLeft = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    PsGtkBase->paned->baseRight = gtk_paned_new(GTK_ORIENTATION_VERTICAL);

    gtk_window_set_titlebar(GTK_WINDOW(PsGtkBase->window->base),
            PsGtkBase->headerbar->base);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(PsGtkBase->headerbar->base),
            PsGtkBase->control->base);
    gtk_window_set_child(GTK_WINDOW(PsGtkBase->window->base),
            PsGtkBase->overlay->base);
    gtk_overlay_add_overlay(GTK_OVERLAY(PsGtkBase->overlay->base),
            PsGtkBase->paned->base);
    gtk_paned_set_start_child(GTK_PANED(PsGtkBase->paned->base),
            PsGtkBase->paned->baseLeft);
    gtk_paned_set_end_child(GTK_PANED(PsGtkBase->paned->base),
            PsGtkBase->paned->baseRight);

    PsGtkBase->window->baseT = PsMap->info->name;
    PsGtkBase->window->baseW = 960;
    PsGtkBase->window->baseH = 540;
    PsGtkBase->paned->baseR = 0.8;
    PsGtkBase->paned->baseLeftR = 0.2;
    PsGtkBase->paned->baseRightR = 0.7;

    gtk_window_controls_set_decoration_layout(
            GTK_WINDOW_CONTROLS(PsGtkBase->control->base),
            "minimize,maximize");
    gtk_window_set_title(GTK_WINDOW(PsGtkBase->window->base),
            PsGtkBase->window->baseT);
    gtk_window_set_default_size(GTK_WINDOW(PsGtkBase->window->base),
            PsGtkBase->window->baseW, PsGtkBase->window->baseH);

    gtk_paned_set_position(GTK_PANED(PsGtkBase->paned->base),
            PsGtkBase->paned->baseR * PsGtkBase->window->baseW);
    gtk_paned_set_position(GTK_PANED(PsGtkBase->paned->baseLeft),
            PsGtkBase->paned->baseLeftR * PsGtkBase->window->baseH);
    gtk_paned_set_position(GTK_PANED(PsGtkBase->paned->baseRight),
            PsGtkBase->paned->baseRightR * PsGtkBase->window->baseH);

    gtk_widget_set_valign(PsGtkBase->paned->base, GTK_ALIGN_FILL);
    gtk_widget_set_halign(PsGtkBase->paned->base, GTK_ALIGN_FILL);
    gtk_widget_set_valign(PsGtkBase->paned->baseLeft, GTK_ALIGN_FILL);
    gtk_widget_set_halign(PsGtkBase->paned->baseLeft, GTK_ALIGN_FILL);
    gtk_widget_set_valign(PsGtkBase->paned->baseRight, GTK_ALIGN_FILL);
    gtk_widget_set_halign(PsGtkBase->paned->baseRight, GTK_ALIGN_FILL);

    FvGtkMenu(PsMap, PsGtkBase);
    FvGtkUri(PsGtkBase, AcArgument[1]);
    FvGtkMime(PsGtkBase);

    gtk_window_present(GTK_WINDOW(PsGtkBase->window->base));
    gtk_window_set_focus(GTK_WINDOW(PsGtkBase->window->base), NULL);
}

