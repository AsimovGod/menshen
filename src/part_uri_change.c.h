// part_uri_change.h



    char*
FaGtkUriEntryGet(GtkWidget* EgEntry)
{
    const char* AcParse;

    AcParse = gtk_editable_get_text(GTK_EDITABLE(EgEntry));
    return AcParse && *AcParse ? g_strdup(AcParse) : g_strdup("");
}


    void
FvGtkUriEntrySet(GtkWidget* EgEntry, char* AcUriEntry)
{
    gtk_editable_set_text(GTK_EDITABLE(EgEntry), AcUriEntry ? AcUriEntry : "");
}


    void
FvGtkUriEntryBuild(GtkEditable* EgEditable, void* PvUserdata)
{
    SaGtkUri* CsGtkUri;
    int DiPort;
    char* AcText;

    CsGtkUri = PvUserdata;

    if (! CsGtkUri->entry || CsGtkUri->change) return;

    CsGtkUri->change = TRUE;

    if (CsGtkUri->parse->scheme) g_free(CsGtkUri->parse->scheme);
    if (CsGtkUri->parse->userinfo) g_free(CsGtkUri->parse->userinfo);
    if (CsGtkUri->parse->host) g_free(CsGtkUri->parse->host);
    if (CsGtkUri->parse->path) g_free(CsGtkUri->parse->path);
    if (CsGtkUri->parse->query) g_free(CsGtkUri->parse->query);
    if (CsGtkUri->parse->fragment) g_free(CsGtkUri->parse->fragment);

    CsGtkUri->parse->scheme = FaGtkUriEntryGet(CsGtkUri->entry->scheme);
    CsGtkUri->parse->userinfo = FaGtkUriEntryGet(CsGtkUri->entry->userinfo);
    CsGtkUri->parse->host = FaGtkUriEntryGet(CsGtkUri->entry->host);
    CsGtkUri->parse->path = FaGtkUriEntryGet(CsGtkUri->entry->path);
    CsGtkUri->parse->query = FaGtkUriEntryGet(CsGtkUri->entry->query);
    CsGtkUri->parse->fragment = FaGtkUriEntryGet(CsGtkUri->entry->fragment);

    DiPort = (int)gtk_spin_button_get_value(
            GTK_SPIN_BUTTON(CsGtkUri->entry->port));
    CsGtkUri->parse->port = DiPort ? DiPort : -1;

    AcText = FaGuriBuild(CsGtkUri->parse);
    gtk_editable_set_text(GTK_EDITABLE(CsGtkUri->entry->uri),
            AcText ? AcText : "");

    if (AcText) g_free(AcText);

    CsGtkUri->change = FALSE;
}


    void
FvGtkUriEntryParse(GtkEditable* EgEditable, void* PvUserdata)
{
    SaGtkUri* CsGtkUri;
    SaGuriParse* CsUriParse;
    const char* AcText;

    CsGtkUri = PvUserdata;

    if (! CsGtkUri->entry || CsGtkUri->change) return;

    CsGtkUri->change = TRUE;

    if (CsGtkUri->parse) g_free(CsGtkUri->parse);

    AcText = gtk_editable_get_text(EgEditable);
    CsUriParse = FsGuriParse(AcText ? AcText : NULL);
    CsGtkUri->parse = CsUriParse ? CsUriParse : g_new0(SaGuriParse, 1);

    FvGtkUriEntrySet(CsGtkUri->entry->scheme, CsGtkUri->parse->scheme);
    FvGtkUriEntrySet(CsGtkUri->entry->userinfo, CsGtkUri->parse->userinfo);
    FvGtkUriEntrySet(CsGtkUri->entry->host, CsGtkUri->parse->host);
    FvGtkUriEntrySet(CsGtkUri->entry->path, CsGtkUri->parse->path);
    FvGtkUriEntrySet(CsGtkUri->entry->query, CsGtkUri->parse->query);
    FvGtkUriEntrySet(CsGtkUri->entry->fragment, CsGtkUri->parse->fragment);

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(CsGtkUri->entry->port),
            CsGtkUri->parse->port ? CsGtkUri->parse->port : -1);

    CsGtkUri->change = FALSE;
}

