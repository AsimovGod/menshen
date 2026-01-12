#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>




    void
FvGtkActivate(GtkApplication* UgApplication, char** AcArgsGtkActivate)
{
    GtkWidget* UgWindow;
    GtkWidget* UgHeaderbar;
    GtkWidget* UgControl;
    GtkWidget* UgBoxMain;
    GtkWidget* UgBoxMainUp;
    GtkWidget* UgBoxMainDown;

    UgWindow = gtk_application_window_new(UgApplication);
    gtk_window_set_title(GTK_WINDOW(UgWindow), "MenShen");
    gtk_window_set_default_size(GTK_WINDOW(UgWindow), 960, 540);

    UgHeaderbar = gtk_header_bar_new();
    gtk_window_set_titlebar(GTK_WINDOW(UgWindow), UgHeaderbar);

    UgControl = gtk_window_controls_new(GTK_PACK_END);
    gtk_window_controls_set_decoration_layout(GTK_WINDOW_CONTROLS(UgControl),
            "minimize,maximize");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(UgHeaderbar), UgControl);

    UgBoxMain = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_widget_set_valign(UgBoxMain, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(UgBoxMain, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(UgWindow), UgBoxMain);

    UgBoxMainUp = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    gtk_widget_set_valign(UgBoxMain, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(UgBoxMain, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(UgBoxMain), UgBoxMainUp);

    UgBoxMainDown = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    gtk_widget_set_valign(UgBoxMain, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(UgBoxMain, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(UgBoxMain), UgBoxMainDown);

    FvGtkUri(UgBoxMainUp, UgBoxMainDown, AcArgsGtkActivate[1]);

    gtk_window_present(GTK_WINDOW(UgWindow));
    gtk_window_set_focus(GTK_WINDOW(UgWindow), NULL);
}

