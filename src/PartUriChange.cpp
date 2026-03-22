// PartUriChange.cpp


// MainInclude.hpp
#include "MainInclude.hpp"



    void
FvGtkUriEntryBuild(GtkEditable* EgEditable, void* PvUserdata)
{
    // declaration
    SaGtkUri* CsGtkUri;
    int DiPort;
    char* AcText;

    // inherit
    CsGtkUri = PvUserdata;

    if ((! CsGtkUri->Entry) || CsGtkUri->change) return;

    // lock on
    CsGtkUri->change = TRUE;

    // free pre
    if (CsGtkUri->Parse->scheme) g_free(CsGtkUri->Parse->scheme);
    if (CsGtkUri->Parse->userinfo) g_free(CsGtkUri->Parse->userinfo);
    if (CsGtkUri->Parse->host) g_free(CsGtkUri->Parse->host);
    if (CsGtkUri->Parse->path) g_free(CsGtkUri->Parse->path);
    if (CsGtkUri->Parse->query) g_free(CsGtkUri->Parse->query);
    if (CsGtkUri->Parse->fragment) g_free(CsGtkUri->Parse->fragment);

    // PartUriChange.cpp
    CsGtkUri->Parse->scheme = FaGtkUriEntryGet(CsGtkUri->Entry->scheme);
    CsGtkUri->Parse->userinfo = FaGtkUriEntryGet(CsGtkUri->Entry->userinfo);
    CsGtkUri->Parse->host = FaGtkUriEntryGet(CsGtkUri->Entry->host);
    CsGtkUri->Parse->path = FaGtkUriEntryGet(CsGtkUri->Entry->path);
    CsGtkUri->Parse->query = FaGtkUriEntryGet(CsGtkUri->Entry->query);
    CsGtkUri->Parse->fragment = FaGtkUriEntryGet(CsGtkUri->Entry->fragment);

    // variable gtk.h
    DiPort = (int)gtk_spin_button_get_value(
            GTK_SPIN_BUTTON(CsGtkUri->Entry->port));

    // variable
    CsGtkUri->Parse->port = DiPort ? DiPort : -1;

    // PartGuri.cpp
    AcText = FaGuriBuild(CsGtkUri->Parse);

    // gtk.h widget
    gtk_editable_set_text(GTK_EDITABLE(CsGtkUri->Entry->uri),
            AcText ? AcText : "");

    // free post
    if (AcText) g_free(AcText);

    // lock off
    CsGtkUri->change = FALSE;
}


    void
FvGtkUriEntryParse(GtkEditable* EgEditable, void* PvUserdata)
{
    // declaration
    SaGtkUri* CsGtkUri;
    SaGuriParse* CsUriParse;
    const char* AcText;

    // inherit
    CsGtkUri = PvUserdata;

    if ((! CsGtkUri->Entry) || CsGtkUri->change) return;

    // lock on
    CsGtkUri->change = TRUE;

    if (CsGtkUri->Parse) g_free(CsGtkUri->Parse);

    // variable gtk.h
    AcText = gtk_editable_get_text(EgEditable);

    // PartGuri.cpp
    CsUriParse = FsGuriParse(AcText ? AcText : NULL);

    // variable glib.h
    CsGtkUri->Parse = CsUriParse ? CsUriParse : g_new0(SaGuriParse, 1);

    // PartUriChange.cpp
    FvGtkUriEntrySet(CsGtkUri->Entry->scheme, CsGtkUri->Parse->scheme);
    FvGtkUriEntrySet(CsGtkUri->Entry->userinfo, CsGtkUri->Parse->userinfo);
    FvGtkUriEntrySet(CsGtkUri->Entry->host, CsGtkUri->Parse->host);
    FvGtkUriEntrySet(CsGtkUri->Entry->path, CsGtkUri->Parse->path);
    FvGtkUriEntrySet(CsGtkUri->Entry->query, CsGtkUri->Parse->query);
    FvGtkUriEntrySet(CsGtkUri->Entry->fragment, CsGtkUri->Parse->fragment);

    // gtk.h widget
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(CsGtkUri->Entry->port),
            CsGtkUri->Parse->port ? CsGtkUri->Parse->port : -1);

    // lock off
    CsGtkUri->change = FALSE;
}


    char*
FaGtkUriEntryGet(GtkWidget* EgEntry)
{
    // declaration
    const char* AcParse;

    // variable gtk.h
    AcParse = gtk_editable_get_text(GTK_EDITABLE(EgEntry));

    // return
    return AcParse && *AcParse ? g_strdup(AcParse) : g_strdup("");
}


    void
FvGtkUriEntrySet(GtkWidget* EgEntry, char* AcUriEntry)
{
    // gtk.h widget
    gtk_editable_set_text(GTK_EDITABLE(EgEntry), AcUriEntry ? AcUriEntry : "");
}

