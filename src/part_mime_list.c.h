// part_mime_list.h



    void
FvGtkMimeListAdd(GtkListBox* UgListbox, GAppInfo* UgAppinfo)
{
    GtkWidget* UgGrid;
    GtkWidget* UgImage;
    GtkWidget* UgLabel;
    GtkWidget* UgListrow;
    GIcon* UgIcon;

    UgGrid = gtk_grid_new();
    UgListrow = gtk_list_box_row_new();
    UgImage = gtk_image_new();
    UgIcon = g_app_info_get_icon(UgAppinfo);
    UgLabel = gtk_label_new(g_app_info_get_name(UgAppinfo));

    gtk_grid_attach(GTK_GRID(UgGrid), UgImage, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(UgGrid), UgLabel, 1, 0, 1, 1);
    gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(UgListrow), UgGrid);
    gtk_list_box_append(GTK_LIST_BOX(UgListbox), UgListrow);

    g_object_set_data_full(G_OBJECT(UgListrow),
            "UgListrow", g_object_ref(UgAppinfo), g_object_unref);

    if (UgIcon) {
        gtk_image_set_from_gicon(GTK_IMAGE(UgImage), UgIcon);
    }
    else {
        gtk_image_set_from_icon_name(GTK_IMAGE(UgImage),
                "application-x-executable");
    }

    gtk_widget_set_size_request(UgListrow, -1, 32);
    gtk_widget_set_margin_top(UgListrow, 4);
    gtk_widget_set_margin_bottom(UgListrow, 4);
    gtk_image_set_pixel_size(GTK_IMAGE(UgImage), 24);
    gtk_widget_set_halign(UgLabel, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(UgLabel, GTK_ALIGN_CENTER);
    gtk_widget_set_vexpand(UgLabel, TRUE);
    gtk_widget_set_hexpand(UgLabel, TRUE);
    gtk_label_set_xalign(GTK_LABEL(UgLabel), 0.5);
}


    void
FvGtkMimeList(SuGtkBase* PsGtkBase, SuGtkMime* PsGtkMime)
{
    const char* VcAppid;
    GList* UgLoop;
    GAppInfo* UgAppinfo;
    GHashTable *UgHashtable;

    PsGtkMime->box->list = gtk_list_box_new();

    gtk_grid_attach(GTK_GRID(PsGtkBase->grid->mimeList),
            PsGtkMime->box->list, 0, 0, 1, 1);

    gtk_widget_set_vexpand(PsGtkMime->box->list, TRUE);
    gtk_widget_set_hexpand(PsGtkMime->box->list, TRUE);
    gtk_list_box_set_selection_mode(GTK_LIST_BOX(PsGtkMime->box->list),
            GTK_SELECTION_SINGLE);

    PsGtkMime->list->http = g_app_info_get_all_for_type(
            "x-scheme-handler/http");
    PsGtkMime->list->https = g_app_info_get_all_for_type(
            "x-scheme-handler/https");
    PsGtkMime->list->all = g_list_concat(PsGtkMime->list->http,
            PsGtkMime->list->https);
    UgHashtable = g_hash_table_new(g_str_hash, g_str_equal);

    for (UgLoop = PsGtkMime->list->all; UgLoop; UgLoop = UgLoop->next) {
        UgAppinfo = G_APP_INFO(UgLoop->data);
        VcAppid = g_app_info_get_id(UgAppinfo);
        if (g_hash_table_contains(UgHashtable, VcAppid)) continue;
        g_hash_table_add(UgHashtable, g_strdup(VcAppid));
        if (! g_app_info_supports_uris(UgAppinfo)) continue;
        FvGtkMimeListAdd(GTK_LIST_BOX(PsGtkMime->box->list), UgAppinfo);
    }

    g_list_free_full(PsGtkMime->list->all, g_object_unref);
    g_hash_table_destroy(UgHashtable);
}

