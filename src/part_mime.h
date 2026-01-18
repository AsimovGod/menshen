// part_mime.h



    void
FvGtkMimeFree(void* PvFree)
{
    SuGtkMime* PsGtkMime;

    PsGtkMime = PvFree;

    if (! PsGtkMime) return;

    g_free(PsGtkMime->list);
    g_free(PsGtkMime->box);
    g_free(PsGtkMime->button);
    g_free(PsGtkMime);
}


    void
FvGtkMime(SuGtkBase* PsGtkBase)
{
    SuGtkMime* PsGtkMime;

    PsGtkMime = PsGtkBase->GtkMime;
    PsGtkMime->list = g_new0(SuGtkMimeList, 1);
    PsGtkMime->box = g_new0(SuGtkMimeBox, 1);
    PsGtkMime->button = g_new0(SuGtkMimeButton, 1);

    PsGtkBase->scroll->mimeList = gtk_scrolled_window_new();
    PsGtkBase->scroll->mimeOpen = gtk_scrolled_window_new();
    PsGtkBase->grid->mimeList = gtk_grid_new();
    PsGtkBase->grid->mimeOpen = gtk_grid_new();

    g_object_set_data_full(G_OBJECT(PsGtkBase->window->main),
            "PsGtkMime", PsGtkMime, (GDestroyNotify)FvGtkMimeFree);

    gtk_paned_set_start_child(GTK_PANED(PsGtkBase->paned->mainRight),
            PsGtkBase->scroll->mimeList);
    gtk_paned_set_end_child(GTK_PANED(PsGtkBase->paned->mainRight),
            PsGtkBase->scroll->mimeOpen);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                PsGtkBase->scroll->mimeList), PsGtkBase->grid->mimeList);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                PsGtkBase->scroll->mimeOpen), PsGtkBase->grid->mimeOpen);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                PsGtkBase->scroll->mimeList),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                PsGtkBase->scroll->mimeOpen),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_widget_set_margin_start(PsGtkBase->grid->mimeList, 16);
    gtk_widget_set_margin_end(PsGtkBase->grid->mimeList, 16);
    gtk_widget_set_margin_top(PsGtkBase->grid->mimeList, 16);
    gtk_widget_set_margin_bottom(PsGtkBase->grid->mimeList, 16);
    gtk_widget_set_margin_start(PsGtkBase->grid->mimeOpen, 16);
    gtk_widget_set_margin_end(PsGtkBase->grid->mimeOpen, 16);
    gtk_widget_set_margin_top(PsGtkBase->grid->mimeOpen, 16);
    gtk_widget_set_margin_bottom(PsGtkBase->grid->mimeOpen, 16);

    gtk_widget_set_vexpand(PsGtkBase->grid->mimeList, TRUE);
    gtk_widget_set_hexpand(PsGtkBase->grid->mimeList, TRUE);
    gtk_widget_set_vexpand(PsGtkBase->grid->mimeOpen, TRUE);
    gtk_widget_set_hexpand(PsGtkBase->grid->mimeOpen, TRUE);

    gtk_widget_set_valign(PsGtkBase->grid->mimeList, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(PsGtkBase->grid->mimeList, GTK_ALIGN_FILL);
    gtk_widget_set_valign(PsGtkBase->grid->mimeOpen, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(PsGtkBase->grid->mimeOpen, GTK_ALIGN_FILL);

    gtk_grid_set_row_homogeneous(GTK_GRID(PsGtkBase->grid->mimeList), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(PsGtkBase->grid->mimeList), FALSE);
    gtk_grid_set_row_homogeneous(GTK_GRID(PsGtkBase->grid->mimeOpen), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(PsGtkBase->grid->mimeOpen), FALSE);

    gtk_grid_set_row_spacing(GTK_GRID(PsGtkBase->grid->mimeList), 4);
    gtk_grid_set_column_spacing(GTK_GRID(PsGtkBase->grid->mimeList), 4);
    gtk_grid_set_row_spacing(GTK_GRID(PsGtkBase->grid->mimeOpen), 4);
    gtk_grid_set_column_spacing(GTK_GRID(PsGtkBase->grid->mimeOpen), 4);

    FvGtkMimeList(PsGtkBase, PsGtkMime);
    FvGtkMimeOpen(PsGtkBase, PsGtkMime);
}

