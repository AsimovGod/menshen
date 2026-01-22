// part_uri.c.h



struct SaGtkUri {
    SaGuriParse* Parse;
    SaGtkUriEntry* Entry;
    bool change;
};


struct SaGtkUriEntry {
    GtkWidget* uri;
    GtkWidget* scheme;
    GtkWidget* userinfo;
    GtkWidget* host;
    GtkWidget* port;
    GtkWidget* path;
    GtkWidget* query;
    GtkWidget* fragment;
};



    void
FvGtkUri(SaMap* CsMap, char* AcUri)
{
    SaGtkTab* CsGtkTab;
    SaGtkUri* CsGtkUri;

    CsGtkTab = CsMap->GtkTab;

    CsGtkUri = g_new0(SaGtkUri, 1);
    CsGtkUri->Entry = g_new0(SaGtkUriEntry, 1);
    CsGtkUri->Parse = g_new0(SaGuriParse, 1);

    CsGtkTab->GtkUri = CsGtkUri;
    CsGtkTab->Scroll->uriBuild = gtk_scrolled_window_new();
    CsGtkTab->Scroll->uriParse = gtk_scrolled_window_new();
    CsGtkTab->Grid->uriBuild = gtk_grid_new();
    CsGtkTab->Grid->uriParse = gtk_grid_new();

    CsMap->GtkUri = CsGtkUri;

    g_object_set_data_full(G_OBJECT(CsGtkTab->Paned->base),
            "CsGtkUri", CsGtkUri, (GDestroyNotify)FvGtkUriFree);

    gtk_paned_set_start_child(GTK_PANED(CsGtkTab->Paned->baseLeft),
            CsGtkTab->Scroll->uriBuild);
    gtk_paned_set_end_child(GTK_PANED(CsGtkTab->Paned->baseLeft),
            CsGtkTab->Scroll->uriParse);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                CsGtkTab->Scroll->uriBuild), CsGtkTab->Grid->uriBuild);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                CsGtkTab->Scroll->uriParse), CsGtkTab->Grid->uriParse);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                CsGtkTab->Scroll->uriBuild),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                CsGtkTab->Scroll->uriParse),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_widget_set_margin_end(CsGtkTab->Grid->uriBuild, 16);
    gtk_widget_set_margin_top(CsGtkTab->Grid->uriBuild, 16);
    gtk_widget_set_margin_bottom(CsGtkTab->Grid->uriBuild, 16);
    gtk_widget_set_margin_end(CsGtkTab->Grid->uriParse, 16);
    gtk_widget_set_margin_top(CsGtkTab->Grid->uriParse, 16);
    gtk_widget_set_margin_bottom(CsGtkTab->Grid->uriParse, 16);

    gtk_widget_set_vexpand(CsGtkTab->Grid->uriBuild, TRUE);
    gtk_widget_set_hexpand(CsGtkTab->Grid->uriBuild, TRUE);
    gtk_widget_set_vexpand(CsGtkTab->Grid->uriParse, TRUE);
    gtk_widget_set_hexpand(CsGtkTab->Grid->uriParse, TRUE);

    gtk_widget_set_valign(CsGtkTab->Grid->uriBuild, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(CsGtkTab->Grid->uriBuild, GTK_ALIGN_FILL);
    gtk_widget_set_valign(CsGtkTab->Grid->uriParse, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(CsGtkTab->Grid->uriParse, GTK_ALIGN_FILL);

    gtk_grid_set_row_homogeneous(GTK_GRID(CsGtkTab->Grid->uriBuild), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(CsGtkTab->Grid->uriBuild), FALSE);
    gtk_grid_set_row_homogeneous(GTK_GRID(CsGtkTab->Grid->uriParse), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(CsGtkTab->Grid->uriParse), FALSE);

    gtk_grid_set_row_spacing(GTK_GRID(CsGtkTab->Grid->uriBuild), 4);
    gtk_grid_set_column_spacing(GTK_GRID(CsGtkTab->Grid->uriBuild), 4);
    gtk_grid_set_row_spacing(GTK_GRID(CsGtkTab->Grid->uriParse), 4);
    gtk_grid_set_column_spacing(GTK_GRID(CsGtkTab->Grid->uriParse), 4);

    FvGtkUriWidget(CsMap);

    gtk_editable_set_text(GTK_EDITABLE(CsGtkUri->Entry->uri),
            AcUri ? AcUri : "");
    FvGtkUriEntryParse(GTK_EDITABLE(CsGtkUri->Entry->uri), CsGtkUri);
}


    void
FvGtkUriWidget(SaMap* CsMap)
{
    SaGtkTab* CsGtkTab;
    SaGtkUri* CsGtkUri;

    CsGtkTab = CsMap->GtkTab;
    CsGtkUri = CsMap->GtkUri;

    CsGtkUri->Entry->uri = FeGtkUriEntry(CsGtkUri, "build",
            CsGtkTab->Grid->uriBuild, 0, "URI");
    CsGtkUri->Entry->scheme = FeGtkUriEntry(CsGtkUri, "parse",
            CsGtkTab->Grid->uriParse, 0, "Scheme");
    CsGtkUri->Entry->host = FeGtkUriEntry(CsGtkUri, "parse",
            CsGtkTab->Grid->uriParse, 1, "Host");
    CsGtkUri->Entry->userinfo = FeGtkUriEntry(CsGtkUri, "parse",
            CsGtkTab->Grid->uriParse, 2, "Userinfo");
    CsGtkUri->Entry->port = FeGtkUriSpin(CsGtkUri, "buttonPort",
            CsGtkTab->Grid->uriParse, 3, "Port");
    CsGtkUri->Entry->path = FeGtkUriEntry(CsGtkUri, "parse",
            CsGtkTab->Grid->uriParse, 4, "Path");
    CsGtkUri->Entry->query = FeGtkUriEntry(CsGtkUri, "parse",
            CsGtkTab->Grid->uriParse, 5, "Query");
    CsGtkUri->Entry->fragment = FeGtkUriEntry(CsGtkUri, "parse",
            CsGtkTab->Grid->uriParse, 6, "Fragment");
}


    void
FvGtkUriFree(void* PvFree)
{
    SaGtkUri* CsGtkUri;

    CsGtkUri = PvFree;

    if (! CsGtkUri) return;

    g_free(CsGtkUri->Parse);
    g_free(CsGtkUri->Entry);
    g_free(CsGtkUri);
}

