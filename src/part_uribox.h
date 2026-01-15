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
FvGtkUriEntry(TgGtkContainer* UtGtkContainer, TgGtkUri* UtGtkUri)
{
    UtGtkUri->entry->scheme = gtk_entry_new();
    UtGtkUri->entry->userinfo = gtk_entry_new();
    UtGtkUri->entry->host = gtk_entry_new();
    UtGtkUri->entry->path = gtk_entry_new();
    UtGtkUri->entry->query = gtk_entry_new();
    UtGtkUri->entry->fragment = gtk_entry_new();
    UtGtkUri->entry->uri = gtk_entry_new();

    gtk_box_append(GTK_BOX(UtGtkContainer->box->uriParse),
            UtGtkUri->entry->scheme);
    gtk_box_append(GTK_BOX(UtGtkContainer->box->uriParse),
            UtGtkUri->entry->userinfo);
    gtk_box_append(GTK_BOX(UtGtkContainer->box->uriParse),
            UtGtkUri->entry->host);
    gtk_box_append(GTK_BOX(UtGtkContainer->box->uriParse),
            UtGtkUri->entry->path);
    gtk_box_append(GTK_BOX(UtGtkContainer->box->uriParse),
            UtGtkUri->entry->query);
    gtk_box_append(GTK_BOX(UtGtkContainer->box->uriParse),
            UtGtkUri->entry->fragment);
    gtk_box_append(GTK_BOX(UtGtkContainer->box->uriBuild),
            UtGtkUri->entry->uri);

    g_signal_connect(UtGtkUri->entry->uri,
            "changed", G_CALLBACK(FvGtkUriParse), UtGtkUri);
    g_signal_connect(UtGtkUri->entry->scheme,
            "changed", G_CALLBACK(FvGtkUriBuild), UtGtkUri);
    g_signal_connect(UtGtkUri->entry->userinfo,
            "changed", G_CALLBACK(FvGtkUriBuild), UtGtkUri);
    g_signal_connect(UtGtkUri->entry->host,
            "changed", G_CALLBACK(FvGtkUriBuild), UtGtkUri);
    g_signal_connect(UtGtkUri->entry->path,
            "changed", G_CALLBACK(FvGtkUriBuild), UtGtkUri);
    g_signal_connect(UtGtkUri->entry->query,
            "changed", G_CALLBACK(FvGtkUriBuild), UtGtkUri);
    g_signal_connect(UtGtkUri->entry->fragment,
            "changed", G_CALLBACK(FvGtkUriBuild), UtGtkUri);
}


    void
FvGtkUriSpin(TgGtkContainer* UtGtkContainer, TgGtkUri* UtGtkUri)
{
    UtGtkUri->spin->port = gtk_spin_button_new_with_range(-1, 65535, 1);

    gtk_box_append(GTK_BOX(UtGtkContainer->box->uriParse),
            UtGtkUri->spin->port);

    g_signal_connect(UtGtkUri->spin->port,
            "value-changed", G_CALLBACK(FvGtkUriBuild), UtGtkUri);
}


    void
FvGtkUriWidget(TgGtkContainer* UtGtkContainer, TgGtkUri* UtGtkUri)
{
    FvGtkUriSpin(UtGtkContainer, UtGtkUri);
    FvGtkUriEntry(UtGtkContainer, UtGtkUri);
}

