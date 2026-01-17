#include <stdio.h>




    void
FvGtkLayoutFree(void* PvFree)
{
    TgGtkLayout* UtGtkLayout;

    UtGtkLayout = PvFree;

    if (! UtGtkLayout) return;

    g_free(UtGtkLayout->window);
    g_free(UtGtkLayout->headerbar);
    g_free(UtGtkLayout->control);
    g_free(UtGtkLayout->paned);
    g_free(UtGtkLayout->grid);
    g_free(UtGtkLayout->scroll);
    g_free(UtGtkLayout);
}


    void
FvGtkActivate(GtkApplication* UgApplication, char** AcArgsGtkActivate)
{
    TgGtkLayout* UtGtkLayout;

    UtGtkLayout = g_new0(TgGtkLayout, 1);
    UtGtkLayout->window = g_new0(TgGtkWindow, 1);
    UtGtkLayout->headerbar = g_new0(TgGtkHeaderbar, 1);
    UtGtkLayout->control = g_new0(TgGtkControl, 1);
    UtGtkLayout->paned = g_new0(TgGtkPaned, 1);
    UtGtkLayout->grid = g_new0(TgGtkGrid, 1);
    UtGtkLayout->scroll = g_new0(TgGtkScroll, 1);

    UtGtkLayout->window->main = gtk_application_window_new(UgApplication);
    UtGtkLayout->headerbar->main = gtk_header_bar_new();
    UtGtkLayout->control->main = gtk_window_controls_new(GTK_PACK_END);
    UtGtkLayout->paned->main = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    UtGtkLayout->paned->mainLeft = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    UtGtkLayout->paned->mainRight = gtk_paned_new(GTK_ORIENTATION_VERTICAL);

    UtGtkLayout->window->mainT = "MenShen";
    UtGtkLayout->window->mainW = 960;
    UtGtkLayout->window->mainH = 540;
    UtGtkLayout->paned->mainR = 0.7;
    UtGtkLayout->paned->mainLeftR = 0.2;
    UtGtkLayout->paned->mainRightR = 0.2;

    g_object_set_data_full(G_OBJECT(UtGtkLayout->window->main),
            "UtGtkLayout", UtGtkLayout, (GDestroyNotify)FvGtkLayoutFree);

    gtk_window_set_titlebar(GTK_WINDOW(UtGtkLayout->window->main),
            UtGtkLayout->headerbar->main);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(UtGtkLayout->headerbar->main),
            UtGtkLayout->control->main);
    gtk_window_set_child(GTK_WINDOW(UtGtkLayout->window->main),
            UtGtkLayout->paned->main);
    gtk_paned_set_start_child(GTK_PANED(UtGtkLayout->paned->main),
            UtGtkLayout->paned->mainLeft);
    gtk_paned_set_end_child(GTK_PANED(UtGtkLayout->paned->main),
            UtGtkLayout->paned->mainRight);

    gtk_window_controls_set_decoration_layout(
            GTK_WINDOW_CONTROLS(UtGtkLayout->control->main),
            "minimize,maximize");
    gtk_window_set_title(GTK_WINDOW(UtGtkLayout->window->main),
            UtGtkLayout->window->mainT);
    gtk_window_set_default_size(GTK_WINDOW(UtGtkLayout->window->main),
            UtGtkLayout->window->mainW, UtGtkLayout->window->mainH);

    gtk_paned_set_position(GTK_PANED(UtGtkLayout->paned->main),
            UtGtkLayout->paned->mainR * UtGtkLayout->window->mainW);
    gtk_paned_set_position(GTK_PANED(UtGtkLayout->paned->mainLeft),
            UtGtkLayout->paned->mainLeftR * UtGtkLayout->window->mainH);
    gtk_paned_set_position(GTK_PANED(UtGtkLayout->paned->mainRight),
            UtGtkLayout->paned->mainRightR * UtGtkLayout->window->mainH);

    gtk_widget_set_valign(UtGtkLayout->paned->main, GTK_ALIGN_FILL);
    gtk_widget_set_halign(UtGtkLayout->paned->main, GTK_ALIGN_FILL);
    gtk_widget_set_valign(UtGtkLayout->paned->mainLeft, GTK_ALIGN_FILL);
    gtk_widget_set_halign(UtGtkLayout->paned->mainLeft, GTK_ALIGN_FILL);
    gtk_widget_set_valign(UtGtkLayout->paned->mainRight, GTK_ALIGN_FILL);
    gtk_widget_set_halign(UtGtkLayout->paned->mainRight, GTK_ALIGN_FILL);

    FvGtkUri(UtGtkLayout, AcArgsGtkActivate[1]);

    gtk_window_present(GTK_WINDOW(UtGtkLayout->window->main));
    gtk_window_set_focus(GTK_WINDOW(UtGtkLayout->window->main), NULL);
}

