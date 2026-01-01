#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>


    static void
FsvGtkActivate(GApplication *UgApplication)
{
    GtkWidget *UgWindow;
    GtkWidget *UgScrolled;
    GtkWidget *UgTextview;
    GtkTextBuffer *UgTextbuffer;
    gchar *UgTextchar;

    UgTextchar = 
        "Text"
        "debug"
        ;

    UgWindow = gtk_application_window_new(GTK_APPLICATION(UgApplication));
    gtk_window_set_title(GTK_WINDOW(UgWindow), "MenShen");
    gtk_window_set_default_size(GTK_WINDOW(UgWindow), 960, 540);

    UgScrolled = gtk_scrolled_window_new ();
    gtk_window_set_child (GTK_WINDOW (UgWindow), UgScrolled);

    UgTextview = gtk_text_view_new();
    UgTextbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(UgTextview));
    gtk_text_buffer_set_text(UgTextbuffer, UgTextchar, -1);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(UgTextview),
            GTK_WRAP_WORD_CHAR);

    gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW (UgScrolled), UgTextview);

    gtk_window_present(GTK_WINDOW(UgWindow));
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
