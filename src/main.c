#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "part_window.h"
#include "part_show.h"
#include "part_option.h"




    int
main(int ViArgs, char **AcArgs)
{
    int ViStatGtk;

    GtkApplication *UgApplication;

    ViStatGtk = FiOptionGlib(ViArgs, AcArgs);

    UgApplication = gtk_application_new("com.AsimovGod.menshen",
            G_APPLICATION_HANDLES_COMMAND_LINE);

    g_application_add_main_option_entries(G_APPLICATION(UgApplication),
            UgOptionentry);

    g_signal_connect(UgApplication, "command-line",
            G_CALLBACK(FiOptionGtk), NULL);

    ViStatGtk = g_application_run(G_APPLICATION(UgApplication),
            ViArgs, AcArgs);

    g_object_unref(UgApplication);

    return ViStatGtk;
}
