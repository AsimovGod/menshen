// PartGuri.cpp


// MainInclude.hpp
#include "MainInclude.hpp"



struct SaGuriParse {
    // declaration
    char* string;
    char* scheme;
    char* userinfo;
    char* host;
    int port;
    char* path;
    char* query;
    char* fragment;
    char* uri;
};



    SaGuriParse*
FsGuriParse(const char* AcBuild)
{
    // declaration
    SaGuriParse* CsParse;
    const char* AcParse;
    GUri* EgGuri;

    // gio.h uri
    EgGuri = g_uri_parse(AcBuild, G_URI_FLAGS_NONE, NULL);

    if (! EgGuri) return NULL;

    // malloc
    CsParse = g_new0(SaGuriParse, 1);

    // variable
    CsParse->string = g_strdup(AcBuild);

    // variable gio.h
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

    // PartGuri.cpp
    AcParse = FaGuriBuild(CsParse);

    // variable glib.h
    CsParse->uri = AcParse ? g_strdup(AcParse) : NULL;

    // free
    if (EgGuri) g_uri_unref(EgGuri);

    // return
    return CsParse;
}


    char*
FaGuriBuild(SaGuriParse* CsParse)
{
    // declaration
    char* AcBuild;
    char* AcParsePath;
    GUri* EgGuri;

    // variable
    EgGuri = NULL;
    AcParsePath = NULL;

    // if variable
    if (CsParse->scheme && *CsParse->scheme) {
        // block variable glib.h
        AcParsePath = CsParse->path && *CsParse->path
            ? g_strconcat("/", CsParse->path, NULL) : g_strdup("");
        // block gio.h
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
        // block variable gio.h
        AcBuild = g_uri_to_string(EgGuri ? EgGuri : NULL);
    }
    else {
        // variable string
        AcBuild = g_strdup("");
    }

    // free
    if (AcParsePath && *AcParsePath) g_free(AcParsePath);
    if (EgGuri) g_uri_unref(EgGuri);

    // return
    return AcBuild;
}


    void
FvUriPrint(int DiArgument, char** TcArgument)
{
    // declaration
    SaGuriParse* CsUri;
    int DiLoop;

    // loop argument
    for (DiLoop = 1; DiLoop < DiArgument; DiLoop++) {
        // block PartGuri.cpp
        CsUri = FsGuriParse(TcArgument[DiLoop]);
        if (! CsUri) continue;
        // block stdio.h printf
        printf("\n");
        printf("URI         %s\n", CsUri->uri);
        printf("Scheme      %s\n", CsUri->scheme);
        printf("Userinfo    %s\n", CsUri->userinfo);
        printf("Host        %s\n", CsUri->host);
        printf("Port        %d\n", CsUri->port);
        printf("Path        %s\n", CsUri->path);
        printf("Query       %s\n", CsUri->query);
        printf("Fragment    %s\n", CsUri->fragment);
        // block free
        FvGuriFree(CsUri);
    }
}


    void
FvGuriFree(void* PvFree)
{
    // declaration
    SaGuriParse* CsParse;

    // inherit
    CsParse = PvFree;

    if (! CsParse) return;

    // free
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

