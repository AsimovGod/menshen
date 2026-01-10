#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>




typedef struct {
    gchar* scheme;
    gchar* host;
    gint port;
    gchar* path;
    gchar* query;
    gchar* fragment;
} TgGuriParse;


TgGuriParse*
FtGuriParse(const gchar* UgUriImport) {
    GUri* UgUriExport;

    TgGuriParse* UtGuriParse;

    UgUriExport = g_uri_parse(UgUriImport, G_URI_FLAGS_NONE, NULL);

    if (!UgUriExport) {
        return NULL;
    }

    UtGuriParse = g_new0(TgGuriParse, 1);
    UtGuriParse->scheme = g_strdup(g_uri_get_scheme(UgUriExport));
    UtGuriParse->host = g_strdup(g_uri_get_host(UgUriExport));
    UtGuriParse->port = g_uri_get_port(UgUriExport);
    UtGuriParse->path = g_strdup(g_uri_get_path(UgUriExport));
    UtGuriParse->query = g_strdup(g_uri_get_query(UgUriExport));
    UtGuriParse->fragment = g_strdup(g_uri_get_fragment(UgUriExport));

    g_uri_unref(UgUriExport);
    return UtGuriParse;
}


int
FiGuriFree(TgGuriParse* UtGuriFree) {
    if (!UtGuriFree) {
        return EXIT_FAILURE;
    }

    g_free(UtGuriFree->scheme);
    g_free(UtGuriFree->host);
    g_free(UtGuriFree->path);
    g_free(UtGuriFree->query);
    g_free(UtGuriFree->fragment);
    g_free(UtGuriFree);
}


int
FiUrlPrint(char* VcUrlPrint) {
    TgGuriParse* UtUrlPrint;

    UtUrlPrint = FtGuriParse(VcUrlPrint);

    if (!UtUrlPrint) {
        return EXIT_FAILURE;
    }

    printf("\n");
    printf("url         %s\n", VcUrlPrint);
    printf("scheme      %s\n", UtUrlPrint->scheme);
    printf("host        %s\n", UtUrlPrint->host);
    printf("port        %d\n", UtUrlPrint->port);
    printf("path        %s\n", UtUrlPrint->path);
    printf("query       %s\n", UtUrlPrint->query);
    printf("fragment    %s\n", UtUrlPrint->fragment);

    FiGuriFree(UtUrlPrint);

    return EXIT_SUCCESS;
}
