// part_mime_list.c.h



    void
FvGtkMimeList(SaMap* CsMap)
{
    SaGtkTab* CsGtkTab;
    SaGtkMime* CsGtkMime;
    SaGtkUri* CsGtkUri;
    const char* AcAppid;
    GList* EgLoop;
    GAppInfo* EgAppinfo;
    GHashTable *EgHashtable;

    CsGtkTab = CsMap->GtkTab;
    CsGtkMime = CsMap->GtkMime;
    CsGtkUri = CsMap->GtkUri;

    CsGtkMime->listbox = gtk_list_box_new();

    gtk_grid_attach(GTK_GRID(CsGtkTab->Grid->mimeList),
            CsGtkMime->listbox, 0, 0, 1, 1);

    gtk_widget_set_vexpand(CsGtkMime->listbox, TRUE);
    gtk_widget_set_hexpand(CsGtkMime->listbox, TRUE);
    gtk_list_box_set_selection_mode(GTK_LIST_BOX(CsGtkMime->listbox),
            GTK_SELECTION_SINGLE);

    CsGtkMime->List->http = g_app_info_get_all_for_type(
            "x-scheme-handler/http");
    CsGtkMime->List->https = g_app_info_get_all_for_type(
            "x-scheme-handler/https");
    CsGtkMime->List->all = g_list_concat(CsGtkMime->List->http,
            CsGtkMime->List->https);
    EgHashtable = g_hash_table_new(g_str_hash, g_str_equal);

    for (EgLoop = CsGtkMime->List->all; EgLoop; EgLoop = EgLoop->next) {
        EgAppinfo = G_APP_INFO(EgLoop->data);
        AcAppid = g_app_info_get_id(EgAppinfo);

        if (g_hash_table_contains(EgHashtable, AcAppid)) continue;
        g_hash_table_add(EgHashtable, g_strdup(AcAppid));
        if (! g_app_info_supports_uris(EgAppinfo)) continue;

        FvGtkMimeListAdd(GTK_LIST_BOX(CsGtkMime->listbox), EgAppinfo, CsMap);
    }

    g_list_free_full(CsGtkMime->List->all, g_object_unref);
    g_hash_table_destroy(EgHashtable);
}


    void
FvGtkMimeListAdd(GtkListBox* EgListbox, GAppInfo* EgAppinfo, void* PvUserdata)
{
    SaMap* CsMap;
    GtkWidget* EgGrid;
    GtkWidget* EgImage;
    GtkWidget* EgLabel;
    GtkWidget* EgListrow;
    GIcon* EgIcon;

    CsMap = PvUserdata;
    EgGrid = gtk_grid_new();
    EgListrow = gtk_list_box_row_new();
    EgImage = gtk_image_new();
    EgIcon = g_app_info_get_icon(EgAppinfo);
    EgLabel = gtk_label_new(g_app_info_get_name(EgAppinfo));

    gtk_grid_attach(GTK_GRID(EgGrid), EgImage, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(EgGrid), EgLabel, 1, 0, 1, 1);
    gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(EgListrow), EgGrid);
    gtk_list_box_append(GTK_LIST_BOX(EgListbox), EgListrow);

    g_object_set_data_full(G_OBJECT(EgListrow),
            "EgAppinfo", g_object_ref(EgAppinfo),
            (GDestroyNotify)g_object_unref);

    if (EgIcon) {
        gtk_image_set_from_gicon(GTK_IMAGE(EgImage),
                EgIcon);
    }
    else {
        gtk_image_set_from_icon_name(GTK_IMAGE(EgImage),
                "application-x-executable");
    }

    gtk_widget_set_size_request(EgListrow, -1, 32);
    gtk_widget_set_margin_top(EgListrow, 4);
    gtk_widget_set_margin_bottom(EgListrow, 4);
    gtk_image_set_pixel_size(GTK_IMAGE(EgImage), 24);
    gtk_widget_set_halign(EgLabel, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(EgLabel, GTK_ALIGN_CENTER);
    gtk_widget_set_vexpand(EgLabel, TRUE);
    gtk_widget_set_hexpand(EgLabel, TRUE);
    gtk_label_set_xalign(GTK_LABEL(EgLabel), 0.5);
}

