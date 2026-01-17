// part_uri.h



    void
FvGtkUriWidget(SuGtkLayout* PsGtkLayout, SuGtkUri* PsGtkUri)
{
    PsGtkUri->entry->uri = FgGtkUriEntry(PsGtkUri, "build",
            PsGtkLayout->grid->uriBuild, 0, "URI");
    PsGtkUri->entry->scheme = FgGtkUriEntry(PsGtkUri, "parse",
            PsGtkLayout->grid->uriParse, 0, "Scheme");
    PsGtkUri->entry->host = FgGtkUriEntry(PsGtkUri, "parse",
            PsGtkLayout->grid->uriParse, 1, "Host");
    PsGtkUri->entry->userinfo = FgGtkUriEntry(PsGtkUri, "parse",
            PsGtkLayout->grid->uriParse, 2, "Userinfo");
    PsGtkUri->spin->port = FgGtkUriSpin(PsGtkUri, "buttonPort",
            PsGtkLayout->grid->uriParse, 3, "Port");
    PsGtkUri->entry->path = FgGtkUriEntry(PsGtkUri, "parse",
            PsGtkLayout->grid->uriParse, 4, "Path");
    PsGtkUri->entry->query = FgGtkUriEntry(PsGtkUri, "parse",
            PsGtkLayout->grid->uriParse, 5, "Query");
    PsGtkUri->entry->fragment = FgGtkUriEntry(PsGtkUri, "parse",
            PsGtkLayout->grid->uriParse, 6, "Fragment");
}


    void
FvGtkUriFree(void* PvFree)
{
    SuGtkUri* PsGtkUri;

    PsGtkUri = PvFree;

    if (! PsGtkUri) return;

    g_free(PsGtkUri->parse);
    g_free(PsGtkUri->entry);
    g_free(PsGtkUri->spin);
    g_free(PsGtkUri);
}


    void
FvGtkUri(SuGtkLayout* PsGtkLayout, char* VcUri)
{
    SuGtkUri* PsGtkUri;

    PsGtkUri = g_new0(SuGtkUri, 1);
    PsGtkUri->entry = g_new0(SuGtkUriEntry, 1);
    PsGtkUri->spin = g_new0(SuGtkUriSpin, 1);
    PsGtkUri->parse = g_new0(SuGuriParse, 1);

    PsGtkLayout->scroll->uriBuild = gtk_scrolled_window_new();
    PsGtkLayout->scroll->uriParse = gtk_scrolled_window_new();
    PsGtkLayout->grid->uriBuild = gtk_grid_new();
    PsGtkLayout->grid->uriParse = gtk_grid_new();

    g_object_set_data_full(G_OBJECT(PsGtkLayout->window->main),
            "PsGtkUri", PsGtkUri, (GDestroyNotify)FvGtkUriFree);

    gtk_paned_set_start_child(GTK_PANED(PsGtkLayout->paned->mainLeft),
            PsGtkLayout->scroll->uriBuild);
    gtk_paned_set_end_child(GTK_PANED(PsGtkLayout->paned->mainLeft),
            PsGtkLayout->scroll->uriParse);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                PsGtkLayout->scroll->uriBuild), PsGtkLayout->grid->uriBuild);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                PsGtkLayout->scroll->uriParse), PsGtkLayout->grid->uriParse);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                PsGtkLayout->scroll->uriBuild),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                PsGtkLayout->scroll->uriParse),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_widget_set_vexpand(PsGtkLayout->grid->uriBuild, TRUE);
    gtk_widget_set_hexpand(PsGtkLayout->grid->uriBuild, TRUE);
    gtk_widget_set_vexpand(PsGtkLayout->grid->uriParse, TRUE);
    gtk_widget_set_hexpand(PsGtkLayout->grid->uriParse, TRUE);

    gtk_widget_set_valign(PsGtkLayout->grid->uriBuild, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(PsGtkLayout->grid->uriBuild, GTK_ALIGN_FILL);
    gtk_widget_set_valign(PsGtkLayout->grid->uriParse, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(PsGtkLayout->grid->uriParse, GTK_ALIGN_FILL);

    gtk_grid_set_row_homogeneous(GTK_GRID(PsGtkLayout->grid->uriBuild), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(PsGtkLayout->grid->uriBuild), FALSE);
    gtk_grid_set_row_homogeneous(GTK_GRID(PsGtkLayout->grid->uriParse), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(PsGtkLayout->grid->uriParse), FALSE);

    gtk_grid_set_row_spacing(GTK_GRID(PsGtkLayout->grid->uriBuild), 4);
    gtk_grid_set_column_spacing(GTK_GRID(PsGtkLayout->grid->uriBuild), 4);
    gtk_grid_set_row_spacing(GTK_GRID(PsGtkLayout->grid->uriParse), 4);
    gtk_grid_set_column_spacing(GTK_GRID(PsGtkLayout->grid->uriParse), 4);

    FvGtkUriWidget(PsGtkLayout, PsGtkUri);

    gtk_editable_set_text(GTK_EDITABLE(PsGtkUri->entry->uri),
            VcUri ? VcUri : "");
    FvGtkUriEntryParse(GTK_EDITABLE(PsGtkUri->entry->uri), PsGtkUri);
}

