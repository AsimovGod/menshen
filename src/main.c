#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <adwaita.h>

#include "init.h"
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
    AdwStyleManager* UaStylemanager;

    ViExit = FiOptionGlib(ViArgs, AcArgs);

    if (UgOptMode
            && g_strcmp0(UgOptMode, "1") == 0
            || g_strcmp0(UgOptMode, "window") == 0)
    {
        adw_init();

        UaStylemanager = adw_style_manager_get_default();

        adw_style_manager_set_color_scheme(UaStylemanager,
                ADW_COLOR_SCHEME_PREFER_DARK);
    }

    UgApplication = gtk_application_new(NULL,
            G_APPLICATION_HANDLES_COMMAND_LINE);

    g_application_add_main_option_entries(G_APPLICATION(UgApplication),
            UgOptionentry);

    g_signal_connect(UgApplication,
            "command-line", G_CALLBACK(FiOptionGtk), NULL);

    FivStructNew();

    ViExit = g_application_run(G_APPLICATION(UgApplication),
            ViArgs, AcArgs);

    g_object_unref(UgApplication);

    FvStructFree();

    return ViExit;
}
