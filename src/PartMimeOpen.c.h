// PartMimeOpen.c.h



    void
FvGtkMimeOpen(SaMap* CsMap)
{
    // declaration
    SaGtkTab* CsGtkTab;
    SaGtkUri* CsGtkUri;
    GtkWidget* EgButton;

    // inherit
    CsGtkTab = CsMap->GtkTab;
    CsGtkUri = CsMap->GtkUri;

    // gtk.h new
    EgButton = gtk_button_new_with_label("OPEN");

    // gtk.h layout
    gtk_grid_attach(GTK_GRID(CsGtkTab->Grid->mimeOpen),
            EgButton, 0, 0, 1, 1);

    // gobject.h signal
    g_signal_connect(EgButton,
            "clicked", G_CALLBACK(FvGtkMimeListOpen), CsGtkTab);

    // gtk.h property
    gtk_widget_set_vexpand(EgButton, TRUE);
    gtk_widget_set_hexpand(EgButton, TRUE);
    gtk_widget_set_valign(EgButton, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(EgButton, GTK_ALIGN_FILL);
}


    void
FvGtkMimeListOpen(GtkWidget* EgButton, void* PvUserdata)
{
    // declaration
    SaGtkTab* CsGtkTab;
    SaGtkTab* CsGtkTabOld;
    SaGtkUri* CsGtkUri;
    SaGtkMime* CsGtkMime;
    const char* AcUri;
    GtkListBox* EgListbox;
    GtkListBoxRow* EgListrow;
    GAppInfo* EgAppinfo;
    GList* EgList;
    GFile* EgFile;

    // inherit
    CsGtkTabOld = PvUserdata;

    // malloc
    CsGtkTab = g_new0(SaGtkTab, 1);

    // branch inherit
    CsGtkTab->Paned = CsGtkTabOld->Paned;

    // gobject.h data
    CsGtkTab->GtkUri = g_object_get_data(G_OBJECT(CsGtkTab->Paned->base),
            "CsGtkUri");
    CsGtkTab->GtkMime = g_object_get_data(G_OBJECT(CsGtkTab->Paned->base),
            "CsGtkMime");

    // variable gtk.h
    EgListbox = GTK_LIST_BOX(CsGtkTab->GtkMime->listbox);
    EgListrow = gtk_list_box_get_selected_row(EgListbox);

    if (! EgListrow) return;

    // variable gio.h
    EgAppinfo = g_object_get_data(G_OBJECT(EgListrow), "EgAppinfo");

    if (! EgAppinfo) return;

    // PartUriChange.h
    AcUri = FaGtkUriEntryGet(CsGtkTab->GtkUri->Entry->uri);

    // varibale glib.h
    EgFile = AcUri ? g_file_new_for_uri(AcUri) : NULL;
    EgList = g_list_append(NULL, EgFile);

    // gio.h
    g_app_info_launch(EgAppinfo, EgList, NULL, NULL);

    // free
    g_list_free_full(EgList, g_object_unref);
}

