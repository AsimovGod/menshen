// PartTab.c.h



struct SaGtkTab {
    // link
    SaGtkUri* GtkUri;
    SaGtkMime* GtkMime;
    SaGtkTabStack* Stack;
    SaGtkTabPaned* Paned;
    SaGtkTabGrid* Grid;
    SaGtkTabScroll* Scroll;
};


struct SaGtkTabPaned {
    // gtk.h widget paned
    GtkWidget* base;
    GtkWidget* baseLeft;
    GtkWidget* baseRight;
    // declaration
    double baseR;
    double baseLeftR;
    double baseRightR;
};


struct SaGtkTabScroll {
    // gtk.h widget scroll
    GtkWidget* uriParse;
    GtkWidget* uriBuild;
    GtkWidget* mimeList;
    GtkWidget* mimeOpen;
};


struct SaGtkTabGrid {
    // gtk.h widget grid
    GtkWidget* uriParse;
    GtkWidget* uriBuild;
    GtkWidget* mimeList;
    GtkWidget* mimeOpen;
};



    void
FvGtkTab(SaMap* CsMap, char* AcUri)
{
    // declaration
    SaGtkTab* CsGtkTab;

    // malloc
    CsGtkTab = g_new0(SaGtkTab, 1);
    CsGtkTab->Paned = g_new0(SaGtkTabPaned, 1);
    CsGtkTab->Grid = g_new0(SaGtkTabGrid, 1);
    CsGtkTab->Scroll = g_new0(SaGtkTabScroll, 1);

    // gtk.h new
    CsGtkTab->Paned->base = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    CsGtkTab->Paned->baseLeft = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    CsGtkTab->Paned->baseRight = gtk_paned_new(GTK_ORIENTATION_VERTICAL);

    // variable
    CsGtkTab->Paned->baseR = 0.8;
    CsGtkTab->Paned->baseLeftR = 0.2;
    CsGtkTab->Paned->baseRightR = 0.6;

    // PartTabStack.c.h
    CsGtkTab->Stack = FsGtkTabStack(CsMap, CsGtkTab);

    // bequeath
    CsMap->GtkTab = CsGtkTab;

    // gobject.h data
    g_object_set_data_full(G_OBJECT(CsGtkTab->Paned->base),
            "CsGtkTab", CsGtkTab, (GDestroyNotify)FvGtkTabFree);

    // gtk.h layout
    gtk_paned_set_start_child(GTK_PANED(CsGtkTab->Paned->base),
            CsGtkTab->Paned->baseLeft);
    gtk_paned_set_end_child(GTK_PANED(CsGtkTab->Paned->base),
            CsGtkTab->Paned->baseRight);

    // gtk.h property
    gtk_paned_set_position(GTK_PANED(CsGtkTab->Paned->base),
            CsGtkTab->Paned->baseR * CsMap->GtkWindow->baseW);
    gtk_paned_set_position(GTK_PANED(CsGtkTab->Paned->baseLeft),
            CsGtkTab->Paned->baseLeftR * CsMap->GtkWindow->baseH);
    gtk_paned_set_position(GTK_PANED(CsGtkTab->Paned->baseRight),
            CsGtkTab->Paned->baseRightR * CsMap->GtkWindow->baseH);

    gtk_widget_set_valign(CsGtkTab->Paned->base, GTK_ALIGN_FILL);
    gtk_widget_set_halign(CsGtkTab->Paned->base, GTK_ALIGN_FILL);
    gtk_widget_set_valign(CsGtkTab->Paned->baseLeft, GTK_ALIGN_FILL);
    gtk_widget_set_halign(CsGtkTab->Paned->baseLeft, GTK_ALIGN_FILL);
    gtk_widget_set_valign(CsGtkTab->Paned->baseRight, GTK_ALIGN_FILL);
    gtk_widget_set_halign(CsGtkTab->Paned->baseRight, GTK_ALIGN_FILL);

    // PartUri.c.h
    FvGtkUri(CsMap, AcUri);

    // PartMime.c.h
    FvGtkMime(CsMap);

    // PartTabStack.c.h
    FvGtkWindowStackScroll(NULL, CsMap);
}


    void
FvGtkTabFree(void* PvFree)
{
    // declaration
    SaGtkTab* CsGtkTab;

    // inherit
    CsGtkTab = PvFree;

    if (! CsGtkTab) return;

    // free
    g_free(CsGtkTab->Stack);
    g_free(CsGtkTab->Paned);
    g_free(CsGtkTab->Grid);
    g_free(CsGtkTab->Scroll);
    g_free(CsGtkTab);
}

