#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>




typedef struct {
    GtkWidget* string;
    GtkWidget* scheme;
    GtkWidget* host;
    GtkWidget* port;
    GtkWidget* path;
    GtkWidget* query;
    GtkWidget* fragment;
    GtkWidget* uri;
} TgGuriWidget;



void FvGtkUriBuild(GtkEditable* UgEditable, gpointer GuUserdata);
void FvGtkUriParse(GtkEditable* UgEditable, gpointer GuUserdata);


    void
FvGtkUriBoolean(TgGuriWidget* UtUriWidget, gboolean UbChangeBoolean)
{
    if (UbChangeBoolean) {
        gtk_widget_set_sensitive(UtUriWidget->string, TRUE);
        gtk_widget_set_sensitive(UtUriWidget->scheme, TRUE);
        gtk_widget_set_sensitive(UtUriWidget->host, TRUE);
        gtk_widget_set_sensitive(UtUriWidget->port, TRUE);
        gtk_widget_set_sensitive(UtUriWidget->path, TRUE);
        gtk_widget_set_sensitive(UtUriWidget->query, TRUE);
        gtk_widget_set_sensitive(UtUriWidget->fragment, TRUE);
        gtk_widget_set_sensitive(UtUriWidget->uri, TRUE);

        g_signal_handlers_unblock_by_func(UtUriWidget->scheme,
                G_CALLBACK(FvGtkUriBuild), UtUriWidget);
        g_signal_handlers_unblock_by_func(UtUriWidget->host,
                G_CALLBACK(FvGtkUriBuild), UtUriWidget);
        g_signal_handlers_unblock_by_func(UtUriWidget->port,
                G_CALLBACK(FvGtkUriBuild), UtUriWidget);
        g_signal_handlers_unblock_by_func(UtUriWidget->path,
                G_CALLBACK(FvGtkUriBuild), UtUriWidget);
        g_signal_handlers_unblock_by_func(UtUriWidget->query,
                G_CALLBACK(FvGtkUriBuild), UtUriWidget);
        g_signal_handlers_unblock_by_func(UtUriWidget->fragment,
                G_CALLBACK(FvGtkUriBuild), UtUriWidget);
        g_signal_handlers_unblock_by_func(UtUriWidget->uri,
                G_CALLBACK(FvGtkUriParse), UtUriWidget);
    }
    else {
        gtk_widget_set_sensitive(UtUriWidget->string, FALSE);
        gtk_widget_set_sensitive(UtUriWidget->scheme, FALSE);
        gtk_widget_set_sensitive(UtUriWidget->host, FALSE);
        gtk_widget_set_sensitive(UtUriWidget->port, FALSE);
        gtk_widget_set_sensitive(UtUriWidget->path, FALSE);
        gtk_widget_set_sensitive(UtUriWidget->query, FALSE);
        gtk_widget_set_sensitive(UtUriWidget->fragment, FALSE);
        gtk_widget_set_sensitive(UtUriWidget->uri, FALSE);

        g_signal_handlers_block_by_func(UtUriWidget->scheme,
                G_CALLBACK(FvGtkUriBuild), UtUriWidget);
        g_signal_handlers_block_by_func(UtUriWidget->host,
                G_CALLBACK(FvGtkUriBuild), UtUriWidget);
        g_signal_handlers_block_by_func(UtUriWidget->port,
                G_CALLBACK(FvGtkUriBuild), UtUriWidget);
        g_signal_handlers_block_by_func(UtUriWidget->path,
                G_CALLBACK(FvGtkUriBuild), UtUriWidget);
        g_signal_handlers_block_by_func(UtUriWidget->query,
                G_CALLBACK(FvGtkUriBuild), UtUriWidget);
        g_signal_handlers_block_by_func(UtUriWidget->fragment,
                G_CALLBACK(FvGtkUriBuild), UtUriWidget);
        g_signal_handlers_block_by_func(UtUriWidget->uri,
                G_CALLBACK(FvGtkUriParse), UtUriWidget);
    }
}


    void
FvGtkUriChange(TgGuriWidget* UtUriWidget,TgGuriParse* UtUriParse)
{
    if (!UtUriWidget) return;

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->uri),
            UtUriParse && UtUriParse->uri
            ? UtUriParse->uri : g_strdup(""));

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->scheme),
            UtUriParse && UtUriParse->scheme
            ? UtUriParse->scheme : g_strdup(""));

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->host),
            UtUriParse && UtUriParse->host
            ? UtUriParse->host : g_strdup(""));

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->port),
            g_strdup(""));

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->path),
            UtUriParse && UtUriParse->path
            ? UtUriParse->path : g_strdup(""));

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->query),
            UtUriParse && UtUriParse->query
            ? UtUriParse->query : NULL);

    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->fragment),
            UtUriParse && UtUriParse->fragment
            ? UtUriParse->fragment : NULL);
}


    void
FvGtkUriParse(GtkEditable* UgEditable, gpointer GuUserdata)
{
    const gchar* VcUriParse;

    TgGuriWidget* UtUriWidget;
    TgGuriParse* UtUriParse;

    UtUriWidget = GuUserdata;

    if (!UtUriWidget) return;

    FvGtkUriBoolean(UtUriWidget, FALSE);

    VcUriParse = gtk_editable_get_text(UgEditable);
    UtUriParse = FtGuriParse(VcUriParse ? VcUriParse : g_strdup(""));

    FvGtkUriChange(UtUriWidget, UtUriParse);

    FvGtkUriBoolean(UtUriWidget, TRUE);
}


    void
FvGtkUriBuild(GtkEditable* UgEditable, gpointer GuUserdata)
{
    const gchar* VcUriParse;

    TgGuriWidget* UtUriWidget;
    TgGuriParse* UtUriBuild;

    UtUriWidget = GuUserdata;

    if (!UtUriWidget) return;

    FvGtkUriBoolean(UtUriWidget, FALSE);

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

    VcUriParse = FcGuriBuild(UtUriBuild);
    UtUriBuild->uri = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : g_strdup("");

    FvGtkUriChange(UtUriWidget, UtUriBuild);

    FvGtkUriBoolean(UtUriWidget, TRUE);
}


    void
FvGtkUri(GtkWidget* UgBoxMainUp, GtkWidget* UgBoxMainDown, char* VcGtkUri)
{
    GtkWidget* UgBoxUriBuild;
    GtkWidget* UgBoxUriParse;
    TgGuriParse* UtUriParse;
    TgGuriWidget* UtUriWidget;

    UtUriWidget = g_new0(TgGuriWidget, 1);

    UgBoxUriBuild = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_box_append(GTK_BOX(UgBoxMainUp), UgBoxUriBuild);

    UtUriWidget->uri = gtk_entry_new();
    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->uri), VcGtkUri);
    gtk_editable_set_width_chars(GTK_EDITABLE(UtUriWidget->uri),
            strlen(VcGtkUri));
    gtk_box_append(GTK_BOX(UgBoxUriBuild), UtUriWidget->uri);

    UgBoxUriParse = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_box_append(GTK_BOX(UgBoxMainDown), UgBoxUriParse);

    UtUriWidget->scheme = gtk_entry_new();
    UtUriWidget->host = gtk_entry_new();
    UtUriWidget->port = gtk_entry_new();
    UtUriWidget->path = gtk_entry_new();
    UtUriWidget->query = gtk_entry_new();
    UtUriWidget->fragment = gtk_entry_new();

    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriWidget->scheme);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriWidget->host);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriWidget->port);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriWidget->path);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriWidget->query);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriWidget->fragment);

    UtUriParse = FtGuriParse(gtk_editable_get_text(
                GTK_EDITABLE(UtUriWidget->uri)));

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

    FvGtkUriParse(GTK_EDITABLE(UtUriWidget->uri), UtUriWidget);
}

