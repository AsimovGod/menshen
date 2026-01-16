#include <stdio.h>




_Bool VbUriChange = FALSE;



    char*
FcGtkUriEntryGet(GtkWidget* UgUriEntry)
{
    const char* VcUriParse;

    VcUriParse = gtk_editable_get_text(GTK_EDITABLE(UgUriEntry));
    return VcUriParse && *VcUriParse ? g_strdup(VcUriParse) : g_strdup("");
}


    void
FgGtkUriWidgetSet(GtkWidget* UgUriEntry, char* VcUriEntry)
{
    gtk_editable_set_text(GTK_EDITABLE(UgUriEntry),
            VcUriEntry ? VcUriEntry : "");
}


    void
FvGtkUriBuild(GtkEditable* UgEditable, void* GuUserdata)
{
    const char* VcUriParse;
    int ViUriParsePort;
    char* VcEdittext;
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

    ViUriParsePort = (int)gtk_spin_button_get_value(
            GTK_SPIN_BUTTON(UtGtkUri->spin->port));
    UtGtkUri->parse->port = ViUriParsePort ? ViUriParsePort : -1;

    VcEdittext = FcGuriBuild(UtGtkUri->parse);
    gtk_editable_set_text(GTK_EDITABLE(UtGtkUri->entry->uri),
            VcEdittext ? VcEdittext : "");

    if (VcEdittext) g_free(VcEdittext);

    VbUriChange = FALSE;
}


    void
FvGtkUriParse(GtkEditable* UgEditable, void* GuUserdata)
{
    const char* VcEdittext;
    TgGuriParse* UtUriParse;
    TgGtkUri* UtGtkUri;

    UtGtkUri = GuUserdata;

    if (! UtGtkUri->entry || VbUriChange) return;

    VbUriChange = TRUE;

    VcEdittext = gtk_editable_get_text(UgEditable);
    UtUriParse = FtGuriParse(VcEdittext ? VcEdittext : NULL);
    UtGtkUri->parse = UtUriParse ? UtUriParse : g_new0(TgGuriParse, 1);

    FgGtkUriWidgetSet(UtGtkUri->entry->scheme, UtGtkUri->parse->scheme);
    FgGtkUriWidgetSet(UtGtkUri->entry->userinfo, UtGtkUri->parse->userinfo);
    FgGtkUriWidgetSet(UtGtkUri->entry->host, UtGtkUri->parse->host);
    FgGtkUriWidgetSet(UtGtkUri->entry->path, UtGtkUri->parse->path);
    FgGtkUriWidgetSet(UtGtkUri->entry->query, UtGtkUri->parse->query);
    FgGtkUriWidgetSet(UtGtkUri->entry->fragment, UtGtkUri->parse->fragment);

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(UtGtkUri->spin->port),
            UtGtkUri->parse->port ? UtGtkUri->parse->port : -1);

    VbUriChange = FALSE;
}


    void
FvGtkWidgetClear(GtkEntry* UgUriEntry,
        GtkEntryIconPosition UgUriPos, GdkEvent* UgUriEvent,
        void* GuUriUserdata)
{
    if (UgUriPos == GTK_ENTRY_ICON_SECONDARY) {
        gtk_editable_delete_text(GTK_EDITABLE(UgUriEntry), 0, -1);
    }
}


    GtkWidget*
FgGtkUriWidget(TgGtkUri* UtGtkUri, const char* VcUriType,
        GtkWidget* UgUriParent, int ViUriRow, const char* VcUriLabel)
{
    GtkWidget* UgUriWidget;

    if (strcmp(VcUriType, "buttonPort") == 0) {
        UgUriWidget = gtk_spin_button_new_with_range(-1, 65535, 1);
    }
    else {
        UgUriWidget = gtk_entry_new();

        gtk_entry_set_icon_from_icon_name(GTK_ENTRY(UgUriWidget),
                GTK_ENTRY_ICON_SECONDARY, "edit-clear-symbolic");

        g_signal_connect(UgUriWidget,
                "icon-press", G_CALLBACK(FvGtkWidgetClear), NULL);
    }

    if (strcmp(VcUriType, "buttonPort") == 0) {
        g_signal_connect(UgUriWidget,
                "value-changed", G_CALLBACK(FvGtkUriBuild), UtGtkUri);
    }
    else if (strcmp(VcUriType, "entryBuild") == 0)
    {
        g_signal_connect(UgUriWidget,
                "changed", G_CALLBACK(FvGtkUriParse), UtGtkUri);
    }
    else if (strcmp(VcUriType, "entryParse") == 0)
    {
        g_signal_connect(UgUriWidget,
                "changed", G_CALLBACK(FvGtkUriBuild), UtGtkUri);
    }
    else return NULL;

    gtk_widget_set_hexpand(UgUriWidget, TRUE);
    gtk_widget_set_margin_start(UgUriWidget, 16);
    gtk_widget_set_margin_end(UgUriWidget, 16);

    gtk_grid_attach(GTK_GRID(UgUriParent),
            UgUriWidget, 1, ViUriRow, 2, 1);

    gtk_grid_attach(GTK_GRID(UgUriParent),
            gtk_label_new(VcUriLabel), 0, ViUriRow, 1, 1);

    return UgUriWidget;
}


    void
FvGtkUriWidget(TgGtkLayout* UtGtkLayout, TgGtkUri* UtGtkUri)
{
    UtGtkUri->entry->uri = FgGtkUriWidget(UtGtkUri, "entryBuild",
            UtGtkLayout->grid->uriBuild, 0, "       URI:        ");
    UtGtkUri->entry->scheme = FgGtkUriWidget(UtGtkUri, "entryParse",
            UtGtkLayout->grid->uriParse, 0, "   Scheme:     ");
    UtGtkUri->entry->host = FgGtkUriWidget(UtGtkUri, "entryParse",
            UtGtkLayout->grid->uriParse, 1, "   Host:       ");
    UtGtkUri->entry->userinfo = FgGtkUriWidget(UtGtkUri, "entryParse",
            UtGtkLayout->grid->uriParse, 2, "   Userinfo:   ");
    UtGtkUri->spin->port = FgGtkUriWidget(UtGtkUri, "buttonPort",
            UtGtkLayout->grid->uriParse, 3, "   Port:       ");
    UtGtkUri->entry->path = FgGtkUriWidget(UtGtkUri, "entryParse",
            UtGtkLayout->grid->uriParse, 4, "   Path:       ");
    UtGtkUri->entry->query = FgGtkUriWidget(UtGtkUri, "entryParse",
            UtGtkLayout->grid->uriParse, 5, "   Query:      ");
    UtGtkUri->entry->fragment = FgGtkUriWidget(UtGtkUri, "entryParse",
            UtGtkLayout->grid->uriParse, 6, "   Fragment:   ");
}

