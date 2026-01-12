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



    void
FvGtkUpdatingSet(GtkWidget* UgUriEntry, gboolean UbGetBoolean)
{
    g_object_set_data(G_OBJECT(UgUriEntry),
            "updating", GINT_TO_POINTER(UbGetBoolean));
}


    gboolean
FbUpdatingGet(GtkWidget* UgUriEntry)
{
    gboolean VbReturn;
    gpointer UpObjectGet;

    UpObjectGet = g_object_get_data(G_OBJECT(UgUriEntry), "updating");
    VbReturn = UpObjectGet ? GPOINTER_TO_INT(UpObjectGet) : FALSE;

    return VbReturn;
}


    void
FvGtkChangedParse(GtkEditable* UgEditable, gpointer GuUserdata)
{
    const gchar* VcEdittext;

    TgGuriWidget* UtUriEntry;
    TgGuriParse* UtUriParse;

    UtUriEntry = GuUserdata;
    UtUriParse = NULL;

    if (!UtUriEntry || FbUpdatingGet(UtUriEntry->uri)) return;

    VcEdittext = gtk_editable_get_text(UgEditable);
    UtUriParse = FtGuriParse(VcEdittext);

    g_object_set_data_full(G_OBJECT(UtUriEntry->uri),
            "parsed", UtUriParse, FvGuriFree);

    FvGtkUpdatingSet(UtUriEntry->uri, TRUE);

    gtk_editable_set_text(GTK_EDITABLE(UtUriEntry->scheme),
            UtUriParse && UtUriParse->scheme
            ? UtUriParse->scheme : g_strdup(""));

    gtk_editable_set_text(GTK_EDITABLE(UtUriEntry->host),
            UtUriParse && UtUriParse->host
            ? UtUriParse->host : g_strdup(""));

    gtk_editable_set_text(GTK_EDITABLE(UtUriEntry->port), g_strdup(""));

    gtk_editable_set_text(GTK_EDITABLE(UtUriEntry->path),
            UtUriParse && UtUriParse->path
            ? UtUriParse->path : g_strdup(""));

    gtk_editable_set_text(GTK_EDITABLE(UtUriEntry->query),
            UtUriParse && UtUriParse->query
            ? UtUriParse->query : NULL);

    gtk_editable_set_text(GTK_EDITABLE(UtUriEntry->fragment),
            UtUriParse && UtUriParse->fragment
            ? UtUriParse->fragment : NULL);

    FvGtkUpdatingSet(UtUriEntry->uri, FALSE);
}


    void
FvGtkChangedBuild(GtkEditable* UgEditable, gpointer GuUserdata)
{
    const gchar* VcUriParse;
    gchar* VcEdittext;

    TgGuriWidget* UtUriEntry;
    TgGuriParse* UtUriBuild;

    UtUriEntry = GuUserdata;

    if (!UtUriEntry || FbUpdatingGet(UtUriEntry->uri)) return;

    UtUriBuild = g_new0(TgGuriParse, 1);

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriEntry->scheme));
    UtUriBuild->scheme = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : g_strdup("");

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriEntry->host));
    UtUriBuild->host = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : g_strdup("");

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriEntry->path));
    UtUriBuild->path = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : g_strdup("");

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriEntry->query));
    UtUriBuild->query = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : NULL;

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UtUriEntry->fragment));
    UtUriBuild->fragment = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : NULL;

    VcEdittext = FcGuriBuild(UtUriBuild);

    if (VcEdittext) {
        g_object_set_data_full(G_OBJECT(UtUriEntry->uri),
                "parsed", UtUriBuild, FvGuriFree);
    }
    else {
        FvGuriFree(UtUriBuild);
    }

    UtUriBuild = NULL;

    FvGtkUpdatingSet(UtUriEntry->uri, TRUE);
    gtk_editable_set_text(GTK_EDITABLE(UtUriEntry->uri),
            VcEdittext ? VcEdittext : NULL);
    FvGtkUpdatingSet(UtUriEntry->uri, FALSE);

    g_free(VcEdittext);
}


    void
FvGtkUri(GtkWidget* UgBoxMainUp, GtkWidget* UgBoxMainDown, char* VcGtkUri)
{
    GtkWidget* UgBoxUriBuild;
    GtkWidget* UgBoxUriParse;
    TgGuriParse* UtUriParse;
    TgGuriWidget* UtUriEntry;

    UtUriEntry = g_new0(TgGuriWidget, 1);

    UgBoxUriBuild = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_box_append(GTK_BOX(UgBoxMainUp), UgBoxUriBuild);

    UtUriEntry->uri = gtk_entry_new();
    gtk_editable_set_text(GTK_EDITABLE(UtUriEntry->uri), VcGtkUri);
    gtk_editable_set_width_chars(GTK_EDITABLE(UtUriEntry->uri),
            strlen(VcGtkUri));
    gtk_box_append(GTK_BOX(UgBoxUriBuild), UtUriEntry->uri);

    UgBoxUriParse = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_box_append(GTK_BOX(UgBoxMainDown), UgBoxUriParse);

    UtUriEntry->scheme = gtk_entry_new();
    UtUriEntry->host = gtk_entry_new();
    UtUriEntry->port = gtk_entry_new();
    UtUriEntry->path = gtk_entry_new();
    UtUriEntry->query = gtk_entry_new();
    UtUriEntry->fragment = gtk_entry_new();

    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriEntry->scheme);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriEntry->host);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriEntry->port);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriEntry->path);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriEntry->query);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriEntry->fragment);

    UtUriParse = FtGuriParse(gtk_editable_get_text(
                GTK_EDITABLE(UtUriEntry->uri)));

    g_object_set_data_full(G_OBJECT(UtUriEntry->uri),
            "parsed", UtUriParse, FvGuriFree);

    FvGtkUpdatingSet(UtUriEntry->uri, FALSE);

    g_signal_connect(UtUriEntry->uri,
            "changed", G_CALLBACK(FvGtkChangedParse), UtUriEntry);

    g_signal_connect(UtUriEntry->scheme,
            "changed", G_CALLBACK(FvGtkChangedBuild), UtUriEntry);
    g_signal_connect(UtUriEntry->host,
            "changed", G_CALLBACK(FvGtkChangedBuild), UtUriEntry);
    g_signal_connect(UtUriEntry->port,
            "changed", G_CALLBACK(FvGtkChangedBuild), UtUriEntry);
    g_signal_connect(UtUriEntry->path,
            "changed", G_CALLBACK(FvGtkChangedBuild), UtUriEntry);
    g_signal_connect(UtUriEntry->query,
            "changed", G_CALLBACK(FvGtkChangedBuild), UtUriEntry);
    g_signal_connect(UtUriEntry->fragment,
            "changed", G_CALLBACK(FvGtkChangedBuild), UtUriEntry);

    FvGtkChangedParse(GTK_EDITABLE(UtUriEntry->uri), UtUriEntry);
}

