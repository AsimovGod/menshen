#include <stdio.h>
#include <stdlib.h>




typedef struct {
    gchar* string;
    gchar* scheme;
    gchar* userinfo;
    gchar* host;
    gint port;
    gchar* path;
    gchar* query;
    gchar* fragment;
    gchar* uri;
} TgGuriParse;

typedef struct {
    GtkWidget* uri;
    GtkWidget* scheme;
    GtkWidget* userinfo;
    GtkWidget* host;
    GtkWidget* port;
    GtkWidget* path;
    GtkWidget* query;
    GtkWidget* fragment;
} TgGuriWidget;

typedef struct {
    GtkWidget* main;
    GtkWidget* mainUp;
    GtkWidget* mainDown;
    GtkWidget* uriParse;
    GtkWidget* uriBuild;
} TgGtkContainer;




_Bool UgOptVersion = FALSE;
_Bool UgOptWindow = FALSE;
char* UgOptMode = NULL;
char* UgOptStyle = NULL;

GOptionEntry UgOptionentry[] = {
    {"version", 'v',    0,  G_OPTION_ARG_NONE,      &UgOptVersion,
        "Version",  NULL},
    {"mode",    'm',    0,  G_OPTION_ARG_STRING,    &UgOptMode,
        "Mode",     NULL},
    {"style",   's',    0,  G_OPTION_ARG_STRING,    &UgOptStyle,
        "Style",    NULL},
    {NULL}
};


_Bool VbUriChange = FALSE;

static TgGtkContainer* UtGtkContainer;
static TgGuriParse* UtUriParse;
static TgGuriWidget* UtUriWidget;


    void FvGuriFree(void* UpGuriFree);

    static inline void
FivStructNew()
{
    UtUriParse = g_new0(TgGuriParse, 1);
    UtUriWidget = g_new0(TgGuriWidget, 1);

    UtGtkContainer = g_new0(TgGtkContainer, 1);
}

static void
FvStructFree()
{
    FvGuriFree(UtUriParse);
    free(UtUriWidget);
    free(UtGtkContainer);
}

