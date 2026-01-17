#include <stdio.h>




    char*
FcGuriBuild(TgGuriParse* UtParse)
{
    char* VcBuild;
    char* VcParsePath;
    GUri* UgGuri;

    UgGuri = NULL;
    VcParsePath = NULL;

    if (UtParse->scheme && *UtParse->scheme) {
        VcParsePath = UtParse->path && *UtParse->path
            ? g_strconcat("/", UtParse->path, NULL) : g_strdup("");

        UgGuri = g_uri_build(G_URI_FLAGS_NONE,
                UtParse->scheme,
                UtParse->userinfo && *UtParse->userinfo
                ? UtParse->userinfo : NULL,
                UtParse->host && *UtParse->host
                ? UtParse->host : NULL,
                UtParse->port ? UtParse->port : -1,
                VcParsePath,
                UtParse->query && *UtParse->query
                ? UtParse->query : NULL,
                UtParse->fragment && *UtParse->fragment
                ? UtParse->fragment : NULL);

        VcBuild = g_uri_to_string(UgGuri ? UgGuri : NULL);
    }
    else {
        VcBuild = g_strdup("");
    }

    if (UgGuri) g_uri_unref(UgGuri);

    if (VcParsePath && *VcParsePath) g_free(VcParsePath);

    return VcBuild;
}


    TgGuriParse*
FtGuriParse(const char* VcBuild)
{
    const char* VcParse;
    GUri* UgGuri;
    TgGuriParse* UtParse;

    UgGuri = g_uri_parse(VcBuild, G_URI_FLAGS_NONE, NULL);

    if (! UgGuri) return NULL;

    UtParse = g_new0(TgGuriParse, 1);
    UtParse->string = g_strdup(VcBuild);

    VcParse = g_uri_get_scheme(UgGuri);
    UtParse->scheme = VcParse ? g_strdup(VcParse) : NULL;

    VcParse = g_uri_get_userinfo(UgGuri);
    UtParse->userinfo = VcParse ? g_strdup(VcParse) : NULL;

    VcParse = g_uri_get_host(UgGuri);
    UtParse->host = VcParse ? g_strdup(VcParse) : NULL;

    UtParse->port = g_uri_get_port(UgGuri) ;

    VcParse = g_uri_get_path(UgGuri);
    UtParse->path = VcParse && *VcParse == '/'
        ? g_strdup(VcParse + 1) : g_strdup("");

    VcParse = g_uri_get_query(UgGuri);
    UtParse->query = VcParse ? g_strdup(VcParse) : NULL;

    VcParse = g_uri_get_fragment(UgGuri);
    UtParse->fragment = VcParse ? g_strdup(VcParse) : NULL;

    VcParse = FcGuriBuild(UtParse);
    UtParse->uri = VcParse ? g_strdup(VcParse) : NULL;

    g_uri_unref(UgGuri);

    return UtParse;
}


    void
FvGuriFree(void* PvFree)
{
    TgGuriParse* UtParse;

    UtParse = PvFree;

    if (! UtParse) return;

    g_free(UtParse->string);
    g_free(UtParse->scheme);
    g_free(UtParse->userinfo);
    g_free(UtParse->host);
    g_free(UtParse->path);
    g_free(UtParse->query);
    g_free(UtParse->fragment);
    g_free(UtParse->uri);
    g_free(UtParse);
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
    printf("userinfo    %s\n", UtUriPrint->userinfo);
    printf("host        %s\n", UtUriPrint->host);
    printf("port        %d\n", UtUriPrint->port);
    printf("path        %s\n", UtUriPrint->path);
    printf("query       %s\n", UtUriPrint->query);
    printf("fragment    %s\n", UtUriPrint->fragment);

    FvGuriFree(UtUriPrint);
}

