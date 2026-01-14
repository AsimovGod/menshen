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


_Bool VbUriChange = FALSE;

TgGuriParse* UtUriParse;
TgGuriWidget* UtUriWidget;


    void
FvGtkUriParseSet(char* UvUriParse,
        GtkWidget* UgGtkWidgetEntry,
        char* VcUriEmpty)
{
    gtk_editable_set_text(GTK_EDITABLE(UgGtkWidgetEntry),
            UtUriParse && UvUriParse ? UvUriParse : VcUriEmpty);
}


    void
FvGtkUriParseGet(char** UvUriParse,
        GtkWidget* UgUriWidgetEntry,
        char* VcUriEmpty)
{
    const char* VcUriParse;

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UgUriWidgetEntry));
    *UvUriParse = VcUriParse && *VcUriParse
        ? g_strdup(VcUriParse) : g_strdup(VcUriEmpty);
}


    void
FvGtkUriParse(GtkEditable* UgEditable)
{
    const char* VcUriParse;
    char* VcEdittext;
    int ViUriParsePort;

    if (! UtUriWidget || VbUriChange) return;

    VbUriChange = TRUE;

    if (UgEditable == GTK_EDITABLE(UtUriWidget->uri)) {
        VcUriParse = gtk_editable_get_text(UgEditable);
        UtUriParse = FtGuriParse(VcUriParse ? VcUriParse : "");

        FvGtkUriParseSet(UtUriParse->scheme, UtUriWidget->scheme, "");
        FvGtkUriParseSet(UtUriParse->userinfo, UtUriWidget->userinfo, "");
        FvGtkUriParseSet(UtUriParse->host, UtUriWidget->host, "");
        FvGtkUriParseSet(UtUriParse->path, UtUriWidget->path, "");
        FvGtkUriParseSet(UtUriParse->query, UtUriWidget->query, "");
        FvGtkUriParseSet(UtUriParse->fragment, UtUriWidget->fragment, "");

        gtk_spin_button_set_value(GTK_SPIN_BUTTON(UtUriWidget->port),
                UtUriParse && UtUriParse->port ? UtUriParse->port : -1);
    }
    else {
        UtUriParse = g_new0(TgGuriParse, 1);

        FvGtkUriParseGet(&UtUriParse->scheme, UtUriWidget->scheme, "");
        FvGtkUriParseGet(&UtUriParse->userinfo, UtUriWidget->userinfo, "");
        FvGtkUriParseGet(&UtUriParse->host, UtUriWidget->host, "");
        FvGtkUriParseGet(&UtUriParse->path, UtUriWidget->path, "");
        FvGtkUriParseGet(&UtUriParse->query, UtUriWidget->query, "");
        FvGtkUriParseGet(&UtUriParse->fragment, UtUriWidget->fragment, "");

        ViUriParsePort = (int)gtk_spin_button_get_value(
                GTK_SPIN_BUTTON(UtUriWidget->port));
        UtUriParse->port = ViUriParsePort ? ViUriParsePort : -1;

        VcEdittext = FcGuriBuild(UtUriParse);
        gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->uri),
                VcEdittext ? VcEdittext : "");

        if (VcEdittext) g_free(VcEdittext);
    }

    if (UtUriParse) FvGuriFree(UtUriParse);

    VbUriChange = FALSE;
}


    void
FvGtkUriWidgetEntry(GtkWidget** UgWidgetEntry, GtkWidget* UgWidgetParent)
{
    *UgWidgetEntry = gtk_entry_new();
    gtk_box_append(GTK_BOX(UgWidgetParent), *UgWidgetEntry);
    gtk_editable_set_width_chars(GTK_EDITABLE(*UgWidgetEntry), 64);
    g_signal_connect(*UgWidgetEntry, "changed",
            G_CALLBACK(FvGtkUriParse), NULL);
}

    void
FvGtkUri(GtkWidget* UgPanedMainUp, GtkWidget* UgPanedMainDown, char* VcGtkUri)
{
    GtkWidget* UgScrollUriBuild;
    GtkWidget* UgScrollUriParse;
    GtkWidget* UgBoxUriBuild;
    GtkWidget* UgBoxUriParse;

    UgScrollUriBuild = gtk_scrolled_window_new();
    UgScrollUriParse = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(UgScrollUriBuild),
            GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(UgScrollUriParse),
            GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_paned_set_start_child(GTK_PANED(UgPanedMainUp), UgScrollUriBuild);
    gtk_paned_set_start_child(GTK_PANED(UgPanedMainDown), UgScrollUriParse);

    UgBoxUriBuild = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    UgBoxUriParse = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(UgScrollUriBuild),
            UgBoxUriBuild);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(UgScrollUriParse),
            UgBoxUriParse);

    UtUriWidget = g_new0(TgGuriWidget, 1);

    FvGtkUriWidgetEntry(&UtUriWidget->uri, UgScrollUriBuild);
    FvGtkUriWidgetEntry(&UtUriWidget->scheme, UgScrollUriBuild);
    FvGtkUriWidgetEntry(&UtUriWidget->userinfo, UgScrollUriBuild);
    FvGtkUriWidgetEntry(&UtUriWidget->host, UgScrollUriBuild);
    FvGtkUriWidgetEntry(&UtUriWidget->path, UgScrollUriBuild);
    FvGtkUriWidgetEntry(&UtUriWidget->query, UgScrollUriBuild);
    FvGtkUriWidgetEntry(&UtUriWidget->fragment, UgScrollUriBuild);

    UtUriWidget->port = gtk_spin_button_new_with_range(-1, 65535, 1);
    gtk_box_append(GTK_BOX(UgBoxUriParse), UtUriWidget->port);
    gtk_editable_set_width_chars(GTK_EDITABLE(UtUriWidget->port), 64);
    g_signal_connect(UtUriWidget->port,
            "value-changed", G_CALLBACK(FvGtkUriParse), NULL);

    UtUriParse = FtGuriParse(VcGtkUri ? VcGtkUri : "");
    gtk_editable_set_text(GTK_EDITABLE(UtUriWidget->uri), UtUriParse->uri);
    FvGtkUriParse(GTK_EDITABLE(UtUriWidget->uri));

    FvGuriFree(UtUriParse);
}

