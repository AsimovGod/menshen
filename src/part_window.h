#include <stdio.h>
#include <stdlib.h>




    void
FvGtkActivate(GtkApplication* UgApplication, char** AcArgsGtkActivate)
{
    GtkWidget* UgWindow;
    GtkWidget* UgHeaderbar;
    GtkWidget* UgControl;

    UgWindow = gtk_application_window_new(UgApplication);
    gtk_window_set_title(GTK_WINDOW(UgWindow), "MenShen");
    gtk_window_set_default_size(GTK_WINDOW(UgWindow), 960, 540);

    UgHeaderbar = gtk_header_bar_new();
    gtk_window_set_titlebar(GTK_WINDOW(UgWindow), UgHeaderbar);

    UgControl = gtk_window_controls_new(GTK_PACK_END);
    gtk_window_controls_set_decoration_layout(GTK_WINDOW_CONTROLS(UgControl),
            "minimize,maximize");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(UgHeaderbar), UgControl);

    UtGtkContainer->main = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    gtk_widget_set_valign(UtGtkContainer->main, GTK_ALIGN_FILL);
    gtk_widget_set_halign(UtGtkContainer->main, GTK_ALIGN_FILL);
    gtk_window_set_child(GTK_WINDOW(UgWindow), UtGtkContainer->main);

    UtGtkContainer->mainUp = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_set_valign(UtGtkContainer->main, GTK_ALIGN_FILL);
    gtk_widget_set_halign(UtGtkContainer->main, GTK_ALIGN_FILL);
    gtk_paned_set_start_child(GTK_PANED(UtGtkContainer->main),
            UtGtkContainer->mainUp);

    UtGtkContainer->mainDown = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_set_valign(UtGtkContainer->main, GTK_ALIGN_FILL);
    gtk_widget_set_halign(UtGtkContainer->main, GTK_ALIGN_FILL);
    gtk_paned_set_start_child(GTK_PANED(UtGtkContainer->main),
            UtGtkContainer->mainDown);

    FvGtkUri(AcArgsGtkActivate[1]);

    gtk_window_present(GTK_WINDOW(UgWindow));
    gtk_window_set_focus(GTK_WINDOW(UgWindow), NULL);
}

