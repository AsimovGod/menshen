#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>




    void
FvGtkActivate(GtkApplication* UgApplication, char** AcArgsGtkActivate)
{
    GtkWidget* UgWindow;
    GtkWidget* UgHeaderbar;
    GtkWidget* UgControl;
    GtkWidget* UgPanedMain;
    GtkWidget* UgPanedMainUp;
    GtkWidget* UgPanedMainDown;

    UgWindow = gtk_application_window_new(UgApplication);
    gtk_window_set_title(GTK_WINDOW(UgWindow), "MenShen");
    gtk_window_set_default_size(GTK_WINDOW(UgWindow), 960, 540);

    UgHeaderbar = gtk_header_bar_new();
    gtk_window_set_titlebar(GTK_WINDOW(UgWindow), UgHeaderbar);

    UgControl = gtk_window_controls_new(GTK_PACK_END);
    gtk_window_controls_set_decoration_layout(GTK_WINDOW_CONTROLS(UgControl),
            "minimize,maximize");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(UgHeaderbar), UgControl);

    UgPanedMain = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    gtk_widget_set_valign(UgPanedMain, GTK_ALIGN_FILL);
    gtk_widget_set_halign(UgPanedMain, GTK_ALIGN_FILL);
    gtk_window_set_child(GTK_WINDOW(UgWindow), UgPanedMain);

    UgPanedMainUp = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_set_valign(UgPanedMain, GTK_ALIGN_FILL);
    gtk_widget_set_halign(UgPanedMain, GTK_ALIGN_FILL);
    gtk_paned_set_start_child(GTK_PANED(UgPanedMain), UgPanedMainUp);

    UgPanedMainDown = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_set_valign(UgPanedMain, GTK_ALIGN_FILL);
    gtk_widget_set_halign(UgPanedMain, GTK_ALIGN_FILL);
    gtk_paned_set_end_child(GTK_PANED(UgPanedMain), UgPanedMainDown);

    FvGtkUri(UgPanedMainUp, UgPanedMainDown, AcArgsGtkActivate[1]);

    gtk_window_present(GTK_WINDOW(UgWindow));
    gtk_window_set_focus(GTK_WINDOW(UgWindow), NULL);
}

