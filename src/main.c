#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <adwaita.h>

#include "main.h"
#include "part_file.h"
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
    TgOption* UtOption;

    UtOption = FgOptionInit();
    ViExit = FiOptionGlib(ViArgs, AcArgs, UtOption);

    if (UtOption->mode && g_strcmp0(UtOption->mode, "1") == 0)
    {
        adw_init();
        UaStylemanager = adw_style_manager_get_default();
        adw_style_manager_set_color_scheme(UaStylemanager,
                ADW_COLOR_SCHEME_PREFER_DARK);
    }

    UgApplication = gtk_application_new(NULL,
            G_APPLICATION_HANDLES_COMMAND_LINE);

    g_application_add_main_option_entries(G_APPLICATION(UgApplication),
            UtOption->option);

    g_signal_connect(UgApplication,
            "command-line", G_CALLBACK(FiOptionGtk), UtOption);

    ViExit = g_application_run(G_APPLICATION(UgApplication), ViArgs, AcArgs);

    g_object_unref(UgApplication);
    FvOptionFree(UtOption);

    return ViExit;
}
