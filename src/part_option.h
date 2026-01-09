#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>




gboolean UgOptVersion = FALSE;
gboolean UgOptWindow = FALSE;

GOptionEntry UgOptionentry[] = {
    {"version", 'v',    0,  G_OPTION_ARG_NONE,      &UgOptVersion,
        "Version",  NULL},
    {"window",  'w',    0,  G_OPTION_ARG_NONE,      &UgOptWindow,
        "Window",   NULL},
    {NULL}
};


    int
FiOptionGlib(int ViArgsOptionglib, char **AcArgsOptionglib)
{
    gchar **AgArgsOptionglib;
    GOptionContext *UgOptioncontext;

    AgArgsOptionglib = g_strdupv((gchar **)AcArgsOptionglib);
    UgOptioncontext = g_option_context_new(NULL);

    g_option_context_set_help_enabled(UgOptioncontext, FALSE);
    g_option_context_add_main_entries(UgOptioncontext, UgOptionentry, NULL);
    g_option_context_parse_strv(UgOptioncontext, &AgArgsOptionglib, NULL);
    g_strfreev(AgArgsOptionglib);

    if (UgOptVersion) {
        printf("\nVersion\n");
        exit(EXIT_SUCCESS);
    }

    return EXIT_SUCCESS;
}


    int
FiOptionGtk(GApplication *UgApplication,
        GApplicationCommandLine *UgCommandline)
{
    int ViOptArgs;
    char **AcOptArgs;

    AcOptArgs = g_application_command_line_get_arguments(UgCommandline,
            &ViOptArgs);

    if (UgOptWindow && ViOptArgs > 1) {
        FvGtkActivate(GTK_APPLICATION(UgApplication),
                AcOptArgs);
    }

    return EXIT_SUCCESS;
}

