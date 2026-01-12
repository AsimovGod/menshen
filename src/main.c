#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <adwaita.h>

#include "part_file.h"
#include "part_guri.h"
#include "part_uribox.h"
#include "part_window.h"
#include "part_option.h"




    int
main(int ViArgs, char** AcArgs)
{
    int ViExit;

    GtkApplication* UgApplication;

    ViExit = FiOptionGlib(ViArgs, AcArgs);

    if (UgOptMode
            && g_strcmp0(UgOptMode, "1") == 0
            || g_strcmp0(UgOptMode, "window") == 0)
    {
        adw_init();
    }

    UgApplication = gtk_application_new("com.AsimovGod.menshen",
            G_APPLICATION_HANDLES_COMMAND_LINE);

    g_application_add_main_option_entries(G_APPLICATION(UgApplication),
            UgOptionentry);

    g_signal_connect(UgApplication,
            "command-line", G_CALLBACK(GiOptionGtk), NULL);

    ViExit = g_application_run(G_APPLICATION(UgApplication),
            ViArgs, AcArgs);

    g_object_unref(UgApplication);

    return ViExit;
}
