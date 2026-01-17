// main.c



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <adwaita.h>

#include "main.h"
#include "part_file.h"
#include "part_mime_list.h"
#include "part_mime.h"
#include "part_guri.h"
#include "part_uri_change.h"
#include "part_uri_clipboard.h"
#include "part_uri_widget.h"
#include "part_uri.h"
#include "part_window.h"
#include "part_option.h"



    int
main(int ViArgs, char** AcArgs)
{
    int ViExit;
    GtkApplication* UgApplication;
    AdwStyleManager* UaStylemanager;
    SuOption* PsOption;

    PsOption = FgOptionInit();
    ViExit = FiOptionGlib(ViArgs, AcArgs, PsOption);

    if (PsOption->mode && g_strcmp0(PsOption->mode, "1") == 0)
    {
        adw_init();
        UaStylemanager = adw_style_manager_get_default();
        adw_style_manager_set_color_scheme(UaStylemanager,
                ADW_COLOR_SCHEME_PREFER_DARK);
    }

    UgApplication = gtk_application_new(NULL,
            G_APPLICATION_HANDLES_COMMAND_LINE);

    g_application_add_main_option_entries(G_APPLICATION(UgApplication),
            PsOption->option);

    g_signal_connect(UgApplication,
            "command-line", G_CALLBACK(FiOptionGtk), PsOption);

    ViExit = g_application_run(G_APPLICATION(UgApplication), ViArgs, AcArgs);

    g_object_unref(UgApplication);
    FvOptionFree(PsOption);

    return ViExit;
}
