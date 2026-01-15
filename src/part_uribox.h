#include <stdio.h>




_Bool VbUriChange = FALSE;



    char*
FcGtkUriEntryGet(GtkWidget* UgUriEntry)
{
    const char* VcUriParse;

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UgUriEntry));
    return VcUriParse && *VcUriParse ? g_strdup(VcUriParse) : g_strdup("");
}


    void
FvGtkUriEntrySet(GtkWidget* UgUriEntry, char* VcUriEntry)
{
    gtk_editable_set_text(GTK_EDITABLE(UgUriEntry),
            VcUriEntry ? VcUriEntry : "");
}


    void
FvGtkUriBuild(GtkEditable* UgEditable, void* GuUserdata)
{
    const char* VcUriParse;
    int ViUriParsePort;
    char* VcEdittext;
    TgGtkUri* UtGtkUri;

    UtGtkUri = GuUserdata;

    if (! UtGtkUri->entry || VbUriChange) return;

    VbUriChange = TRUE;

    UtGtkUri->parse->scheme = FcGtkUriEntryGet(UtGtkUri->entry->scheme);
    UtGtkUri->parse->userinfo = FcGtkUriEntryGet(UtGtkUri->entry->userinfo);
    UtGtkUri->parse->host = FcGtkUriEntryGet(UtGtkUri->entry->host);
    UtGtkUri->parse->path = FcGtkUriEntryGet(UtGtkUri->entry->path);
    UtGtkUri->parse->query = FcGtkUriEntryGet(UtGtkUri->entry->query);
    UtGtkUri->parse->fragment = FcGtkUriEntryGet(UtGtkUri->entry->fragment);

    ViUriParsePort = (int)gtk_spin_button_get_value(
            GTK_SPIN_BUTTON(UtGtkUri->spin->port));
    UtGtkUri->parse->port = ViUriParsePort ? ViUriParsePort : -1;

    VcEdittext = FcGuriBuild(UtGtkUri->parse);
    gtk_editable_set_text(GTK_EDITABLE(UtGtkUri->entry->uri),
            VcEdittext ? VcEdittext : "");

    if (VcEdittext) g_free(VcEdittext);

    VbUriChange = FALSE;
}


    void
FvGtkUriParse(GtkEditable* UgEditable, void* GuUserdata)
{
    const char* VcEdittext;
    TgGuriParse* UtUriParse;
    TgGtkUri* UtGtkUri;

    UtGtkUri = GuUserdata;

    if (! UtGtkUri->entry || VbUriChange) return;

    VbUriChange = TRUE;

    VcEdittext = gtk_editable_get_text(UgEditable);
    UtUriParse = FtGuriParse(VcEdittext ? VcEdittext : NULL);
    UtGtkUri->parse = UtUriParse ? UtUriParse : g_new0(TgGuriParse, 1);

    FvGtkUriEntrySet(UtGtkUri->entry->scheme, UtGtkUri->parse->scheme);
    FvGtkUriEntrySet(UtGtkUri->entry->userinfo, UtGtkUri->parse->userinfo);
    FvGtkUriEntrySet(UtGtkUri->entry->host, UtGtkUri->parse->host);
    FvGtkUriEntrySet(UtGtkUri->entry->path, UtGtkUri->parse->path);
    FvGtkUriEntrySet(UtGtkUri->entry->query, UtGtkUri->parse->query);
    FvGtkUriEntrySet(UtGtkUri->entry->fragment, UtGtkUri->parse->fragment);

    VbUriChange = FALSE;
}


    void
FvGtkUriEntryClear(GtkEntry* UgUriEntry,
        GtkEntryIconPosition UgUriPos,
        GdkEvent* UgUriEvent,
        void* GuUriUserdata)
{
    if (UgUriPos == GTK_ENTRY_ICON_SECONDARY) {
        gtk_editable_delete_text(GTK_EDITABLE(UgUriEntry), 0, -1);
    }
}


    void
FvGtkUriEntry(TgGtkUri* UtGtkUri, GtkWidget* UgUriParent,
        GtkWidget** UgUriEntry, int ViUriRow, const char* VcUriLabel)
{
    *UgUriEntry = gtk_entry_new();

    gtk_widget_set_hexpand(*UgUriEntry, TRUE);
    gtk_widget_set_margin_end(*UgUriEntry, 16);

    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(*UgUriEntry),
            GTK_ENTRY_ICON_SECONDARY, "edit-clear-symbolic");

    g_signal_connect(*UgUriEntry,
            "icon-press", G_CALLBACK(FvGtkUriEntryClear), NULL);

    if (*UgUriEntry == UtGtkUri->entry->uri) {
        g_signal_connect(*UgUriEntry,
                "changed", G_CALLBACK(FvGtkUriParse), UtGtkUri);
    }
    else {
        g_signal_connect(*UgUriEntry,
                "changed", G_CALLBACK(FvGtkUriBuild), UtGtkUri);
    }

    gtk_grid_attach(GTK_GRID(UgUriParent),
            *UgUriEntry, 1, ViUriRow, 2, 1);

    gtk_grid_attach(GTK_GRID(UgUriParent),
            gtk_label_new(VcUriLabel), 0, ViUriRow, 1, 1);
}


    void
FvGtkUriSpin(TgGtkContainer* UtGtkContainer, TgGtkUri* UtGtkUri)
{
    UtGtkUri->spin->port = gtk_spin_button_new_with_range(-1, 65535, 1);

    gtk_widget_set_hexpand(UtGtkUri->spin->port, TRUE);
    gtk_widget_set_margin_end(UtGtkUri->spin->port, 16);

    g_signal_connect(UtGtkUri->spin->port,
            "value-changed", G_CALLBACK(FvGtkUriBuild), UtGtkUri);

    gtk_grid_attach(GTK_GRID(UtGtkContainer->grid->uriParse),
            UtGtkUri->spin->port, 1, 3, 1, 1);

    gtk_grid_attach(GTK_GRID(UtGtkContainer->grid->uriParse),
            gtk_label_new("Port:"), 0, 3, 1, 1);
}


    void
FvGtkUriWidget(TgGtkContainer* UtGtkContainer, TgGtkUri* UtGtkUri)
{
    FvGtkUriEntry(UtGtkUri, UtGtkContainer->grid->uriBuild,
            &UtGtkUri->entry->uri, 0, "URI:");
    FvGtkUriEntry(UtGtkUri, UtGtkContainer->grid->uriParse,
            &UtGtkUri->entry->scheme, 0, "Scheme:");
    FvGtkUriEntry(UtGtkUri, UtGtkContainer->grid->uriParse,
            &UtGtkUri->entry->host, 1, "Host:");
    FvGtkUriEntry(UtGtkUri, UtGtkContainer->grid->uriParse,
            &UtGtkUri->entry->userinfo, 2, "Userinfo:");
    FvGtkUriEntry(UtGtkUri, UtGtkContainer->grid->uriParse,
            &UtGtkUri->entry->path, 4, "Path:");
    FvGtkUriEntry(UtGtkUri, UtGtkContainer->grid->uriParse,
            &UtGtkUri->entry->query, 5, "Query:");
    FvGtkUriEntry(UtGtkUri, UtGtkContainer->grid->uriParse,
            &UtGtkUri->entry->fragment, 6, "Fragment:");

    FvGtkUriSpin(UtGtkContainer, UtGtkUri);
}

