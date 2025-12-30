#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>



    static void
FsvGtkActivateChickClose(GtkButton *UgButton,
        GtkWindow *UgWindow)
{
    gtk_window_destroy(UgWindow);
    g_print("Clicked.\n");
}

    static void
FsvGtkActivateChickBox(GtkButton *UgButton)
{
    const char *AccStr;

    AccStr = gtk_button_get_label(UgButton);

    if (g_strcmp0(AccStr, "Hello.") == 0) {
        gtk_button_set_label(UgButton, "Bye.");
    }
    else {
        gtk_button_set_label(UgButton, "Hello.");
    }
}

    static void
FsvGtkActivate(GApplication *UgApplication,
        gpointer *UgUserData
        )
{
    GtkWidget *UgWindow;
    GtkWidget *UgBox;
    GtkWidget *UgButton1;
    GtkWidget *UgButton2;

    UgWindow = gtk_application_window_new(GTK_APPLICATION(UgApplication));
    gtk_window_set_title(GTK_WINDOW(UgWindow), "MenShen");
    gtk_window_set_default_size(GTK_WINDOW(UgWindow), 960, 540);

    UgBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_set_homogeneous(GTK_BOX(UgBox), TRUE);
    gtk_window_set_child(GTK_WINDOW(UgWindow), UgBox);

    UgButton1 = gtk_button_new_with_label("Close");
    g_signal_connect(UgButton1, "clicked",
            G_CALLBACK(FsvGtkActivateChickClose), UgWindow);

    UgButton2 = gtk_button_new_with_label("Close");
    g_signal_connect(UgButton2, "clicked",
            G_CALLBACK(FsvGtkActivateChickBox), NULL);

    gtk_box_append(GTK_BOX(UgBox), UgButton1);
    gtk_box_append(GTK_BOX(UgBox), UgButton2);

    gtk_window_present(GTK_WINDOW(UgWindow));

    g_print("GtkApplication is activated.\n");
}



    int
FiGtk(int ViArgsGtk, char *AcArgsGtk[])
{
    GtkApplication *UgApplication;

    int ViStat;

    UgApplication = gtk_application_new("com.AsimovGod.menshen",
            G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(UgApplication, "activate",
            G_CALLBACK(FsvGtkActivate), NULL);

    ViStat = g_application_run(G_APPLICATION(UgApplication),
            ViArgsGtk, AcArgsGtk);

    g_object_unref(UgApplication);

    return ViStat;
}
