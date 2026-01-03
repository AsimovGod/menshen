#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <adwaita.h>


    static void
FsvGtkActivate(GtkApplication *UgApplication)
{
    GtkWidget *UgWindow = adw_window_new();
    gtk_window_set_application(GTK_WINDOW(UgWindow), UgApplication);
    gtk_window_set_decorated(GTK_WINDOW(UgWindow), FALSE);
    gtk_window_set_title(GTK_WINDOW(UgWindow), "MenShen");
    gtk_window_set_default_size(GTK_WINDOW(UgWindow), 960, 540);

    GtkWidget *UaToolbar = adw_toolbar_view_new();
    adw_window_set_content(ADW_WINDOW(UgWindow), UaToolbar);

    GtkWidget *UaHeaderbar = adw_header_bar_new();
    adw_toolbar_view_add_top_bar(ADW_TOOLBAR_VIEW(UaToolbar),
            GTK_WIDGET(UaHeaderbar));

    GtkWidget *UgControl = gtk_window_controls_new(GTK_PACK_END);
    gtk_window_controls_set_decoration_layout(GTK_WINDOW_CONTROLS(UgControl),
            "minimize,maximize,close");
    adw_header_bar_pack_end(ADW_HEADER_BAR(UaHeaderbar), UgControl);

    GtkWidget *UgCenterbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_valign(UgCenterbox, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(UgCenterbox, GTK_ALIGN_CENTER);

    GtkWidget *UgEntry = gtk_entry_new();
    gtk_editable_set_text(GTK_EDITABLE(UgEntry), "Hello World.");

    gtk_box_append(GTK_BOX(UgCenterbox), UgEntry);
    adw_toolbar_view_set_content(ADW_TOOLBAR_VIEW(UaToolbar), UgCenterbox);

    gtk_window_present(GTK_WINDOW(UgWindow));
}


    int
FiGtk(int ViArgsGtk, char *AcArgsGtk[])
{
    AdwApplication *UgApplication;

    int ViStat;

    UgApplication = adw_application_new("com.AsimovGod.menshen",
            G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(UgApplication, "activate",
            G_CALLBACK(FsvGtkActivate), NULL);

    ViStat = g_application_run(G_APPLICATION(UgApplication),
            ViArgsGtk, AcArgsGtk);

    g_object_unref(UgApplication);

    return ViStat;
}
