#include <stdio.h>
#include <stdlib.h>




    int
FiOptionGlib(int ViArgsOptionglib, char** AcArgsOptionglib)
{
    int ViLoop;
    int ViOptArgs;
    char** AcOptArgs;

    GOptionContext* UgOptioncontext;

    ViOptArgs = ViArgsOptionglib;
    AcOptArgs = g_strdupv((char**)AcArgsOptionglib);
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
        for (ViLoop = 1; ViLoop < ViOptArgs; ViLoop++) {
            FvUriPrint(AcOptArgs[ViLoop]);
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
    int ViOptArgs;
    char** AcOptArgs;

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

