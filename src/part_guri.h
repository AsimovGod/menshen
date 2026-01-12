#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>




typedef struct {
    gchar* string;
    gchar* scheme;
    gchar* host;
    gint port;
    gchar* path;
    gchar* query;
    gchar* fragment;
    gchar* uri;
} TgGuriParse;



    char*
FcGuriBuild(TgGuriParse* UtGuriBuild)
{
    gchar* VcUriExport;
    GUri* UgUriExport;

    UgUriExport = g_uri_build(G_URI_FLAGS_NONE,
            UtGuriBuild->scheme ? UtGuriBuild->scheme : g_strdup(""),
            NULL,
            UtGuriBuild->host ? UtGuriBuild->host : g_strdup(""),
            UtGuriBuild->port ? UtGuriBuild->port : -1,
            UtGuriBuild->path ? UtGuriBuild->path : g_strdup(""),
            UtGuriBuild->query ? UtGuriBuild->query : NULL,
            UtGuriBuild->fragment ? UtGuriBuild->fragment : NULL);

    VcUriExport = g_uri_to_string(UgUriExport);

    g_uri_unref(UgUriExport);

    return VcUriExport;
}


    TgGuriParse*
FtGuriParse(const gchar* VcUriExport)
{
    const gchar* VcGuriParse;
    gint ViGuriParsePort;
    GUri* UgUriExport;
    TgGuriParse* UtGuriParse;

    UgUriExport = g_uri_parse(VcUriExport, G_URI_FLAGS_NONE, NULL);

    if (UgUriExport) {
        UtGuriParse = g_new0(TgGuriParse, 1);
        UtGuriParse->string = g_strdup(VcUriExport);
    }
    else {
        return NULL;
    }

    VcGuriParse = g_uri_get_scheme(UgUriExport);
    UtGuriParse->scheme = VcGuriParse ? g_strdup(VcGuriParse) : g_strdup("");

    VcGuriParse = g_uri_get_host(UgUriExport);
    UtGuriParse->host = VcGuriParse ? g_strdup(VcGuriParse) : g_strdup("");

    ViGuriParsePort = g_uri_get_port(UgUriExport) ;
    UtGuriParse->port = ViGuriParsePort ? ViGuriParsePort : -1;

    VcGuriParse = g_uri_get_path(UgUriExport);
    UtGuriParse->path = VcGuriParse ? g_strdup(VcGuriParse) : g_strdup("");

    VcGuriParse = g_uri_get_query(UgUriExport);
    UtGuriParse->query = VcGuriParse ? g_strdup(VcGuriParse) : NULL;

    VcGuriParse = g_uri_get_fragment(UgUriExport);
    UtGuriParse->fragment = VcGuriParse ? g_strdup(VcGuriParse) : NULL;

    VcGuriParse = FcGuriBuild(UtGuriParse);
    UtGuriParse->uri = VcGuriParse ? g_strdup(VcGuriParse) : NULL;

    g_uri_unref(UgUriExport);
    return UtGuriParse;
}


    void
FvGuriFree(gpointer UpGuriFree)
{
    TgGuriParse* UtGuriFree;

    UtGuriFree = UpGuriFree;

    if (!UtGuriFree) return;

    g_free(UtGuriFree->string);
    g_free(UtGuriFree->scheme);
    g_free(UtGuriFree->host);
    g_free(UtGuriFree->path);
    g_free(UtGuriFree->query);
    g_free(UtGuriFree->fragment);
    g_free(UtGuriFree->uri);
    g_free(UtGuriFree);
}


    int
FiUriPrint(char* VcUriPrint)
{
    TgGuriParse* UtUriPrint;

    UtUriPrint = FtGuriParse(VcUriPrint);

    if (!UtUriPrint) {
        return EXIT_FAILURE;
    }

    printf("\n");
    printf("uri         %s\n", UtUriPrint->uri);
    printf("scheme      %s\n", UtUriPrint->scheme);
    printf("host        %s\n", UtUriPrint->host);
    printf("port        %d\n", UtUriPrint->port);
    printf("path        %s\n", UtUriPrint->path);
    printf("query       %s\n", UtUriPrint->query);
    printf("fragment    %s\n", UtUriPrint->fragment);

    FvGuriFree(UtUriPrint);

    return EXIT_SUCCESS;
}

