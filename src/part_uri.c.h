// part_uri.h



    void
FvGtkUriWidget(SaMap* CsMap)
{
    SaGtkStack* CsGtkStack;
    SaGtkUri* CsGtkUri;

    CsGtkStack = CsMap->GtkStack;
    CsGtkUri = CsMap->GtkUri;

    CsGtkUri->entry->uri = FeGtkUriEntry(CsGtkUri, "build",
            CsGtkStack->grid->uriBuild, 0, "URI");
    CsGtkUri->entry->scheme = FeGtkUriEntry(CsGtkUri, "parse",
            CsGtkStack->grid->uriParse, 0, "Scheme");
    CsGtkUri->entry->host = FeGtkUriEntry(CsGtkUri, "parse",
            CsGtkStack->grid->uriParse, 1, "Host");
    CsGtkUri->entry->userinfo = FeGtkUriEntry(CsGtkUri, "parse",
            CsGtkStack->grid->uriParse, 2, "Userinfo");
    CsGtkUri->entry->port = FeGtkUriSpin(CsGtkUri, "buttonPort",
            CsGtkStack->grid->uriParse, 3, "Port");
    CsGtkUri->entry->path = FeGtkUriEntry(CsGtkUri, "parse",
            CsGtkStack->grid->uriParse, 4, "Path");
    CsGtkUri->entry->query = FeGtkUriEntry(CsGtkUri, "parse",
            CsGtkStack->grid->uriParse, 5, "Query");
    CsGtkUri->entry->fragment = FeGtkUriEntry(CsGtkUri, "parse",
            CsGtkStack->grid->uriParse, 6, "Fragment");
}


    void
FvGtkUriFree(void* PvFree)
{
    SaGtkUri* CsGtkUri;

    CsGtkUri = PvFree;

    if (! CsGtkUri) return;

    g_free(CsGtkUri->parse);
    g_free(CsGtkUri->entry);
    g_free(CsGtkUri);
}


    void
FvGtkUri(SaMap* CsMap, char* AcUri)
{
    SaGtkStack* CsGtkStack;
    SaGtkUri* CsGtkUri;

    CsGtkStack = CsMap->GtkStack;

    CsGtkUri = g_new0(SaGtkUri, 1);
    CsGtkUri->entry = g_new0(SaGtkUriEntry, 1);
    CsGtkUri->parse = g_new0(SaGuriParse, 1);

    CsGtkStack->scroll->uriBuild = gtk_scrolled_window_new();
    CsGtkStack->scroll->uriParse = gtk_scrolled_window_new();
    CsGtkStack->grid->uriBuild = gtk_grid_new();
    CsGtkStack->grid->uriParse = gtk_grid_new();

    CsMap->GtkUri = CsGtkUri;

    g_object_set_data_full(G_OBJECT(CsMap->GtkWindow->base),
            "CsGtkUri", CsGtkUri, (GDestroyNotify)FvGtkUriFree);

    gtk_paned_set_start_child(GTK_PANED(CsGtkStack->paned->baseLeft),
            CsGtkStack->scroll->uriBuild);
    gtk_paned_set_end_child(GTK_PANED(CsGtkStack->paned->baseLeft),
            CsGtkStack->scroll->uriParse);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                CsGtkStack->scroll->uriBuild), CsGtkStack->grid->uriBuild);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                CsGtkStack->scroll->uriParse), CsGtkStack->grid->uriParse);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                CsGtkStack->scroll->uriBuild),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                CsGtkStack->scroll->uriParse),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_widget_set_margin_end(CsGtkStack->grid->uriBuild, 16);
    gtk_widget_set_margin_top(CsGtkStack->grid->uriBuild, 16);
    gtk_widget_set_margin_bottom(CsGtkStack->grid->uriBuild, 16);
    gtk_widget_set_margin_end(CsGtkStack->grid->uriParse, 16);
    gtk_widget_set_margin_top(CsGtkStack->grid->uriParse, 16);
    gtk_widget_set_margin_bottom(CsGtkStack->grid->uriParse, 16);

    gtk_widget_set_vexpand(CsGtkStack->grid->uriBuild, TRUE);
    gtk_widget_set_hexpand(CsGtkStack->grid->uriBuild, TRUE);
    gtk_widget_set_vexpand(CsGtkStack->grid->uriParse, TRUE);
    gtk_widget_set_hexpand(CsGtkStack->grid->uriParse, TRUE);

    gtk_widget_set_valign(CsGtkStack->grid->uriBuild, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(CsGtkStack->grid->uriBuild, GTK_ALIGN_FILL);
    gtk_widget_set_valign(CsGtkStack->grid->uriParse, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(CsGtkStack->grid->uriParse, GTK_ALIGN_FILL);

    gtk_grid_set_row_homogeneous(GTK_GRID(CsGtkStack->grid->uriBuild), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(CsGtkStack->grid->uriBuild), FALSE);
    gtk_grid_set_row_homogeneous(GTK_GRID(CsGtkStack->grid->uriParse), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(CsGtkStack->grid->uriParse), FALSE);

    gtk_grid_set_row_spacing(GTK_GRID(CsGtkStack->grid->uriBuild), 4);
    gtk_grid_set_column_spacing(GTK_GRID(CsGtkStack->grid->uriBuild), 4);
    gtk_grid_set_row_spacing(GTK_GRID(CsGtkStack->grid->uriParse), 4);
    gtk_grid_set_column_spacing(GTK_GRID(CsGtkStack->grid->uriParse), 4);

    FvGtkUriWidget(CsMap);

    gtk_editable_set_text(GTK_EDITABLE(CsGtkUri->entry->uri),
            AcUri ? AcUri : "");
    FvGtkUriEntryParse(GTK_EDITABLE(CsGtkUri->entry->uri), CsGtkUri);
}

