#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>




typedef struct {
    GtkWidget* uri;
    GtkWidget* scheme;
    GtkWidget* host;
    GtkWidget* port;
    GtkWidget* path;
    GtkWidget* query;
    GtkWidget* fragment;
} TgGuriWidget;



    gboolean
GbGtkUriGet(GtkWidget* UgUriWidget)
{
    gpointer UpObjectGet;

    UpObjectGet = g_object_get_data(G_OBJECT(UgUriWidget), "updating");

    return UpObjectGet ? GPOINTER_TO_INT(UpObjectGet) : FALSE;
}


    void
FvGtkUriSet(GtkWidget* UgUriWidget, gboolean UbUriBoolean)
{
    g_object_set_data(G_OBJECT(UgUriWidget),
            "updating", GINT_TO_POINTER(UbUriBoolean));
}


    void
FvGtkUriFree(GtkWidget* UgUriWidget, TgGuriParse* UtUriParse)
{
    g_object_set_data_full(G_OBJECT(UgUriWidget),
            "parsed", UtUriParse, FvGuriFree);
}


    void
FvGtkUriParse(GtkEditable* UgEditable, gpointer GuUserdata)
{
    const gchar* VcEdittext;
    TgGuriWidget* UtUriWidget;
    TgGuriParse* UtUriParse;


    UtUriWidget = GuUserdata;

    if (! UtUriWidget || GbGtkUriGet(UtUriWidget->uri)) return;

    VcEdittext = gtk_editable_get_text(UgEditable);
    UtUriParse = FtGuriParse(VcEdittext ? VcEdittext : NULL);

    FvGtkUriFree(UtUriWidget->uri, UtUriParse);
    FvGtkUriSet(UtUriWidget->uri, TRUE);

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->scheme),
            UtUriParse && UtUriParse->scheme
            ? UtUriParse->scheme : g_strdup(""));

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->host),
            UtUriParse && UtUriParse->host
            ? UtUriParse->host : g_strdup(""));

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->port), g_strdup(""));

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->path),
            UtUriParse && UtUriParse->path
            ? UtUriParse->path : g_strdup(""));

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->query),
            UtUriParse && UtUriParse->query
            ? UtUriParse->query : g_strdup(""));

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->fragment),
            UtUriParse && UtUriParse->fragment
            ? UtUriParse->fragment : g_strdup(""));

    FvGtkUriSet(UtUriWidget->uri, FALSE);
}


    void
FvGtkUriBuild(GtkEditable* UgEditable, gpointer GuUserdata)
{
    const gchar* VcUriParse;
    gchar* VcEdittext;
    TgGuriWidget* UtUriWidget;
    TgGuriParse* UtUriBuild;

    UtUriWidget = GuUserdata;

    if (! UtUriWidget || GbGtkUriGet(UtUriWidget->uri)) return;

    UtUriBuild = g_new0(TgGuriParse, 1);

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->scheme));
    UtUriBuild->scheme = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : g_strdup("");

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->host));
    UtUriBuild->host = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : g_strdup("");

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->path));
    UtUriBuild->path = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : g_strdup("");

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->query));
    UtUriBuild->query = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : NULL;

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriWidget->fragment));
    UtUriBuild->fragment = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : NULL;

    FvGtkUriFree(UtUriWidget->uri, UtUriBuild);
    FvGtkUriSet(UtUriWidget->uri, TRUE);

    VcEdittext = FcGuriBuild(UtUriBuild);
    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->uri),
            VcEdittext ? VcEdittext : NULL);

    FvGtkUriSet(UtUriWidget->uri, FALSE);

    g_free(VcEdittext);
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
    UtUriWidget->host = gtk_entry_new();
    UtUriWidget->port = gtk_entry_new();
    UtUriWidget->path = gtk_entry_new();
    UtUriWidget->query = gtk_entry_new();
    UtUriWidget->fragment = gtk_entry_new();
    UtUriWidget->uri = gtk_entry_new();

    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriWidget->scheme);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriWidget->host);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriWidget->port);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriWidget->path);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriWidget->query);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriWidget->fragment);
    gtk_box_append(GTK_BOX(UgBoxUriBuild), UtUriWidget->uri);

    gtk_editable_set_width_chars(GTK_EDITABLE(UtUriWidget->scheme), 128);
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
    g_signal_connect(UtUriWidget->host,
            "changed", G_CALLBACK(FvGtkUriBuild), UtUriWidget);
    g_signal_connect(UtUriWidget->port,
            "changed", G_CALLBACK(FvGtkUriBuild), UtUriWidget);
    g_signal_connect(UtUriWidget->path,
            "changed", G_CALLBACK(FvGtkUriBuild), UtUriWidget);
    g_signal_connect(UtUriWidget->query,
            "changed", G_CALLBACK(FvGtkUriBuild), UtUriWidget);
    g_signal_connect(UtUriWidget->fragment,
            "changed", G_CALLBACK(FvGtkUriBuild), UtUriWidget);

    UtUriParse = FtGuriParse(VcGtkUri ? VcGtkUri : "");
    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->uri), UtUriParse->uri);

    FvGtkUriFree(UtUriWidget->uri, UtUriParse);
    FvGtkUriSet(UtUriWidget->uri, FALSE);

    FvGtkUriParse(GTK_EDITABLE(UtUriWidget->uri), UtUriWidget);
}

