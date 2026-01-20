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

    if (! CsGtkUri->Entry || CsGtkUri->change) return;

    CsGtkUri->change = TRUE;

    if (CsGtkUri->Parse->scheme) g_free(CsGtkUri->Parse->scheme);
    if (CsGtkUri->Parse->userinfo) g_free(CsGtkUri->Parse->userinfo);
    if (CsGtkUri->Parse->host) g_free(CsGtkUri->Parse->host);
    if (CsGtkUri->Parse->path) g_free(CsGtkUri->Parse->path);
    if (CsGtkUri->Parse->query) g_free(CsGtkUri->Parse->query);
    if (CsGtkUri->Parse->fragment) g_free(CsGtkUri->Parse->fragment);

    CsGtkUri->Parse->scheme = FaGtkUriEntryGet(CsGtkUri->Entry->scheme);
    CsGtkUri->Parse->userinfo = FaGtkUriEntryGet(CsGtkUri->Entry->userinfo);
    CsGtkUri->Parse->host = FaGtkUriEntryGet(CsGtkUri->Entry->host);
    CsGtkUri->Parse->path = FaGtkUriEntryGet(CsGtkUri->Entry->path);
    CsGtkUri->Parse->query = FaGtkUriEntryGet(CsGtkUri->Entry->query);
    CsGtkUri->Parse->fragment = FaGtkUriEntryGet(CsGtkUri->Entry->fragment);

    DiPort = (int)gtk_spin_button_get_value(
            GTK_SPIN_BUTTON(CsGtkUri->Entry->port));
    CsGtkUri->Parse->port = DiPort ? DiPort : -1;

    AcText = FaGuriBuild(CsGtkUri->Parse);
    gtk_editable_set_text(GTK_EDITABLE(CsGtkUri->Entry->uri),
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

    if (! CsGtkUri->Entry || CsGtkUri->change) return;

    CsGtkUri->change = TRUE;

    if (CsGtkUri->Parse) g_free(CsGtkUri->Parse);

    AcText = gtk_editable_get_text(EgEditable);
    CsUriParse = FsGuriParse(AcText ? AcText : NULL);
    CsGtkUri->Parse = CsUriParse ? CsUriParse : g_new0(SaGuriParse, 1);

    FvGtkUriEntrySet(CsGtkUri->Entry->scheme, CsGtkUri->Parse->scheme);
    FvGtkUriEntrySet(CsGtkUri->Entry->userinfo, CsGtkUri->Parse->userinfo);
    FvGtkUriEntrySet(CsGtkUri->Entry->host, CsGtkUri->Parse->host);
    FvGtkUriEntrySet(CsGtkUri->Entry->path, CsGtkUri->Parse->path);
    FvGtkUriEntrySet(CsGtkUri->Entry->query, CsGtkUri->Parse->query);
    FvGtkUriEntrySet(CsGtkUri->Entry->fragment, CsGtkUri->Parse->fragment);

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(CsGtkUri->Entry->port),
            CsGtkUri->Parse->port ? CsGtkUri->Parse->port : -1);

    CsGtkUri->change = FALSE;
}

