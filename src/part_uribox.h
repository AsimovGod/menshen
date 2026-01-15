#include <stdio.h>
#include <stdlib.h>




    void
FvGtkUriBuild(GtkEditable* UgEditable)
{
    const char* VcUriParse;
    int ViUriParsePort;
    char* VcEdittext;

    if (! UtUriWidget || VbUriChange) return;

    VbUriChange = TRUE;

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->scheme));
    UtUriParse->scheme = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : NULL;

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->userinfo));
    UtUriParse->userinfo = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : NULL;

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->host));
    UtUriParse->host = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : g_strdup("");

    ViUriParsePort = (int)gtk_spin_button_get_value(
            GTK_SPIN_BUTTON(UtUriWidget->port));
    UtUriParse->port = ViUriParsePort ? ViUriParsePort : -1;

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->path));
    UtUriParse->path = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : g_strdup("");

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->query));
    UtUriParse->query = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : NULL;

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->fragment));
    UtUriParse->fragment = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : NULL;

    VcEdittext = FcGuriBuild(UtUriParse);
    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->uri),
            VcEdittext ? VcEdittext : "");

    if (VcEdittext) g_free(VcEdittext);

    VbUriChange = FALSE;
}


    void
FvGtkUriParse(GtkEditable* UgEditable)
{
    const char* VcEdittext;

    if (! UtUriWidget || VbUriChange) return;

    VbUriChange = TRUE;

    VcEdittext = gtk_editable_get_text(UgEditable);
    UtUriParse = FtGuriParse(VcEdittext ? VcEdittext : NULL);

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->scheme),
            UtUriParse && UtUriParse->scheme ? UtUriParse->scheme : "");

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->userinfo),
            UtUriParse && UtUriParse->userinfo ? UtUriParse->userinfo : "");

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->host),
            UtUriParse && UtUriParse->host ? UtUriParse->host : "");

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(UtUriWidget->port),
            UtUriParse && UtUriParse->port ? UtUriParse->port : -1);

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->path),
            UtUriParse && UtUriParse->path ? UtUriParse->path : "");

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->query),
            UtUriParse && UtUriParse->query ? UtUriParse->query : "");

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->fragment),
            UtUriParse && UtUriParse->fragment ? UtUriParse->fragment : "");

    VbUriChange = FALSE;
}

    void
FvGtkUriWidget()
{
    UtUriWidget->scheme = gtk_entry_new();
    UtUriWidget->userinfo = gtk_entry_new();
    UtUriWidget->host = gtk_entry_new();
    UtUriWidget->port = gtk_spin_button_new_with_range(-1, 65535, 1);
    UtUriWidget->path = gtk_entry_new();
    UtUriWidget->query = gtk_entry_new();
    UtUriWidget->fragment = gtk_entry_new();
    UtUriWidget->uri = gtk_entry_new();

    gtk_box_append(GTK_BOX(UtGtkContainer->uriParse), UtUriWidget->scheme);
    gtk_box_append(GTK_BOX(UtGtkContainer->uriParse), UtUriWidget->userinfo);
    gtk_box_append(GTK_BOX(UtGtkContainer->uriParse), UtUriWidget->host);
    gtk_box_append(GTK_BOX(UtGtkContainer->uriParse), UtUriWidget->port);
    gtk_box_append(GTK_BOX(UtGtkContainer->uriParse), UtUriWidget->path);
    gtk_box_append(GTK_BOX(UtGtkContainer->uriParse), UtUriWidget->query);
    gtk_box_append(GTK_BOX(UtGtkContainer->uriParse), UtUriWidget->fragment);
    gtk_box_append(GTK_BOX(UtGtkContainer->uriBuild), UtUriWidget->uri);

    gtk_editable_set_width_chars(GTK_EDITABLE(UtUriWidget->scheme), 128);
    gtk_editable_set_width_chars(GTK_EDITABLE(UtUriWidget->userinfo), 128);
    gtk_editable_set_width_chars(GTK_EDITABLE(UtUriWidget->host), 128);
    gtk_editable_set_width_chars(GTK_EDITABLE(UtUriWidget->port), 128);
    gtk_editable_set_width_chars(GTK_EDITABLE(UtUriWidget->path), 128);
    gtk_editable_set_width_chars(GTK_EDITABLE(UtUriWidget->query), 128);
    gtk_editable_set_width_chars(GTK_EDITABLE(UtUriWidget->fragment), 128);
    gtk_editable_set_width_chars(GTK_EDITABLE(UtUriWidget->uri), 128);

    g_signal_connect(UtUriWidget->uri,
            "changed", G_CALLBACK(FvGtkUriParse), NULL);
    g_signal_connect(UtUriWidget->scheme,
            "changed", G_CALLBACK(FvGtkUriBuild), NULL);
    g_signal_connect(UtUriWidget->userinfo,
            "changed", G_CALLBACK(FvGtkUriBuild), NULL);
    g_signal_connect(UtUriWidget->host,
            "changed", G_CALLBACK(FvGtkUriBuild), NULL);
    g_signal_connect(UtUriWidget->port,
            "value-changed", G_CALLBACK(FvGtkUriBuild), NULL);
    g_signal_connect(UtUriWidget->path,
            "changed", G_CALLBACK(FvGtkUriBuild), NULL);
    g_signal_connect(UtUriWidget->query,
            "changed", G_CALLBACK(FvGtkUriBuild), NULL);
    g_signal_connect(UtUriWidget->fragment,
            "changed", G_CALLBACK(FvGtkUriBuild), NULL);
}


    void
FvGtkUri(char* VcGtkUri)
{
    UtGtkContainer->uriBuild = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    UtGtkContainer->uriParse = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_paned_set_start_child(GTK_PANED(UtGtkContainer->mainUp),
            UtGtkContainer->uriBuild);
    gtk_paned_set_start_child(GTK_PANED(UtGtkContainer->mainDown),
            UtGtkContainer->uriParse);

    FvGtkUriWidget();

    UtUriParse = FtGuriParse(VcGtkUri ? VcGtkUri : "");
    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->uri), UtUriParse->uri);
    FvGtkUriParse(GTK_EDITABLE(UtUriWidget->uri));
}

