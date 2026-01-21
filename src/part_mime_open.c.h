// part_mime_open.c.h



    void
FvGtkMimeOpen(SaMap* CsMap)
{
    SaGtkTab* CsGtkTab;
    SaGtkUri* CsGtkUri;
    GtkWidget* EgButton;

    CsGtkTab = CsMap->GtkTab;
    CsGtkUri = CsMap->GtkUri;

    EgButton = gtk_button_new_with_label("OPEN");

    gtk_grid_attach(GTK_GRID(CsGtkTab->Grid->mimeOpen),
            EgButton, 0, 0, 1, 1);

    g_signal_connect(EgButton,
            "clicked", G_CALLBACK(FvGtkMimeListOpen), CsMap);

    gtk_widget_set_vexpand(EgButton, TRUE);
    gtk_widget_set_hexpand(EgButton, TRUE);
    gtk_widget_set_valign(EgButton, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(EgButton, GTK_ALIGN_FILL);
}


    void
FvGtkMimeListOpen(GtkWidget* EgBotton, void* PvUserdata)
{
    SaMap* CsMap;
    const char* AcUri;
    GtkListBox* EgListbox;
    GtkListBoxRow* EgListrow;
    GAppInfo* EgAppinfo;
    GList* EgList;
    GFile* EgFile;

    CsMap = PvUserdata;
    EgListbox = GTK_LIST_BOX(CsMap->GtkMime->listbox);
    EgListrow = gtk_list_box_get_selected_row(EgListbox);

    if (! EgListrow) return;

    EgAppinfo = g_object_get_data(G_OBJECT(EgListrow), "EgAppinfo");
    AcUri = FaGtkUriEntryGet(CsMap->GtkUri->Entry->uri);
    EgFile = AcUri ? g_file_new_for_uri(AcUri) : NULL;
    EgList = g_list_append(NULL, EgFile);

    if (! EgAppinfo) return;

    g_app_info_launch(EgAppinfo, EgList, NULL, NULL);

    g_list_free_full(EgList, g_object_unref);
}

