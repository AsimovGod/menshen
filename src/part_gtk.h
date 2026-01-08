#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>




    static void
FsvGtkActivate(GtkApplication *UgApplication)
{
    GtkWidget *UgWindow;
    GtkWidget *UgHeaderbar;
    GtkWidget *UgControl;
    GtkWidget *UgCenterbox;
    GtkWidget *UgEntry;


    UgWindow = gtk_application_window_new(UgApplication);
    gtk_window_set_title(GTK_WINDOW(UgWindow), "MenShen");
    gtk_window_set_default_size(GTK_WINDOW(UgWindow), 960, 540);

    UgHeaderbar = gtk_header_bar_new();
    gtk_window_set_titlebar(GTK_WINDOW(UgWindow), UgHeaderbar);

    UgControl = gtk_window_controls_new(GTK_PACK_END);
    gtk_window_controls_set_decoration_layout(GTK_WINDOW_CONTROLS(UgControl),
            "minimize,maximize");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(UgHeaderbar), UgControl);

    UgCenterbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_valign(UgCenterbox, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(UgCenterbox, GTK_ALIGN_CENTER);

    UgEntry = gtk_entry_new();
    gtk_editable_set_text(GTK_EDITABLE(UgEntry), "Hello World.");
    gtk_box_append(GTK_BOX(UgCenterbox), UgEntry);
    gtk_window_set_child(GTK_WINDOW(UgWindow), UgCenterbox);

    gtk_window_present(GTK_WINDOW(UgWindow));
}


    int
FiGtk(int ViArgsGtk, char *AcArgsGtk[])
{
    int ViStatGtk;

    GtkApplication *UgApplication;

    UgApplication = gtk_application_new("com.AsimovGod.menshen",
            G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(UgApplication, "activate",
            G_CALLBACK(FsvGtkActivate), NULL);

    ViStatGtk = g_application_run(G_APPLICATION(UgApplication),
            ViArgsGtk, AcArgsGtk);

    g_object_unref(UgApplication);

    return ViStatGtk;
}
