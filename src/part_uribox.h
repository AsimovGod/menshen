#include <stdio.h>




_Bool VbUriChange = FALSE;


    void
FvGtkUriBuild(GtkEditable* UgEditable, void* GuUserdata)
{
    const char* VcUriParse;
    int ViUriParsePort;
    char* VcEdittext;
    TgGuriWidget* UtUriWidget;

    UtUriWidget = GuUserdata;

    if (! UtUriWidget || VbUriChange) return;

    VbUriChange = TRUE;

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->scheme));
    UtUriWidget->parse->scheme = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : g_strdup("");

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->userinfo));
    UtUriWidget->parse->userinfo = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : g_strdup("");

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->host));
    UtUriWidget->parse->host = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : g_strdup("");

    ViUriParsePort = (int)gtk_spin_button_get_value(
            GTK_SPIN_BUTTON(UtUriWidget->port));
    UtUriWidget->parse->port = ViUriParsePort ? ViUriParsePort : -1;

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->path));
    UtUriWidget->parse->path = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : g_strdup("");

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->query));
    UtUriWidget->parse->query = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : g_strdup("");

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->fragment));
    UtUriWidget->parse->fragment = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : g_strdup("");

    VcEdittext = FcGuriBuild(UtUriWidget->parse);
    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->uri),
            VcEdittext ? VcEdittext : "");

    if (VcEdittext) g_free(VcEdittext);

    VbUriChange = FALSE;
}


    void
FvGtkUriParse(GtkEditable* UgEditable, void* GuUserdata)
{
    const char* VcEdittext;
    TgGuriWidget* UtUriWidget;

    UtUriWidget = GuUserdata;

    if (! UtUriWidget || VbUriChange) return;

    VbUriChange = TRUE;

    VcEdittext = gtk_editable_get_text(UgEditable);
    UtUriWidget->parse = FtGuriParse(VcEdittext ? VcEdittext : NULL);

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->scheme),
            UtUriWidget->parse && UtUriWidget->parse->scheme
            ? UtUriWidget->parse->scheme : "");

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->userinfo),
            UtUriWidget->parse && UtUriWidget->parse->userinfo
            ? UtUriWidget->parse->userinfo : "");

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->host),
            UtUriWidget->parse && UtUriWidget->parse->host
            ? UtUriWidget->parse->host : "");

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(UtUriWidget->port),
            UtUriWidget->parse && UtUriWidget->parse->port
            ? UtUriWidget->parse->port : -1);

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->path),
            UtUriWidget->parse && UtUriWidget->parse->path
            ? UtUriWidget->parse->path : "");

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->query),
            UtUriWidget->parse && UtUriWidget->parse->query
            ? UtUriWidget->parse->query : "");

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->fragment),
            UtUriWidget->parse && UtUriWidget->parse->fragment
            ? UtUriWidget->parse->fragment : "");

    VbUriChange = FALSE;
}


    void
FvGtkUriWidget(TgGtkContainer* UtGtkContainer, TgGuriWidget* UtUriWidget)
{
    UtUriWidget->scheme = gtk_entry_new();
    UtUriWidget->userinfo = gtk_entry_new();
    UtUriWidget->host = gtk_entry_new();
    UtUriWidget->port = gtk_spin_button_new_with_range(-1, 65535, 1);
    UtUriWidget->path = gtk_entry_new();
    UtUriWidget->query = gtk_entry_new();
    UtUriWidget->fragment = gtk_entry_new();
    UtUriWidget->uri = gtk_entry_new();

    gtk_box_append(GTK_BOX(UtGtkContainer->box->uriParse),
            UtUriWidget->scheme);
    gtk_box_append(GTK_BOX(UtGtkContainer->box->uriParse),
            UtUriWidget->userinfo);
    gtk_box_append(GTK_BOX(UtGtkContainer->box->uriParse),
            UtUriWidget->host);
    gtk_box_append(GTK_BOX(UtGtkContainer->box->uriParse),
            UtUriWidget->port);
    gtk_box_append(GTK_BOX(UtGtkContainer->box->uriParse),
            UtUriWidget->path);
    gtk_box_append(GTK_BOX(UtGtkContainer->box->uriParse),
            UtUriWidget->query);
    gtk_box_append(GTK_BOX(UtGtkContainer->box->uriParse),
            UtUriWidget->fragment);
    gtk_box_append(GTK_BOX(UtGtkContainer->box->uriBuild),
            UtUriWidget->uri);

    g_signal_connect(UtUriWidget->uri,
            "changed", G_CALLBACK(FvGtkUriParse), UtUriWidget);
    g_signal_connect(UtUriWidget->scheme,
            "changed", G_CALLBACK(FvGtkUriBuild), UtUriWidget);
    g_signal_connect(UtUriWidget->userinfo,
            "changed", G_CALLBACK(FvGtkUriBuild), UtUriWidget);
    g_signal_connect(UtUriWidget->host,
            "changed", G_CALLBACK(FvGtkUriBuild), UtUriWidget);
    g_signal_connect(UtUriWidget->port,
            "value-changed", G_CALLBACK(FvGtkUriBuild), UtUriWidget);
    g_signal_connect(UtUriWidget->path,
            "changed", G_CALLBACK(FvGtkUriBuild), UtUriWidget);
    g_signal_connect(UtUriWidget->query,
            "changed", G_CALLBACK(FvGtkUriBuild), UtUriWidget);
    g_signal_connect(UtUriWidget->fragment,
            "changed", G_CALLBACK(FvGtkUriBuild), UtUriWidget);
}

