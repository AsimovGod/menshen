// part_mime.c.h



struct SaGtkMime {
    SaGtkMimeList* List;
    SaGtkMimeButton* Button;
    GtkWidget* listbox;
};


struct SaGtkMimeList {
    GList* http;
    GList* https;
    GList* all;
};


struct SaGtkMimeButton {
    GtkWidget* open;
};



    void
FvGtkMime(SaMap* CsMap)
{
    SaGtkTab* CsGtkTab;
    SaGtkMime* CsGtkMime;

    CsGtkTab = CsMap->GtkTab;

    CsGtkMime = g_new0(SaGtkMime, 1);
    CsGtkMime->List = g_new0(SaGtkMimeList, 1);
    CsGtkMime->Button = g_new0(SaGtkMimeButton, 1);

    CsGtkTab->Scroll->mimeList = gtk_scrolled_window_new();
    CsGtkTab->Scroll->mimeOpen = gtk_scrolled_window_new();
    CsGtkTab->Grid->mimeList = gtk_grid_new();
    CsGtkTab->Grid->mimeOpen = gtk_grid_new();

    CsMap->GtkMime = CsGtkMime;

    g_object_set_data_full(G_OBJECT(CsMap->GtkWindow->base),
            "CsGtkMime", CsGtkMime, (GDestroyNotify)FvGtkMimeFree);

    gtk_paned_set_start_child(GTK_PANED(CsGtkTab->Paned->baseRight),
            CsGtkTab->Scroll->mimeList);
    gtk_paned_set_end_child(GTK_PANED(CsGtkTab->Paned->baseRight),
            CsGtkTab->Scroll->mimeOpen);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                CsGtkTab->Scroll->mimeList), CsGtkTab->Grid->mimeList);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                CsGtkTab->Scroll->mimeOpen), CsGtkTab->Grid->mimeOpen);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                CsGtkTab->Scroll->mimeList),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                CsGtkTab->Scroll->mimeOpen),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_widget_set_margin_start(CsGtkTab->Grid->mimeList, 16);
    gtk_widget_set_margin_end(CsGtkTab->Grid->mimeList, 16);
    gtk_widget_set_margin_top(CsGtkTab->Grid->mimeList, 16);
    gtk_widget_set_margin_bottom(CsGtkTab->Grid->mimeList, 16);
    gtk_widget_set_margin_start(CsGtkTab->Grid->mimeOpen, 16);
    gtk_widget_set_margin_end(CsGtkTab->Grid->mimeOpen, 16);
    gtk_widget_set_margin_top(CsGtkTab->Grid->mimeOpen, 16);
    gtk_widget_set_margin_bottom(CsGtkTab->Grid->mimeOpen, 16);

    gtk_widget_set_vexpand(CsGtkTab->Grid->mimeList, TRUE);
    gtk_widget_set_hexpand(CsGtkTab->Grid->mimeList, TRUE);
    gtk_widget_set_vexpand(CsGtkTab->Grid->mimeOpen, TRUE);
    gtk_widget_set_hexpand(CsGtkTab->Grid->mimeOpen, TRUE);

    gtk_widget_set_valign(CsGtkTab->Grid->mimeList, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(CsGtkTab->Grid->mimeList, GTK_ALIGN_FILL);
    gtk_widget_set_valign(CsGtkTab->Grid->mimeOpen, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(CsGtkTab->Grid->mimeOpen, GTK_ALIGN_FILL);

    gtk_grid_set_row_homogeneous(GTK_GRID(CsGtkTab->Grid->mimeList), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(CsGtkTab->Grid->mimeList), FALSE);
    gtk_grid_set_row_homogeneous(GTK_GRID(CsGtkTab->Grid->mimeOpen), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(CsGtkTab->Grid->mimeOpen), FALSE);

    gtk_grid_set_row_spacing(GTK_GRID(CsGtkTab->Grid->mimeList), 4);
    gtk_grid_set_column_spacing(GTK_GRID(CsGtkTab->Grid->mimeList), 4);
    gtk_grid_set_row_spacing(GTK_GRID(CsGtkTab->Grid->mimeOpen), 4);
    gtk_grid_set_column_spacing(GTK_GRID(CsGtkTab->Grid->mimeOpen), 4);

    FvGtkMimeList(CsMap);
    FvGtkMimeOpen(CsMap);
}


    void
FvGtkMimeFree(void* PvFree)
{
    SaGtkMime* CsGtkMime;

    CsGtkMime = PvFree;

    if (! CsGtkMime) return;

    g_free(CsGtkMime->List);
    g_free(CsGtkMime->Button);
    g_free(CsGtkMime);
}

