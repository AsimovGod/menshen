#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>


    static void
FsvGtkActivate(GApplication *UgApplication)
{
    g_printerr ("You need a filename argument.\n");
}

    static void
FsvGtkOpen(GApplication *UgApplication,
        GFile **UgFiles,
        int ViFiles,
        char *AcHint)
{
    GtkWidget *UgWindow;
    GtkWidget *UgNotebook;
    GtkWidget *UgLabel;
    GtkNotebookPage *UgNotebookpage;
    GtkWidget *UgScroll;
    GtkWidget *UgTextview;
    GtkTextBuffer *UgTextbuffer;

    gsize UgLength;
    GError *UgErr = NULL;

    char *AcContent;
    char *AcFilename;

    UgWindow = gtk_application_window_new(GTK_APPLICATION(UgApplication));
    gtk_window_set_title(GTK_WINDOW(UgWindow), "MenShen");
    gtk_window_set_default_size(GTK_WINDOW(UgWindow), 960, 540);

    UgNotebook = gtk_notebook_new();
    gtk_window_set_child(GTK_WINDOW (UgWindow), UgNotebook);

    for (int ViLoop = 0; ViLoop < ViFiles; ViLoop++) {
        if (g_file_load_contents(UgFiles[ViLoop],
                    NULL, &AcContent, &UgLength, NULL, &UgErr))
        {
            UgScroll = gtk_scrolled_window_new();
            UgTextview = gtk_text_view_new();
            UgTextbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(UgTextview));
            gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(UgTextview),
                    GTK_WRAP_WORD_CHAR);
            gtk_text_view_set_editable(GTK_TEXT_VIEW (UgTextview), FALSE);
            gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW (UgScroll), UgTextview);

            gtk_text_buffer_set_text(UgTextbuffer, AcContent, UgLength);
            g_free(AcContent);

            if ((AcFilename = g_file_get_basename(UgFiles[ViLoop])) != NULL) {
                UgLabel = gtk_label_new(AcFilename);
                gtk_window_set_title(GTK_WINDOW(UgWindow), AcFilename);
                g_free(AcFilename);
            }
            else {
                UgLabel = gtk_label_new("");
            }

            gtk_notebook_append_page(GTK_NOTEBOOK(UgNotebook),
                    UgScroll, UgLabel);
            UgNotebookpage = gtk_notebook_get_page(GTK_NOTEBOOK(UgNotebook),
                    UgScroll);

            g_object_set(UgNotebookpage, "tab-expand", TRUE, NULL);

        }
        else {
            g_printerr("%s.\n", UgErr->message);
            g_error_free(UgErr);
        }
    }

    if (gtk_notebook_get_n_pages(GTK_NOTEBOOK (UgNotebook)) > 0) {
        gtk_window_present(GTK_WINDOW(UgWindow));
    }
    else {
        gtk_window_destroy(GTK_WINDOW(UgWindow));
    }
    gtk_window_set_child (GTK_WINDOW (UgWindow), UgScroll);
}



    int
FiGtk(int ViArgsGtk, char *AcArgsGtk[])
{
    GtkApplication *UgApplication;

    int ViStat;

    UgApplication = gtk_application_new("com.AsimovGod.menshen",
            G_APPLICATION_HANDLES_OPEN);

    g_signal_connect(UgApplication, "activate",
            G_CALLBACK(FsvGtkActivate), NULL);

    g_signal_connect (UgApplication, "open",
            G_CALLBACK (FsvGtkOpen), NULL);

    ViStat = g_application_run(G_APPLICATION(UgApplication),
            ViArgsGtk, AcArgsGtk);

    g_object_unref(UgApplication);

    return ViStat;
}
