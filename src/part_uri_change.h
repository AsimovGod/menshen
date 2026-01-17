// part_uri_change.h



    char*
FcGtkUriEntryGet(GtkWidget* UgEntry)
{
    const char* VcParse;

    VcParse = gtk_editable_get_text(GTK_EDITABLE(UgEntry));
    return VcParse && *VcParse ? g_strdup(VcParse) : g_strdup("");
}


    void
FvGtkUriEntrySet(GtkWidget* UgEntry, char* VcUriEntry)
{
    gtk_editable_set_text(GTK_EDITABLE(UgEntry), VcUriEntry ? VcUriEntry : "");
}


    void
FvGtkUriEntryBuild(GtkEditable* UgEditable, void* PvUserdata)
{
    int ViPort;
    char* VcText;
    SuGtkUri* PsGtkUri;

    PsGtkUri = PvUserdata;

    if (! PsGtkUri->entry || PsGtkUri->boolean) return;

    PsGtkUri->boolean = TRUE;

    if (PsGtkUri->parse->scheme) g_free(PsGtkUri->parse->scheme);
    if (PsGtkUri->parse->userinfo) g_free(PsGtkUri->parse->userinfo);
    if (PsGtkUri->parse->host) g_free(PsGtkUri->parse->host);
    if (PsGtkUri->parse->path) g_free(PsGtkUri->parse->path);
    if (PsGtkUri->parse->query) g_free(PsGtkUri->parse->query);
    if (PsGtkUri->parse->fragment) g_free(PsGtkUri->parse->fragment);

    PsGtkUri->parse->scheme = FcGtkUriEntryGet(PsGtkUri->entry->scheme);
    PsGtkUri->parse->userinfo = FcGtkUriEntryGet(PsGtkUri->entry->userinfo);
    PsGtkUri->parse->host = FcGtkUriEntryGet(PsGtkUri->entry->host);
    PsGtkUri->parse->path = FcGtkUriEntryGet(PsGtkUri->entry->path);
    PsGtkUri->parse->query = FcGtkUriEntryGet(PsGtkUri->entry->query);
    PsGtkUri->parse->fragment = FcGtkUriEntryGet(PsGtkUri->entry->fragment);

    ViPort = (int)gtk_spin_button_get_value(
            GTK_SPIN_BUTTON(PsGtkUri->spin->port));
    PsGtkUri->parse->port = ViPort ? ViPort : -1;

    VcText = FcGuriBuild(PsGtkUri->parse);
    gtk_editable_set_text(GTK_EDITABLE(PsGtkUri->entry->uri),
            VcText ? VcText : "");

    g_object_set_data_full(G_OBJECT(PsGtkUri->entry->uri),
            "PsGtkUri->entry->uri", g_strdup(VcText), g_free);

    if (VcText) g_free(VcText);

    PsGtkUri->boolean = FALSE;
}


    void
FvGtkUriEntryParse(GtkEditable* UgEditable, void* PvUserdata)
{
    const char* VcText;
    SuGuriParse* PsUriParse;
    SuGtkUri* PsGtkUri;

    PsGtkUri = PvUserdata;

    if (! PsGtkUri->entry || PsGtkUri->boolean) return;

    PsGtkUri->boolean = TRUE;

    if (PsGtkUri->parse) g_free(PsGtkUri->parse);

    VcText = gtk_editable_get_text(UgEditable);
    PsUriParse = FtGuriParse(VcText ? VcText : NULL);
    PsGtkUri->parse = PsUriParse ? PsUriParse : g_new0(SuGuriParse, 1);

    FvGtkUriEntrySet(PsGtkUri->entry->scheme, PsGtkUri->parse->scheme);
    FvGtkUriEntrySet(PsGtkUri->entry->userinfo, PsGtkUri->parse->userinfo);
    FvGtkUriEntrySet(PsGtkUri->entry->host, PsGtkUri->parse->host);
    FvGtkUriEntrySet(PsGtkUri->entry->path, PsGtkUri->parse->path);
    FvGtkUriEntrySet(PsGtkUri->entry->query, PsGtkUri->parse->query);
    FvGtkUriEntrySet(PsGtkUri->entry->fragment, PsGtkUri->parse->fragment);

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(PsGtkUri->spin->port),
            PsGtkUri->parse->port ? PsGtkUri->parse->port : -1);

    g_object_set_data_full(G_OBJECT(PsGtkUri->entry->uri),
            "PsGtkUri->entry->uri", g_strdup(VcText), g_free);

    PsGtkUri->boolean = FALSE;
}

