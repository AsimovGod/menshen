#include <stdio.h>




    char*
FcGuriBuild(TgGuriParse* UtGuriParse)
{
    char* VcUriExport;
    char* VcGuriParsePath;
    GUri* UgUriExport;

    UgUriExport = NULL;
    VcGuriParsePath = g_strdup("");

    if (UtGuriParse->scheme && *UtGuriParse->scheme) {
        VcGuriParsePath = UtGuriParse->path && *UtGuriParse->path
            ? g_strconcat("/", UtGuriParse->path, NULL) : g_strdup("");

        UgUriExport = g_uri_build(G_URI_FLAGS_NONE,
                UtGuriParse->scheme,
                UtGuriParse->userinfo && *UtGuriParse->userinfo
                ? UtGuriParse->userinfo : NULL,
                UtGuriParse->host && *UtGuriParse->host
                ? UtGuriParse->host : NULL,
                UtGuriParse->port ? UtGuriParse->port : -1,
                VcGuriParsePath,
                UtGuriParse->query && *UtGuriParse->query
                ? UtGuriParse->query : NULL,
                UtGuriParse->fragment && *UtGuriParse->fragment
                ? UtGuriParse->fragment : NULL);

        VcUriExport = g_uri_to_string(UgUriExport ? UgUriExport : NULL);
    }
    else {
        VcUriExport = g_strdup("");
    }

    if (UgUriExport) g_uri_unref(UgUriExport);

    if (VcGuriParsePath && *VcGuriParsePath) g_free(VcGuriParsePath);

    return VcUriExport;
}


    TgGuriParse*
FtGuriParse(const char* VcUriExport)
{
    const char* VcGuriParse;
    GUri* UgUriExport;
    TgGuriParse* UtGuriParse;

    UgUriExport = g_uri_parse(VcUriExport, G_URI_FLAGS_NONE, NULL);

    if (! UgUriExport) return NULL;

    UtGuriParse = g_new0(TgGuriParse, 1);
    UtGuriParse->string = g_strdup(VcUriExport);

    VcGuriParse = g_uri_get_scheme(UgUriExport);
    UtGuriParse->scheme = VcGuriParse ? g_strdup(VcGuriParse) : NULL;

    VcGuriParse = g_uri_get_userinfo(UgUriExport);
    UtGuriParse->userinfo = VcGuriParse ? g_strdup(VcGuriParse) : NULL;

    VcGuriParse = g_uri_get_host(UgUriExport);
    UtGuriParse->host = VcGuriParse ? g_strdup(VcGuriParse) : NULL;

    UtGuriParse->port = g_uri_get_port(UgUriExport) ;

    VcGuriParse = g_uri_get_path(UgUriExport);
    UtGuriParse->path = VcGuriParse && *VcGuriParse == '/'
        ? g_strdup(VcGuriParse + 1) : g_strdup("");

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

    if (! UtGuriFree) return;

    g_free(UtGuriFree->string);
    g_free(UtGuriFree->scheme);
    g_free(UtGuriFree->userinfo);
    g_free(UtGuriFree->host);
    g_free(UtGuriFree->path);
    g_free(UtGuriFree->query);
    g_free(UtGuriFree->fragment);
    g_free(UtGuriFree->uri);
    g_free(UtGuriFree);
}


    void
FvUriPrint(char* VcUriPrint)
{
    TgGuriParse* UtUriPrint;

    UtUriPrint = FtGuriParse(VcUriPrint);

    if (! UtUriPrint) return;

    printf("\n");
    printf("uri         %s\n", UtUriPrint->uri);
    printf("scheme      %s\n", UtUriPrint->scheme);
    printf("host        %s\n", UtUriPrint->host);
    printf("port        %d\n", UtUriPrint->port);
    printf("path        %s\n", UtUriPrint->path);
    printf("query       %s\n", UtUriPrint->query);
    printf("fragment    %s\n", UtUriPrint->fragment);

    FvGuriFree(UtUriPrint);
}

