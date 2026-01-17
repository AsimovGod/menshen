// part_guri.h



    char*
FcGuriBuild(SuGuriParse* PsParse)
{
    char* VcBuild;
    char* VcParsePath;
    GUri* UgGuri;

    UgGuri = NULL;
    VcParsePath = NULL;

    if (PsParse->scheme && *PsParse->scheme) {
        VcParsePath = PsParse->path && *PsParse->path
            ? g_strconcat("/", PsParse->path, NULL) : g_strdup("");

        UgGuri = g_uri_build(G_URI_FLAGS_NONE,
                PsParse->scheme,
                PsParse->userinfo && *PsParse->userinfo
                ? PsParse->userinfo : NULL,
                PsParse->host && *PsParse->host
                ? PsParse->host : NULL,
                PsParse->port ? PsParse->port : -1,
                VcParsePath,
                PsParse->query && *PsParse->query
                ? PsParse->query : NULL,
                PsParse->fragment && *PsParse->fragment
                ? PsParse->fragment : NULL);

        VcBuild = g_uri_to_string(UgGuri ? UgGuri : NULL);
    }
    else {
        VcBuild = g_strdup("");
    }

    if (UgGuri) g_uri_unref(UgGuri);

    if (VcParsePath && *VcParsePath) g_free(VcParsePath);

    return VcBuild;
}


    SuGuriParse*
FtGuriParse(const char* VcBuild)
{
    const char* VcParse;
    GUri* UgGuri;
    SuGuriParse* PsParse;

    UgGuri = g_uri_parse(VcBuild, G_URI_FLAGS_NONE, NULL);

    if (! UgGuri) return NULL;

    PsParse = g_new0(SuGuriParse, 1);
    PsParse->string = g_strdup(VcBuild);

    VcParse = g_uri_get_scheme(UgGuri);
    PsParse->scheme = VcParse ? g_strdup(VcParse) : NULL;

    VcParse = g_uri_get_userinfo(UgGuri);
    PsParse->userinfo = VcParse ? g_strdup(VcParse) : NULL;

    VcParse = g_uri_get_host(UgGuri);
    PsParse->host = VcParse ? g_strdup(VcParse) : NULL;

    PsParse->port = g_uri_get_port(UgGuri) ;

    VcParse = g_uri_get_path(UgGuri);
    PsParse->path = VcParse && *VcParse == '/'
        ? g_strdup(VcParse + 1) : g_strdup("");

    VcParse = g_uri_get_query(UgGuri);
    PsParse->query = VcParse ? g_strdup(VcParse) : NULL;

    VcParse = g_uri_get_fragment(UgGuri);
    PsParse->fragment = VcParse ? g_strdup(VcParse) : NULL;

    VcParse = FcGuriBuild(PsParse);
    PsParse->uri = VcParse ? g_strdup(VcParse) : NULL;

    g_uri_unref(UgGuri);

    return PsParse;
}


    void
FvGuriFree(void* PvFree)
{
    SuGuriParse* PsParse;

    PsParse = PvFree;

    if (! PsParse) return;

    g_free(PsParse->string);
    g_free(PsParse->scheme);
    g_free(PsParse->userinfo);
    g_free(PsParse->host);
    g_free(PsParse->path);
    g_free(PsParse->query);
    g_free(PsParse->fragment);
    g_free(PsParse->uri);
    g_free(PsParse);
}


    void
FvUriPrint(char* VcUriPrint)
{
    SuGuriParse* PsUriPrint;

    PsUriPrint = FtGuriParse(VcUriPrint);

    if (! PsUriPrint) return;

    printf("\n");
    printf("uri         %s\n", PsUriPrint->uri);
    printf("scheme      %s\n", PsUriPrint->scheme);
    printf("userinfo    %s\n", PsUriPrint->userinfo);
    printf("host        %s\n", PsUriPrint->host);
    printf("port        %d\n", PsUriPrint->port);
    printf("path        %s\n", PsUriPrint->path);
    printf("query       %s\n", PsUriPrint->query);
    printf("fragment    %s\n", PsUriPrint->fragment);

    FvGuriFree(PsUriPrint);
}

