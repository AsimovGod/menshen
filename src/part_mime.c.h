// part_mime.h



    void
FvGtkMimeFree(void* PvFree)
{
    SaGtkMime* CsGtkMime;

    CsGtkMime = PvFree;

    if (! CsGtkMime) return;

    g_free(CsGtkMime->list);
    g_free(CsGtkMime->button);
    g_free(CsGtkMime);
}


    void
FvGtkMime(SaMap* CsMap)
{
    SaGtkStack* CsGtkStack;
    SaGtkMime* CsGtkMime;

    CsGtkStack = CsMap->GtkStack;

    CsGtkMime = g_new0(SaGtkMime, 1);
    CsGtkMime->list = g_new0(SaGtkMimeList, 1);
    CsGtkMime->button = g_new0(SaGtkMimeButton, 1);

    CsGtkStack->scroll->mimeList = gtk_scrolled_window_new();
    CsGtkStack->scroll->mimeOpen = gtk_scrolled_window_new();
    CsGtkStack->grid->mimeList = gtk_grid_new();
    CsGtkStack->grid->mimeOpen = gtk_grid_new();

    CsMap->GtkMime = CsGtkMime;

    g_object_set_data_full(G_OBJECT(CsMap->GtkWindow->base),
            "CsGtkMime", CsGtkMime, (GDestroyNotify)FvGtkMimeFree);

    gtk_paned_set_start_child(GTK_PANED(CsGtkStack->paned->baseRight),
            CsGtkStack->scroll->mimeList);
    gtk_paned_set_end_child(GTK_PANED(CsGtkStack->paned->baseRight),
            CsGtkStack->scroll->mimeOpen);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                CsGtkStack->scroll->mimeList), CsGtkStack->grid->mimeList);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                CsGtkStack->scroll->mimeOpen), CsGtkStack->grid->mimeOpen);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                CsGtkStack->scroll->mimeList),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                CsGtkStack->scroll->mimeOpen),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_widget_set_margin_start(CsGtkStack->grid->mimeList, 16);
    gtk_widget_set_margin_end(CsGtkStack->grid->mimeList, 16);
    gtk_widget_set_margin_top(CsGtkStack->grid->mimeList, 16);
    gtk_widget_set_margin_bottom(CsGtkStack->grid->mimeList, 16);
    gtk_widget_set_margin_start(CsGtkStack->grid->mimeOpen, 16);
    gtk_widget_set_margin_end(CsGtkStack->grid->mimeOpen, 16);
    gtk_widget_set_margin_top(CsGtkStack->grid->mimeOpen, 16);
    gtk_widget_set_margin_bottom(CsGtkStack->grid->mimeOpen, 16);

    gtk_widget_set_vexpand(CsGtkStack->grid->mimeList, TRUE);
    gtk_widget_set_hexpand(CsGtkStack->grid->mimeList, TRUE);
    gtk_widget_set_vexpand(CsGtkStack->grid->mimeOpen, TRUE);
    gtk_widget_set_hexpand(CsGtkStack->grid->mimeOpen, TRUE);

    gtk_widget_set_valign(CsGtkStack->grid->mimeList, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(CsGtkStack->grid->mimeList, GTK_ALIGN_FILL);
    gtk_widget_set_valign(CsGtkStack->grid->mimeOpen, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(CsGtkStack->grid->mimeOpen, GTK_ALIGN_FILL);

    gtk_grid_set_row_homogeneous(GTK_GRID(CsGtkStack->grid->mimeList), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(CsGtkStack->grid->mimeList), FALSE);
    gtk_grid_set_row_homogeneous(GTK_GRID(CsGtkStack->grid->mimeOpen), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(CsGtkStack->grid->mimeOpen), FALSE);

    gtk_grid_set_row_spacing(GTK_GRID(CsGtkStack->grid->mimeList), 4);
    gtk_grid_set_column_spacing(GTK_GRID(CsGtkStack->grid->mimeList), 4);
    gtk_grid_set_row_spacing(GTK_GRID(CsGtkStack->grid->mimeOpen), 4);
    gtk_grid_set_column_spacing(GTK_GRID(CsGtkStack->grid->mimeOpen), 4);

    FvGtkMimeList(CsMap);
    FvGtkMimeOpen(CsMap);
}

