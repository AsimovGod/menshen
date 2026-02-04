// PartMimeList.c.h



struct SaGtkMimeList {
    // glib.h
    GList* http;
    GList* https;
    GList* all;
};



    void
FvGtkMimeList(SaMap* CsMap)
{
    //declaration
    SaGtkMime* CsGtkMime;
    const char* AcAppid;
    GList* EgLoop;
    GAppInfo* EgAppinfo;
    GHashTable *EgHashtable;

    // inherit
    CsGtkMime = CsMap->GtkMime;

    // malloc
    CsGtkMime->List = g_new0(SaGtkMimeList, 1);

    // gtk.h property
    gtk_widget_set_vexpand(CsGtkMime->listbox, TRUE);
    gtk_widget_set_hexpand(CsGtkMime->listbox, TRUE);
    gtk_list_box_set_selection_mode(GTK_LIST_BOX(CsGtkMime->listbox),
            GTK_SELECTION_SINGLE);

    // gio.h mime
    CsGtkMime->List->http = g_app_info_get_all_for_type(
            "x-scheme-handler/http");
    CsGtkMime->List->https = g_app_info_get_all_for_type(
            "x-scheme-handler/https");

    // glib.h list
    CsGtkMime->List->all = g_list_concat(CsGtkMime->List->http,
            CsGtkMime->List->https);

    // glib.h hash
    EgHashtable = g_hash_table_new(g_str_hash, g_str_equal);

    // loop glib.h mime
    for (EgLoop = CsGtkMime->List->all; EgLoop; EgLoop = EgLoop->next) {
        // block gio.h mime
        EgAppinfo = G_APP_INFO(EgLoop->data);
        AcAppid = g_app_info_get_id(EgAppinfo);
        // block glib.h hash
        if (g_hash_table_contains(EgHashtable, AcAppid)) continue;
        g_hash_table_add(EgHashtable, g_strdup(AcAppid));
        if (! g_app_info_supports_uris(EgAppinfo)) continue;
        // block PartMiMeList.c.h
        FvGtkMimeListAdd(GTK_LIST_BOX(CsGtkMime->listbox), EgAppinfo, CsMap);
    }

    // free
    g_list_free_full(CsGtkMime->List->all, g_object_unref);
    g_hash_table_destroy(EgHashtable);
}


    void
FvGtkMimeListAdd(GtkListBox* EgListbox, GAppInfo* EgAppinfo, void* PvUserdata)
{
    // declaration
    GtkWidget* EgGrid;
    GtkWidget* EgImage;
    GtkWidget* EgLabel;
    GtkWidget* EgListrow;
    GIcon* EgIcon;

    // gtk.h new
    EgGrid = gtk_grid_new();
    EgListrow = gtk_list_box_row_new();
    EgImage = gtk_image_new();
    EgIcon = g_app_info_get_icon(EgAppinfo);
    EgLabel = gtk_label_new(g_app_info_get_name(EgAppinfo));

    // gtk.h layout
    gtk_grid_attach(GTK_GRID(EgGrid), EgImage, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(EgGrid), EgLabel, 1, 0, 1, 1);
    gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(EgListrow), EgGrid);
    gtk_list_box_append(GTK_LIST_BOX(EgListbox), EgListrow);

    if (EgIcon) {
        gtk_image_set_from_gicon(GTK_IMAGE(EgImage),
                EgIcon);
    }
    else {
        gtk_image_set_from_icon_name(GTK_IMAGE(EgImage),
                "application-x-executable");
    }

    // gobject.h data
    g_object_set_data_full(G_OBJECT(EgListrow),
            "EgAppinfo", g_object_ref(EgAppinfo),
            (GDestroyNotify)g_object_unref);

    // gtk.h property
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


    void
FvGtkMimeListPress(GtkGestureClick* EgCtrl,
        double DfCtrlX, double DfCtrlY, unsigned int DiButton, void* PvUserdata)
{
    // declaration
    SaGtkMime* CsGtkMime;
    GtkListBoxRow* EgListboxrow;

    // inherit
    CsGtkMime = PvUserdata;

    if (! CsGtkMime) return;

    // variable gtk.h
    EgListboxrow = gtk_list_box_get_row_at_y(GTK_LIST_BOX(CsGtkMime->listbox),
            (int)DfCtrlY);

    if (! EgListboxrow) {
        gtk_list_box_unselect_all(GTK_LIST_BOX(CsGtkMime->listbox));
    }
}

