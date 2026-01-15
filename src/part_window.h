#include <stdio.h>




    void
FvGtkUri(TgGtkContainer* UtGtkContainer, char* VcGtkUri)
{
    TgGtkUri* UtGtkUri;

    UtGtkContainer->scroll->uriBuild = gtk_scrolled_window_new();
    UtGtkContainer->scroll->uriParse = gtk_scrolled_window_new();

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                UtGtkContainer->scroll->uriBuild),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
                UtGtkContainer->scroll->uriParse),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_paned_set_start_child(GTK_PANED(UtGtkContainer->paned->mainUp),
            UtGtkContainer->scroll->uriBuild);
    gtk_paned_set_start_child(GTK_PANED(UtGtkContainer->paned->mainDown),
            UtGtkContainer->scroll->uriParse);

    UtGtkContainer->grid->uriBuild = gtk_grid_new();
    UtGtkContainer->grid->uriParse = gtk_grid_new();

    gtk_grid_set_row_spacing(GTK_GRID(UtGtkContainer->grid->uriBuild), 4);
    gtk_grid_set_column_spacing(GTK_GRID(UtGtkContainer->grid->uriBuild), 4);
    gtk_grid_set_row_spacing(GTK_GRID(UtGtkContainer->grid->uriParse), 4);
    gtk_grid_set_column_spacing(GTK_GRID(UtGtkContainer->grid->uriParse), 4);

    gtk_widget_set_vexpand(UtGtkContainer->grid->uriBuild, TRUE);
    gtk_widget_set_hexpand(UtGtkContainer->grid->uriBuild, TRUE);
    gtk_widget_set_vexpand(UtGtkContainer->grid->uriParse, TRUE);
    gtk_widget_set_hexpand(UtGtkContainer->grid->uriParse, TRUE);

    gtk_widget_set_valign(UtGtkContainer->grid->uriBuild, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(UtGtkContainer->grid->uriBuild, GTK_ALIGN_FILL);
    gtk_widget_set_valign(UtGtkContainer->grid->uriParse, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(UtGtkContainer->grid->uriParse, GTK_ALIGN_FILL);

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                UtGtkContainer->scroll->uriBuild),
            UtGtkContainer->grid->uriBuild);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(
                UtGtkContainer->scroll->uriParse),
            UtGtkContainer->grid->uriParse);

    UtGtkUri = g_new0(TgGtkUri, 1);
    UtGtkUri->entry = g_new0(TgGuriEntry, 1);
    UtGtkUri->spin = g_new0(TgGuriSpin, 1);
    UtGtkUri->parse = g_new0(TgGuriParse, 1);

    g_object_set_data_full(G_OBJECT(UtGtkContainer->window),
            "UtGtkUri->parse", UtGtkUri->parse, (GDestroyNotify)FvGuriFree);
    g_object_set_data_full(G_OBJECT(UtGtkContainer->window),
            "UtGtkUri->entry", UtGtkUri->entry, (GDestroyNotify)g_free);
    g_object_set_data_full(G_OBJECT(UtGtkContainer->window),
            "UtGtkUri->spin", UtGtkUri->spin, (GDestroyNotify)g_free);
    g_object_set_data_full(G_OBJECT(UtGtkContainer->window),
            "UtGtkUri", UtGtkUri, (GDestroyNotify)g_free);

    FvGtkUriWidget(UtGtkContainer, UtGtkUri);

    UtGtkUri->parse = FtGuriParse(VcGtkUri ? VcGtkUri : "");
    gtk_editable_set_text(GTK_EDITABLE(UtGtkUri->entry->uri),
            UtGtkUri->parse->uri);
    FvGtkUriParse(GTK_EDITABLE(UtGtkUri->entry->uri), UtGtkUri);
}


    void
FvGtkActivate(GtkApplication* UgApplication, char** AcArgsGtkActivate)
{
    GtkWidget* UgWindow;
    GtkWidget* UgHeaderbar;
    GtkWidget* UgControl;
    TgGtkContainer* UtGtkContainer;

    UgWindow = gtk_application_window_new(UgApplication);
    gtk_window_set_title(GTK_WINDOW(UgWindow), "MenShen");
    gtk_window_set_default_size(GTK_WINDOW(UgWindow), 960, 540);

    UgHeaderbar = gtk_header_bar_new();
    UgControl = gtk_window_controls_new(GTK_PACK_END);

    gtk_window_set_titlebar(GTK_WINDOW(UgWindow), UgHeaderbar);
    gtk_window_controls_set_decoration_layout(GTK_WINDOW_CONTROLS(UgControl),
            "minimize,maximize");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(UgHeaderbar), UgControl);

    UtGtkContainer = g_new0(TgGtkContainer, 1);
    UtGtkContainer->window = UgWindow;
    UtGtkContainer->paned = g_new0(TgGtkPaned, 1);
    UtGtkContainer->grid = g_new0(TgGtkGrid, 1);
    UtGtkContainer->scroll = g_new0(TgGtkScroll, 1);

    g_object_set_data_full(G_OBJECT(UgWindow), "UtGtkContainer->paned",
            UtGtkContainer->paned, (GDestroyNotify)g_free);
    g_object_set_data_full(G_OBJECT(UgWindow), "UtGtkContainer->box",
            UtGtkContainer->box, (GDestroyNotify)g_free);
    g_object_set_data_full(G_OBJECT(UgWindow), "UtGtkContainer->scroll",
            UtGtkContainer->scroll, (GDestroyNotify)g_free);
    g_object_set_data_full(G_OBJECT(UgWindow), "UtGtkContainer",
            UtGtkContainer, (GDestroyNotify)g_free);

    UtGtkContainer->paned->main = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    UtGtkContainer->paned->mainUp = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    UtGtkContainer->paned->mainDown = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);

    gtk_widget_set_valign(UtGtkContainer->paned->main, GTK_ALIGN_FILL);
    gtk_widget_set_halign(UtGtkContainer->paned->main, GTK_ALIGN_FILL);
    gtk_widget_set_valign(UtGtkContainer->paned->mainUp, GTK_ALIGN_FILL);
    gtk_widget_set_halign(UtGtkContainer->paned->mainUp, GTK_ALIGN_FILL);
    gtk_widget_set_valign(UtGtkContainer->paned->mainDown, GTK_ALIGN_FILL);
    gtk_widget_set_halign(UtGtkContainer->paned->mainDown, GTK_ALIGN_FILL);

    gtk_paned_set_position(GTK_PANED(UtGtkContainer->paned->main), 128);
    gtk_paned_set_position(GTK_PANED(UtGtkContainer->paned->mainUp), 256);
    gtk_paned_set_position(GTK_PANED(UtGtkContainer->paned->mainDown), 256);

    gtk_window_set_child(GTK_WINDOW(UgWindow),
            UtGtkContainer->paned->main);
    gtk_paned_set_start_child(GTK_PANED(UtGtkContainer->paned->main),
            UtGtkContainer->paned->mainUp);
    gtk_paned_set_end_child(GTK_PANED(UtGtkContainer->paned->main),
            UtGtkContainer->paned->mainDown);

    FvGtkUri(UtGtkContainer, AcArgsGtkActivate[1]);

    gtk_window_present(GTK_WINDOW(UgWindow));
    gtk_window_set_focus(GTK_WINDOW(UgWindow), NULL);
}

