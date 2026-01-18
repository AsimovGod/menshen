// part_mime_open.h



    void
FvGtkMimeListOpen(GtkButton *UgBotton, void* PvUserdata)
{
    const char* VcUri;
    GtkListBox* UgListbox;
    GtkListBoxRow* UgListrow;
    GAppInfo* UgAppinfo;
    GList* UgList;
    GFile* UgFile;
    SuGtkBase* PsGtkBase;

    PsGtkBase = PvUserdata;
    UgListbox = GTK_LIST_BOX(PsGtkBase->GtkMime->box->list);
    UgListrow = gtk_list_box_get_selected_row(UgListbox);

    if (! UgListrow) return;

    UgAppinfo = g_object_get_data(G_OBJECT(UgListrow), "UgListrow");
    VcUri = FcGtkUriEntryGet(PsGtkBase->GtkUri->entry->uri);
    UgFile = VcUri ? g_file_new_for_uri(VcUri) : NULL;
    UgList = g_list_append(NULL, UgFile);

    if (! UgAppinfo) return;

    g_app_info_launch(UgAppinfo, UgList, NULL, NULL);

    g_list_free_full(UgList, g_object_unref);
}


    void
FvGtkMimeOpen(SuGtkBase* PsGtkBase, SuGtkMime* PsGtkMime)
{
    GtkWidget* UgButton;

    UgButton = gtk_button_new_with_label("OPEN");

    gtk_grid_attach(GTK_GRID(PsGtkBase->grid->mimeOpen),
            UgButton, 0, 0, 1, 1);

    g_signal_connect(UgButton,
            "clicked", G_CALLBACK(FvGtkMimeListOpen), PsGtkBase);

    gtk_widget_set_vexpand(UgButton, TRUE);
    gtk_widget_set_hexpand(UgButton, TRUE);
    gtk_widget_set_valign(UgButton, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(UgButton, GTK_ALIGN_FILL);
}

