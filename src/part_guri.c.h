// part_guri.c.h



    SaGuriParse*
FsGuriParse(const char* AcBuild)
{
    SaGuriParse* CsParse;
    const char* AcParse;
    GUri* EgGuri;

    EgGuri = g_uri_parse(AcBuild, G_URI_FLAGS_NONE, NULL);

    if (! EgGuri) return NULL;

    CsParse = g_new0(SaGuriParse, 1);
    CsParse->string = g_strdup(AcBuild);

    AcParse = g_uri_get_scheme(EgGuri);
    CsParse->scheme = AcParse ? g_strdup(AcParse) : NULL;

    AcParse = g_uri_get_userinfo(EgGuri);
    CsParse->userinfo = AcParse ? g_strdup(AcParse) : NULL;

    AcParse = g_uri_get_host(EgGuri);
    CsParse->host = AcParse ? g_strdup(AcParse) : NULL;

    CsParse->port = g_uri_get_port(EgGuri) ;

    AcParse = g_uri_get_path(EgGuri);
    CsParse->path = AcParse && *AcParse == '/'
        ? g_strdup(AcParse + 1) : g_strdup("");

    AcParse = g_uri_get_query(EgGuri);
    CsParse->query = AcParse ? g_strdup(AcParse) : NULL;

    AcParse = g_uri_get_fragment(EgGuri);
    CsParse->fragment = AcParse ? g_strdup(AcParse) : NULL;

    AcParse = FaGuriBuild(CsParse);
    CsParse->uri = AcParse ? g_strdup(AcParse) : NULL;

    if (EgGuri) g_uri_unref(EgGuri);

    return CsParse;
}


    char*
FaGuriBuild(SaGuriParse* CsParse)
{
    char* AcBuild;
    char* AcParsePath;
    GUri* EgGuri;

    EgGuri = NULL;
    AcParsePath = NULL;

    if (CsParse->scheme && *CsParse->scheme) {
        AcParsePath = CsParse->path && *CsParse->path
            ? g_strconcat("/", CsParse->path, NULL) : g_strdup("");

        EgGuri = g_uri_build(G_URI_FLAGS_NONE,
                CsParse->scheme,

                CsParse->userinfo && *CsParse->userinfo
                ? CsParse->userinfo : NULL,

                CsParse->host && *CsParse->host
                ? CsParse->host : NULL,

                CsParse->port ? CsParse->port : -1,

                AcParsePath,

                CsParse->query && *CsParse->query
                ? CsParse->query : NULL,

                CsParse->fragment && *CsParse->fragment
                ? CsParse->fragment : NULL);

        AcBuild = g_uri_to_string(EgGuri ? EgGuri : NULL);
    }
    else {
        AcBuild = g_strdup("");
    }

    if (AcParsePath && *AcParsePath) g_free(AcParsePath);
    if (EgGuri) g_uri_unref(EgGuri);

    return AcBuild;
}


    void
FvUriPrint(int DiArgument, char** TcArgument)
{
    SaGuriParse* CsUri;
    int DiLoop;

    for (DiLoop = 1; DiLoop < DiArgument; DiLoop++) {
        CsUri = FsGuriParse(TcArgument[DiLoop]);

        if (! CsUri) continue;

        printf("\n");
        printf("URI         %s\n", CsUri->uri);
        printf("Scheme      %s\n", CsUri->scheme);
        printf("Userinfo    %s\n", CsUri->userinfo);
        printf("Host        %s\n", CsUri->host);
        printf("Port        %d\n", CsUri->port);
        printf("Path        %s\n", CsUri->path);
        printf("Query       %s\n", CsUri->query);
        printf("Fragment    %s\n", CsUri->fragment);

        FvGuriFree(CsUri);
    }
}


    void
FvGuriFree(void* PvFree)
{
    SaGuriParse* CsParse;

    CsParse = PvFree;

    if (! CsParse) return;

    g_free(CsParse->string);
    g_free(CsParse->scheme);
    g_free(CsParse->userinfo);
    g_free(CsParse->host);
    g_free(CsParse->path);
    g_free(CsParse->query);
    g_free(CsParse->fragment);
    g_free(CsParse->uri);
    g_free(CsParse);
}

