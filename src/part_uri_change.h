#include <stdio.h>




_Bool VbUriChange = FALSE;



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
FvGtkUriEntryBuild(GtkEditable* UgEditable, void* GuUserdata)
{
    int ViPort;
    char* VcText;
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

    ViPort = (int)gtk_spin_button_get_value(
            GTK_SPIN_BUTTON(UtGtkUri->spin->port));
    UtGtkUri->parse->port = ViPort ? ViPort : -1;

    VcText = FcGuriBuild(UtGtkUri->parse);
    gtk_editable_set_text(GTK_EDITABLE(UtGtkUri->entry->uri),
            VcText ? VcText : "");

    if (VcText) g_free(VcText);

    VbUriChange = FALSE;
}


    void
FvGtkUriEntryParse(GtkEditable* UgEditable, void* GuUserdata)
{
    const char* VcText;
    TgGuriParse* UtUriParse;
    TgGtkUri* UtGtkUri;

    UtGtkUri = GuUserdata;

    if (! UtGtkUri->entry || VbUriChange) return;

    VbUriChange = TRUE;

    VcText = gtk_editable_get_text(UgEditable);
    UtUriParse = FtGuriParse(VcText ? VcText : NULL);
    UtGtkUri->parse = UtUriParse ? UtUriParse : g_new0(TgGuriParse, 1);

    FvGtkUriEntrySet(UtGtkUri->entry->scheme, UtGtkUri->parse->scheme);
    FvGtkUriEntrySet(UtGtkUri->entry->userinfo, UtGtkUri->parse->userinfo);
    FvGtkUriEntrySet(UtGtkUri->entry->host, UtGtkUri->parse->host);
    FvGtkUriEntrySet(UtGtkUri->entry->path, UtGtkUri->parse->path);
    FvGtkUriEntrySet(UtGtkUri->entry->query, UtGtkUri->parse->query);
    FvGtkUriEntrySet(UtGtkUri->entry->fragment, UtGtkUri->parse->fragment);

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(UtGtkUri->spin->port),
            UtGtkUri->parse->port ? UtGtkUri->parse->port : -1);

    VbUriChange = FALSE;
}

