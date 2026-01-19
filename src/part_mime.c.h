// part_mime.h



    void
FvGtkMimeFree(void* PvFree)
{
    SaGtkMime* CsGtkMime;

    CsGtkMime = PvFree;

    if (! CsGtkMime) return;

    g_free(CsGtkMime->list);
    g_free(CsGtkMime->box);
    g_free(CsGtkMime->button);
    g_free(CsGtkMime);
}


    void
FvGtkMime(SaGtkBase* CsGtkBase)
{
    SaGtkMime* CsGtkMime;

    CsGtkMime = g_new0(SaGtkMime, 1);
    CsGtkMime->list = g_new0(SaGtkMimeList, 1);
    CsGtkMime->box = g_new0(SaGtkMimeBox, 1);
    CsGtkMime->button = g_new0(SaGtkMimeButton, 1);

    CsGtkBase->scroll->mimeList = gtk_scrolled_window_new();
    CsGtkBase->scroll->mimeOpen = gtk_scrolled_window_new();
    CsGtkBase->grid->mimeList = gtk_grid_new();
    CsGtkBase->grid->mimeOpen = gtk_grid_new();

    CsGtkBase->GtkMime = CsGtkMime;

    g_object_set_data_full(G_OBJECT(CsGtkBase->window->base),
            "CsGtkMime", CsGtkMime, (GDestroyNotify)FvGtkMimeFree);

    gtk_paned_set_start_child(GTK_PANED(CsGtkBase->paned->baseRight),
            CsGtkBase->scroll->mimeList);
    gtk_paned_set_end_child(GTK_PANED(CsGtkBase->paned->baseRight),
            CsGtkBase->scroll->mimeOpen);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                CsGtkBase->scroll->mimeList), CsGtkBase->grid->mimeList);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                CsGtkBase->scroll->mimeOpen), CsGtkBase->grid->mimeOpen);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                CsGtkBase->scroll->mimeList),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                CsGtkBase->scroll->mimeOpen),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_widget_set_margin_start(CsGtkBase->grid->mimeList, 16);
    gtk_widget_set_margin_end(CsGtkBase->grid->mimeList, 16);
    gtk_widget_set_margin_top(CsGtkBase->grid->mimeList, 16);
    gtk_widget_set_margin_bottom(CsGtkBase->grid->mimeList, 16);
    gtk_widget_set_margin_start(CsGtkBase->grid->mimeOpen, 16);
    gtk_widget_set_margin_end(CsGtkBase->grid->mimeOpen, 16);
    gtk_widget_set_margin_top(CsGtkBase->grid->mimeOpen, 16);
    gtk_widget_set_margin_bottom(CsGtkBase->grid->mimeOpen, 16);

    gtk_widget_set_vexpand(CsGtkBase->grid->mimeList, TRUE);
    gtk_widget_set_hexpand(CsGtkBase->grid->mimeList, TRUE);
    gtk_widget_set_vexpand(CsGtkBase->grid->mimeOpen, TRUE);
    gtk_widget_set_hexpand(CsGtkBase->grid->mimeOpen, TRUE);

    gtk_widget_set_valign(CsGtkBase->grid->mimeList, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(CsGtkBase->grid->mimeList, GTK_ALIGN_FILL);
    gtk_widget_set_valign(CsGtkBase->grid->mimeOpen, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(CsGtkBase->grid->mimeOpen, GTK_ALIGN_FILL);

    gtk_grid_set_row_homogeneous(GTK_GRID(CsGtkBase->grid->mimeList), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(CsGtkBase->grid->mimeList), FALSE);
    gtk_grid_set_row_homogeneous(GTK_GRID(CsGtkBase->grid->mimeOpen), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(CsGtkBase->grid->mimeOpen), FALSE);

    gtk_grid_set_row_spacing(GTK_GRID(CsGtkBase->grid->mimeList), 4);
    gtk_grid_set_column_spacing(GTK_GRID(CsGtkBase->grid->mimeList), 4);
    gtk_grid_set_row_spacing(GTK_GRID(CsGtkBase->grid->mimeOpen), 4);
    gtk_grid_set_column_spacing(GTK_GRID(CsGtkBase->grid->mimeOpen), 4);

    FvGtkMimeList(CsGtkBase, CsGtkMime);
    FvGtkMimeOpen(CsGtkBase, CsGtkMime);
}

