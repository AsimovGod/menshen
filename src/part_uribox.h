#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>




typedef struct {
    GtkWidget* uri;
    GtkWidget* scheme;
    GtkWidget* userinfo;
    GtkWidget* host;
    GtkWidget* port;
    GtkWidget* path;
    GtkWidget* query;
    GtkWidget* fragment;
} TgGuriWidget;


gboolean VbUriBoolean = FALSE;


    void
FvGtkUriBuild(GtkEditable* UgEditable, gpointer GuUserdata)
{
    const gchar* VcUriParse;
    gint ViUriParsePort;
    gchar* VcEdittext;
    TgGuriWidget* UtUriWidget;
    TgGuriParse* UtUriBuild;

    UtUriWidget = GuUserdata;

    if (! UtUriWidget || VbUriBoolean) return;

    VbUriBoolean = TRUE;

    UtUriBuild = g_new0(TgGuriParse, 1);

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->scheme));
    UtUriBuild->scheme = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : NULL;

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->userinfo));
    UtUriBuild->userinfo = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : NULL;

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->host));
    UtUriBuild->host = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : g_strdup("");

    ViUriParsePort = (gint)gtk_spin_button_get_value(
            GTK_SPIN_BUTTON(UtUriWidget->port));
    UtUriBuild->port = ViUriParsePort ? ViUriParsePort : -1;

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->path));
    UtUriBuild->path = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : g_strdup("");

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->query));
    UtUriBuild->query = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : NULL;

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->fragment));
    UtUriBuild->fragment = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : NULL;

    VcEdittext = FcGuriBuild(UtUriBuild);
    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->uri),
            VcEdittext ? VcEdittext : "");

    FvGuriFree(UtUriBuild);

    if (VcEdittext) g_free(VcEdittext);

    VbUriBoolean = FALSE;
}


    void
FvGtkUriParse(GtkEditable* UgEditable, gpointer GuUserdata)
{
    const gchar* VcEdittext;
    TgGuriWidget* UtUriWidget;
    TgGuriParse* UtUriParse;

    UtUriWidget = GuUserdata;

    if (! UtUriWidget || VbUriBoolean) return;

    VbUriBoolean = TRUE;

    VcEdittext = gtk_editable_get_text(UgEditable);
    UtUriParse = FtGuriParse(VcEdittext ? VcEdittext : NULL);

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->scheme),
            UtUriParse && UtUriParse->scheme ? UtUriParse->scheme : "");

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->userinfo),
            UtUriParse && UtUriParse->userinfo ? UtUriParse->userinfo : "");

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->host),
            UtUriParse && UtUriParse->host ? UtUriParse->host : "");

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(UtUriWidget->port),
            UtUriParse->port ? UtUriParse->port : -1);

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->path),
            UtUriParse && UtUriParse->path ? UtUriParse->path : "");

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->query),
            UtUriParse && UtUriParse->query ? UtUriParse->query : "");

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->fragment),
            UtUriParse && UtUriParse->fragment ? UtUriParse->fragment : "");

    FvGuriFree(UtUriParse);

    VbUriBoolean = FALSE;
}


    void
FvGtkUri(GtkWidget* UgBoxMainUp, GtkWidget* UgBoxMainDown, char* VcGtkUri)
{
    GtkWidget* UgBoxUriBuild;
    GtkWidget* UgBoxUriParse;
    TgGuriParse* UtUriParse;
    TgGuriWidget* UtUriWidget;

    UgBoxUriBuild = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    UgBoxUriParse = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_box_append(GTK_BOX(UgBoxMainUp), UgBoxUriBuild);
    gtk_box_append(GTK_BOX(UgBoxMainDown), UgBoxUriParse);

    UtUriWidget = g_new0(TgGuriWidget, 1);
    UtUriWidget->scheme = gtk_entry_new();
    UtUriWidget->userinfo = gtk_entry_new();
    UtUriWidget->host = gtk_entry_new();
    UtUriWidget->port = gtk_spin_button_new_with_range(-1, 65535, 1);
    UtUriWidget->path = gtk_entry_new();
    UtUriWidget->query = gtk_entry_new();
    UtUriWidget->fragment = gtk_entry_new();
    UtUriWidget->uri = gtk_entry_new();

    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriWidget->scheme);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriWidget->userinfo);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriWidget->host);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriWidget->port);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriWidget->path);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriWidget->query);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriWidget->fragment);
    gtk_box_append(GTK_BOX(UgBoxUriBuild), UtUriWidget->uri);

    gtk_editable_set_width_chars(GTK_EDITABLE(UtUriWidget->scheme), 128);
    gtk_editable_set_width_chars(GTK_EDITABLE(UtUriWidget->userinfo), 128);
    gtk_editable_set_width_chars(GTK_EDITABLE(UtUriWidget->host), 128);
    gtk_editable_set_width_chars(GTK_EDITABLE(UtUriWidget->port), 128);
    gtk_editable_set_width_chars(GTK_EDITABLE(UtUriWidget->path), 128);
    gtk_editable_set_width_chars(GTK_EDITABLE(UtUriWidget->query), 128);
    gtk_editable_set_width_chars(GTK_EDITABLE(UtUriWidget->fragment), 128);
    gtk_editable_set_width_chars(GTK_EDITABLE(UtUriWidget->uri), 128);

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

    UtUriParse = FtGuriParse(VcGtkUri ? VcGtkUri : "");
    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->uri), UtUriParse->uri);
    FvGtkUriParse(GTK_EDITABLE(UtUriWidget->uri), UtUriWidget);

    FvGuriFree(UtUriParse);
}

