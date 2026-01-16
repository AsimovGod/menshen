#include <stdio.h>




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
    UtGtkLayout->window->Tmain = "MenShen";
    UtGtkLayout->window->Wmain = 960;
    UtGtkLayout->window->Hmain = 540;
    gtk_window_set_title(GTK_WINDOW(UtGtkLayout->window->main),
            UtGtkLayout->window->Tmain);
    gtk_window_set_default_size(GTK_WINDOW(UtGtkLayout->window->main),
            UtGtkLayout->window->Wmain, UtGtkLayout->window->Hmain);

    g_object_set_data_full(G_OBJECT(UtGtkLayout->window->main),
            "UtGtkLayout->window",
            UtGtkLayout->window, (GDestroyNotify)g_free);
    g_object_set_data_full(G_OBJECT(UtGtkLayout->window->main),
            "UtGtkLayout->headerbar",
            UtGtkLayout->headerbar, (GDestroyNotify)g_free);
    g_object_set_data_full(G_OBJECT(UtGtkLayout->window->main),
            "UtGtkLayout->control",
            UtGtkLayout->control, (GDestroyNotify)g_free);
    g_object_set_data_full(G_OBJECT(UtGtkLayout->window->main),
            "UtGtkLayout->paned",
            UtGtkLayout->paned, (GDestroyNotify)g_free);
    g_object_set_data_full(G_OBJECT(UtGtkLayout->window->main),
            "UtGtkLayout->grid",
            UtGtkLayout->grid, (GDestroyNotify)g_free);
    g_object_set_data_full(G_OBJECT(UtGtkLayout->window->main),
            "UtGtkLayout->scroll",
            UtGtkLayout->scroll, (GDestroyNotify)g_free);
    g_object_set_data_full(G_OBJECT(UtGtkLayout->window->main),
            "UtGtkLayout",
            UtGtkLayout, (GDestroyNotify)g_free);

    UtGtkLayout->headerbar->main = gtk_header_bar_new();
    UtGtkLayout->control->main = gtk_window_controls_new(GTK_PACK_END);

    gtk_window_set_titlebar(GTK_WINDOW(UtGtkLayout->window->main),
            UtGtkLayout->headerbar->main);
    gtk_window_controls_set_decoration_layout(
            GTK_WINDOW_CONTROLS(UtGtkLayout->control->main),
            "minimize,maximize");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(UtGtkLayout->headerbar->main),
            UtGtkLayout->control->main);

    UtGtkLayout->paned->main = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    UtGtkLayout->paned->mainLeft = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    UtGtkLayout->paned->mainRight = gtk_paned_new(GTK_ORIENTATION_VERTICAL);

    UtGtkLayout->paned->Rmain = 0.7;
    UtGtkLayout->paned->RmainLeft = 0.2;
    UtGtkLayout->paned->RmainRight = 0.2;

    gtk_paned_set_position(GTK_PANED(UtGtkLayout->paned->main),
            UtGtkLayout->paned->Rmain * UtGtkLayout->window->Wmain);
    gtk_paned_set_position(GTK_PANED(UtGtkLayout->paned->mainLeft),
            UtGtkLayout->paned->RmainLeft * UtGtkLayout->window->Hmain);
    gtk_paned_set_position(GTK_PANED(UtGtkLayout->paned->mainRight),
            UtGtkLayout->paned->RmainRight * UtGtkLayout->window->Hmain);

    gtk_widget_set_valign(UtGtkLayout->paned->main, GTK_ALIGN_FILL);
    gtk_widget_set_halign(UtGtkLayout->paned->main, GTK_ALIGN_FILL);
    gtk_widget_set_valign(UtGtkLayout->paned->mainLeft, GTK_ALIGN_FILL);
    gtk_widget_set_halign(UtGtkLayout->paned->mainLeft, GTK_ALIGN_FILL);
    gtk_widget_set_valign(UtGtkLayout->paned->mainRight, GTK_ALIGN_FILL);
    gtk_widget_set_halign(UtGtkLayout->paned->mainRight, GTK_ALIGN_FILL);

    gtk_window_set_child(GTK_WINDOW(UtGtkLayout->window->main),
            UtGtkLayout->paned->main);
    gtk_paned_set_start_child(GTK_PANED(UtGtkLayout->paned->main),
            UtGtkLayout->paned->mainLeft);
    gtk_paned_set_end_child(GTK_PANED(UtGtkLayout->paned->main),
            UtGtkLayout->paned->mainRight);

    FvGtkUri(UtGtkLayout, AcArgsGtkActivate[1]);

    gtk_window_present(GTK_WINDOW(UtGtkLayout->window->main));
    gtk_window_set_focus(GTK_WINDOW(UtGtkLayout->window->main), NULL);
}

