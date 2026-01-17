// part_uri.h



    void
FvGtkUriWidget(SuGtkBase* PsGtkBase, SuGtkUri* PsGtkUri)
{
    PsGtkUri->entry->uri = FgGtkUriEntry(PsGtkUri, "build",
            PsGtkBase->grid->uriBuild, 0, "URI");
    PsGtkUri->entry->scheme = FgGtkUriEntry(PsGtkUri, "parse",
            PsGtkBase->grid->uriParse, 0, "Scheme");
    PsGtkUri->entry->host = FgGtkUriEntry(PsGtkUri, "parse",
            PsGtkBase->grid->uriParse, 1, "Host");
    PsGtkUri->entry->userinfo = FgGtkUriEntry(PsGtkUri, "parse",
            PsGtkBase->grid->uriParse, 2, "Userinfo");
    PsGtkUri->spin->port = FgGtkUriSpin(PsGtkUri, "buttonPort",
            PsGtkBase->grid->uriParse, 3, "Port");
    PsGtkUri->entry->path = FgGtkUriEntry(PsGtkUri, "parse",
            PsGtkBase->grid->uriParse, 4, "Path");
    PsGtkUri->entry->query = FgGtkUriEntry(PsGtkUri, "parse",
            PsGtkBase->grid->uriParse, 5, "Query");
    PsGtkUri->entry->fragment = FgGtkUriEntry(PsGtkUri, "parse",
            PsGtkBase->grid->uriParse, 6, "Fragment");
}


    void
FvGtkUriFree(void* PvFree)
{
    SuGtkUri* PsGtkUri;

    PsGtkUri = PvFree;

    if (! PsGtkUri) return;

    free(PsGtkUri->parse);
    free(PsGtkUri->entry);
    free(PsGtkUri->spin);
    free(PsGtkUri);
}


    void
FvGtkUri(SuGtkBase* PsGtkBase, char* VcUri)
{
    SuGtkUri* PsGtkUri;

    PsGtkUri = g_new0(SuGtkUri, 1);
    PsGtkUri->entry = g_new0(SuGtkUriEntry, 1);
    PsGtkUri->spin = g_new0(SuGtkUriSpin, 1);
    PsGtkUri->parse = g_new0(SuGuriParse, 1);

    PsGtkBase->scroll->uriBuild = gtk_scrolled_window_new();
    PsGtkBase->scroll->uriParse = gtk_scrolled_window_new();
    PsGtkBase->grid->uriBuild = gtk_grid_new();
    PsGtkBase->grid->uriParse = gtk_grid_new();

    g_object_set_data_full(G_OBJECT(PsGtkBase->window->main),
            "PsGtkUri", PsGtkUri, (GDestroyNotify)FvGtkUriFree);

    gtk_paned_set_start_child(GTK_PANED(PsGtkBase->paned->mainLeft),
            PsGtkBase->scroll->uriBuild);
    gtk_paned_set_end_child(GTK_PANED(PsGtkBase->paned->mainLeft),
            PsGtkBase->scroll->uriParse);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                PsGtkBase->scroll->uriBuild), PsGtkBase->grid->uriBuild);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                PsGtkBase->scroll->uriParse), PsGtkBase->grid->uriParse);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                PsGtkBase->scroll->uriBuild),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                PsGtkBase->scroll->uriParse),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_widget_set_margin_end(PsGtkBase->grid->uriBuild, 16);
    gtk_widget_set_margin_top(PsGtkBase->grid->uriBuild, 16);
    gtk_widget_set_margin_bottom(PsGtkBase->grid->uriBuild, 16);
    gtk_widget_set_margin_end(PsGtkBase->grid->uriParse, 16);
    gtk_widget_set_margin_top(PsGtkBase->grid->uriParse, 16);
    gtk_widget_set_margin_bottom(PsGtkBase->grid->uriParse, 16);

    gtk_widget_set_vexpand(PsGtkBase->grid->uriBuild, TRUE);
    gtk_widget_set_hexpand(PsGtkBase->grid->uriBuild, TRUE);
    gtk_widget_set_vexpand(PsGtkBase->grid->uriParse, TRUE);
    gtk_widget_set_hexpand(PsGtkBase->grid->uriParse, TRUE);

    gtk_widget_set_valign(PsGtkBase->grid->uriBuild, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(PsGtkBase->grid->uriBuild, GTK_ALIGN_FILL);
    gtk_widget_set_valign(PsGtkBase->grid->uriParse, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(PsGtkBase->grid->uriParse, GTK_ALIGN_FILL);

    gtk_grid_set_row_homogeneous(GTK_GRID(PsGtkBase->grid->uriBuild), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(PsGtkBase->grid->uriBuild), FALSE);
    gtk_grid_set_row_homogeneous(GTK_GRID(PsGtkBase->grid->uriParse), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(PsGtkBase->grid->uriParse), FALSE);

    gtk_grid_set_row_spacing(GTK_GRID(PsGtkBase->grid->uriBuild), 4);
    gtk_grid_set_column_spacing(GTK_GRID(PsGtkBase->grid->uriBuild), 4);
    gtk_grid_set_row_spacing(GTK_GRID(PsGtkBase->grid->uriParse), 4);
    gtk_grid_set_column_spacing(GTK_GRID(PsGtkBase->grid->uriParse), 4);

    FvGtkUriWidget(PsGtkBase, PsGtkUri);

    gtk_editable_set_text(GTK_EDITABLE(PsGtkUri->entry->uri),
            VcUri ? VcUri : "");
    FvGtkUriEntryParse(GTK_EDITABLE(PsGtkUri->entry->uri), PsGtkUri);
}

