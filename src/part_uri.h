#include <stdio.h>




    void
FvGtkUriWidget(TgGtkLayout* UtGtkLayout, TgGtkUri* UtGtkUri)
{
    UtGtkUri->entry->uri = FgGtkUriEntry(UtGtkUri, "entryBuild",
            UtGtkLayout->grid->uriBuild, 0, "       URI:        ");
    UtGtkUri->entry->scheme = FgGtkUriEntry(UtGtkUri, "entryParse",
            UtGtkLayout->grid->uriParse, 0, "   Scheme:     ");
    UtGtkUri->entry->host = FgGtkUriEntry(UtGtkUri, "entryParse",
            UtGtkLayout->grid->uriParse, 1, "   Host:       ");
    UtGtkUri->entry->userinfo = FgGtkUriEntry(UtGtkUri, "entryParse",
            UtGtkLayout->grid->uriParse, 2, "   Userinfo:   ");
    UtGtkUri->spin->port = FgGtkUriEntry(UtGtkUri, "buttonPort",
            UtGtkLayout->grid->uriParse, 3, "   Port:       ");
    UtGtkUri->entry->path = FgGtkUriEntry(UtGtkUri, "entryParse",
            UtGtkLayout->grid->uriParse, 4, "   Path:       ");
    UtGtkUri->entry->query = FgGtkUriEntry(UtGtkUri, "entryParse",
            UtGtkLayout->grid->uriParse, 5, "   Query:      ");
    UtGtkUri->entry->fragment = FgGtkUriEntry(UtGtkUri, "entryParse",
            UtGtkLayout->grid->uriParse, 6, "   Fragment:   ");
}


    void
FvGtkUri(TgGtkLayout* UtGtkLayout, char* VcGtkUri)
{
    TgGtkUri* UtGtkUri;

    UtGtkLayout->scroll->uriBuild = gtk_scrolled_window_new();
    UtGtkLayout->scroll->uriParse = gtk_scrolled_window_new();

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                UtGtkLayout->scroll->uriBuild),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                UtGtkLayout->scroll->uriParse),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_paned_set_start_child(GTK_PANED(UtGtkLayout->paned->mainLeft),
            UtGtkLayout->scroll->uriBuild);
    gtk_paned_set_end_child(GTK_PANED(UtGtkLayout->paned->mainLeft),
            UtGtkLayout->scroll->uriParse);

    UtGtkLayout->grid->uriBuild = gtk_grid_new();
    UtGtkLayout->grid->uriParse = gtk_grid_new();

    gtk_grid_set_row_spacing(GTK_GRID(UtGtkLayout->grid->uriBuild), 4);
    gtk_grid_set_column_spacing(GTK_GRID(UtGtkLayout->grid->uriBuild), 4);
    gtk_grid_set_row_spacing(GTK_GRID(UtGtkLayout->grid->uriParse), 4);
    gtk_grid_set_column_spacing(GTK_GRID(UtGtkLayout->grid->uriParse), 4);

    gtk_widget_set_vexpand(UtGtkLayout->grid->uriBuild, TRUE);
    gtk_widget_set_hexpand(UtGtkLayout->grid->uriBuild, TRUE);
    gtk_widget_set_vexpand(UtGtkLayout->grid->uriParse, TRUE);
    gtk_widget_set_hexpand(UtGtkLayout->grid->uriParse, TRUE);

    gtk_widget_set_valign(UtGtkLayout->grid->uriBuild, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(UtGtkLayout->grid->uriBuild, GTK_ALIGN_FILL);
    gtk_widget_set_valign(UtGtkLayout->grid->uriParse, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(UtGtkLayout->grid->uriParse, GTK_ALIGN_FILL);

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                UtGtkLayout->scroll->uriBuild), UtGtkLayout->grid->uriBuild);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                UtGtkLayout->scroll->uriParse), UtGtkLayout->grid->uriParse);

    UtGtkUri = g_new0(TgGtkUri, 1);
    UtGtkUri->entry = g_new0(TgGtkUriEntry, 1);
    UtGtkUri->spin = g_new0(TgGtkUriSpin, 1);
    UtGtkUri->parse = g_new0(TgGuriParse, 1);

    g_object_set_data_full(G_OBJECT(UtGtkLayout->window->main),
            "UtGtkUri->parse", UtGtkUri->parse, (GDestroyNotify)FvGuriFree);
    g_object_set_data_full(G_OBJECT(UtGtkLayout->window->main),
            "UtGtkUri->entry", UtGtkUri->entry, (GDestroyNotify)g_free);
    g_object_set_data_full(G_OBJECT(UtGtkLayout->window->main),
            "UtGtkUri->spin", UtGtkUri->spin, (GDestroyNotify)g_free);
    g_object_set_data_full(G_OBJECT(UtGtkLayout->window->main),
            "UtGtkUri", UtGtkUri, (GDestroyNotify)g_free);

    FvGtkUriWidget(UtGtkLayout, UtGtkUri);

    UtGtkUri->parse = FtGuriParse(VcGtkUri ? VcGtkUri : "");
    gtk_editable_set_text(GTK_EDITABLE(UtGtkUri->entry->uri), UtGtkUri->parse->uri);
    FvGtkUriEntryParse(GTK_EDITABLE(UtGtkUri->entry->uri), UtGtkUri);
}

