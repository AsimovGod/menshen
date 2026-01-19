// part_uri.h



    void
FvGtkUriWidget(SaGtkBase* CsGtkBase, SaGtkUri* CsGtkUri)
{
    CsGtkUri->entry->uri = FeGtkUriEntry(CsGtkUri, "build",
            CsGtkBase->grid->uriBuild, 0, "URI");
    CsGtkUri->entry->scheme = FeGtkUriEntry(CsGtkUri, "parse",
            CsGtkBase->grid->uriParse, 0, "Scheme");
    CsGtkUri->entry->host = FeGtkUriEntry(CsGtkUri, "parse",
            CsGtkBase->grid->uriParse, 1, "Host");
    CsGtkUri->entry->userinfo = FeGtkUriEntry(CsGtkUri, "parse",
            CsGtkBase->grid->uriParse, 2, "Userinfo");
    CsGtkUri->spin->port = FeGtkUriSpin(CsGtkUri, "buttonPort",
            CsGtkBase->grid->uriParse, 3, "Port");
    CsGtkUri->entry->path = FeGtkUriEntry(CsGtkUri, "parse",
            CsGtkBase->grid->uriParse, 4, "Path");
    CsGtkUri->entry->query = FeGtkUriEntry(CsGtkUri, "parse",
            CsGtkBase->grid->uriParse, 5, "Query");
    CsGtkUri->entry->fragment = FeGtkUriEntry(CsGtkUri, "parse",
            CsGtkBase->grid->uriParse, 6, "Fragment");
}


    void
FvGtkUriFree(void* PvFree)
{
    SaGtkUri* CsGtkUri;

    CsGtkUri = PvFree;

    if (! CsGtkUri) return;

    g_free(CsGtkUri->parse);
    g_free(CsGtkUri->entry);
    g_free(CsGtkUri->spin);
    g_free(CsGtkUri);
}


    void
FvGtkUri(SaGtkBase* CsGtkBase, char* AcUri)
{
    SaGtkUri* CsGtkUri;

    CsGtkUri = g_new0(SaGtkUri, 1);
    CsGtkUri->entry = g_new0(SaGtkUriEntry, 1);
    CsGtkUri->spin = g_new0(SaGtkUriSpin, 1);
    CsGtkUri->parse = g_new0(SaGuriParse, 1);

    CsGtkBase->scroll->uriBuild = gtk_scrolled_window_new();
    CsGtkBase->scroll->uriParse = gtk_scrolled_window_new();
    CsGtkBase->grid->uriBuild = gtk_grid_new();
    CsGtkBase->grid->uriParse = gtk_grid_new();

    CsGtkBase->GtkUri = CsGtkUri;

    g_object_set_data_full(G_OBJECT(CsGtkBase->window->base),
            "CsGtkUri", CsGtkUri, (GDestroyNotify)FvGtkUriFree);

    gtk_paned_set_start_child(GTK_PANED(CsGtkBase->paned->baseLeft),
            CsGtkBase->scroll->uriBuild);
    gtk_paned_set_end_child(GTK_PANED(CsGtkBase->paned->baseLeft),
            CsGtkBase->scroll->uriParse);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                CsGtkBase->scroll->uriBuild), CsGtkBase->grid->uriBuild);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                CsGtkBase->scroll->uriParse), CsGtkBase->grid->uriParse);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                CsGtkBase->scroll->uriBuild),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                CsGtkBase->scroll->uriParse),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_widget_set_margin_end(CsGtkBase->grid->uriBuild, 16);
    gtk_widget_set_margin_top(CsGtkBase->grid->uriBuild, 16);
    gtk_widget_set_margin_bottom(CsGtkBase->grid->uriBuild, 16);
    gtk_widget_set_margin_end(CsGtkBase->grid->uriParse, 16);
    gtk_widget_set_margin_top(CsGtkBase->grid->uriParse, 16);
    gtk_widget_set_margin_bottom(CsGtkBase->grid->uriParse, 16);

    gtk_widget_set_vexpand(CsGtkBase->grid->uriBuild, TRUE);
    gtk_widget_set_hexpand(CsGtkBase->grid->uriBuild, TRUE);
    gtk_widget_set_vexpand(CsGtkBase->grid->uriParse, TRUE);
    gtk_widget_set_hexpand(CsGtkBase->grid->uriParse, TRUE);

    gtk_widget_set_valign(CsGtkBase->grid->uriBuild, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(CsGtkBase->grid->uriBuild, GTK_ALIGN_FILL);
    gtk_widget_set_valign(CsGtkBase->grid->uriParse, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(CsGtkBase->grid->uriParse, GTK_ALIGN_FILL);

    gtk_grid_set_row_homogeneous(GTK_GRID(CsGtkBase->grid->uriBuild), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(CsGtkBase->grid->uriBuild), FALSE);
    gtk_grid_set_row_homogeneous(GTK_GRID(CsGtkBase->grid->uriParse), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(CsGtkBase->grid->uriParse), FALSE);

    gtk_grid_set_row_spacing(GTK_GRID(CsGtkBase->grid->uriBuild), 4);
    gtk_grid_set_column_spacing(GTK_GRID(CsGtkBase->grid->uriBuild), 4);
    gtk_grid_set_row_spacing(GTK_GRID(CsGtkBase->grid->uriParse), 4);
    gtk_grid_set_column_spacing(GTK_GRID(CsGtkBase->grid->uriParse), 4);

    FvGtkUriWidget(CsGtkBase, CsGtkUri);

    gtk_editable_set_text(GTK_EDITABLE(CsGtkUri->entry->uri),
            AcUri ? AcUri : "");
    FvGtkUriEntryParse(GTK_EDITABLE(CsGtkUri->entry->uri), CsGtkUri);
}

