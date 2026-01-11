#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>




gboolean UgOptVersion = FALSE;
gboolean UgOptWindow = FALSE;
gchar* UgOptMode = "1";
gchar* UgOptStyle = NULL;

GOptionEntry UgOptionentry[] = {
    {"version", 'v',    0,  G_OPTION_ARG_NONE,      &UgOptVersion,
        "Version",  NULL},
    {"mode",    'm',    0,  G_OPTION_ARG_STRING,    &UgOptMode,
        "Mode",     NULL},
    {"style",   's',    0,  G_OPTION_ARG_STRING,    &UgOptStyle,
        "Style",    NULL},
    {NULL}
};


    int
FiOptionGlib(int ViArgsOptionglib, char** AcArgsOptionglib)
{
    gint ViOptArgs;
    gchar** AcOptArgs;

    GOptionContext* UgOptioncontext;

    ViOptArgs = ViArgsOptionglib;
    AcOptArgs = g_strdupv((gchar**)AcArgsOptionglib);
    UgOptioncontext = g_option_context_new(NULL);

    g_option_context_set_help_enabled(UgOptioncontext, FALSE);
    g_option_context_add_main_entries(UgOptioncontext, UgOptionentry, NULL);
    g_option_context_parse(UgOptioncontext, &ViOptArgs, &AcOptArgs, NULL);

    if (UgOptVersion) {
        printf("\n0.0.1\n");

        exit(EXIT_SUCCESS);
    }

    if (UgOptMode
            && g_strcmp0(UgOptMode, "0") == 0
            || g_strcmp0(UgOptMode, "term") == 0)
    {
        for (int ViLoop = 1; ViLoop < ViOptArgs; ViLoop++) {
            FiUriPrint(AcOptArgs[ViLoop]);
        }

        exit(EXIT_SUCCESS);
    }

    g_strfreev(AcOptArgs);

    return EXIT_SUCCESS;
}


    int
FiOptionGtk(GApplication* UgApplication,
        GApplicationCommandLine* UgCommandline)
{
    gint ViOptArgs;
    gchar** AcOptArgs;

    AcOptArgs = g_application_command_line_get_arguments(UgCommandline,
            &ViOptArgs);

    if (UgOptMode
            && g_strcmp0(UgOptMode, "1") == 0
            || g_strcmp0(UgOptMode, "window") == 0)
    {
        FvGtkActivate(GTK_APPLICATION(UgApplication), AcOptArgs);
    }

    return EXIT_SUCCESS;
}

