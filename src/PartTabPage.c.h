// PartTabPage.c.h



struct SaGtkTabPaned {
    GtkWidget* base;
    double baseR;
    GtkWidget* baseLeft;
    double baseLeftR;
    GtkWidget* baseRight;
    double baseRightR;
};


struct SaGtkTabScroll {
    GtkWidget* uriParse;
    GtkWidget* uriBuild;
    GtkWidget* mimeList;
    GtkWidget* mimeOpen;
};



    void
FvGtkTabWidget(SaMap* CsMap, char* AcUri)
{
    SaGtkWindow* CsGtkWindow;
    SaGtkTab* CsGtkTab;

    CsGtkWindow = CsMap->GtkWindow;
    CsGtkTab = CsMap->GtkTab;

    CsGtkTab->Paned = g_new0(SaGtkTabPaned, 1);
    CsGtkTab->Scroll = g_new0(SaGtkTabScroll, 1);

    CsGtkTab->Paned->base = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    CsGtkTab->Paned->baseLeft = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    CsGtkTab->Paned->baseRight = gtk_paned_new(GTK_ORIENTATION_VERTICAL);

    g_object_set_data_full(G_OBJECT(CsGtkTab->Paned->base),
            "CsGtkTab", CsGtkTab, (GDestroyNotify)FvGtkTabFree);

    gtk_paned_set_start_child(GTK_PANED(CsGtkTab->Paned->base),
            CsGtkTab->Paned->baseLeft);
    gtk_paned_set_end_child(GTK_PANED(CsGtkTab->Paned->base),
            CsGtkTab->Paned->baseRight);

    gtk_stack_add_titled(GTK_STACK(CsGtkWindow->Stack->base),
            CsGtkTab->Paned->base,
            CsGtkTab->name, CsGtkTab->name);

    CsGtkTab->Paned->baseR = 0.8;
    CsGtkTab->Paned->baseLeftR = 0.2;
    CsGtkTab->Paned->baseRightR = 0.7;

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

    FvGtkUri(CsMap, AcUri);
    FvGtkMime(CsMap);
}


    void
FvGtkTabSwitch(GtkWidget* EgButton, void* PvUserdata)
{
    SaMap* CsMap;
    SaGtkWindow* CsGtkWindow;
    SaGtkTab* CsGtkTab;

    CsMap = PvUserdata;
    CsGtkWindow = CsMap->GtkWindow;
    CsGtkTab = g_object_get_data(G_OBJECT(EgButton), "CsGtkTab");

    if ((! CsGtkTab) || (! CsGtkTab->name)) return;

    gtk_stack_set_visible_child(GTK_STACK(CsGtkWindow->Stack->base),
            CsGtkTab->Paned->base);
}


    void
FvGtkTabClose(GtkWidget* EgButton, void* PvUserdata)
{
    SaMap* CsMap;
    SaGtkWindow* CsGtkWindow;
    SaGtkTab* CsGtkTab;
    GtkWidget* EgPage;

    CsMap = PvUserdata;
    CsGtkWindow = CsMap->GtkWindow;
    CsGtkTab = g_object_get_data(G_OBJECT(EgButton), "CsGtkTab");

    if ((! CsGtkTab) || (! CsGtkTab->name)) return;

    EgPage = gtk_stack_get_child_by_name(GTK_STACK(CsGtkWindow->Stack->base),
            CsGtkTab->name);

    gtk_stack_remove(GTK_STACK(CsGtkWindow->Stack->base),
            EgPage);

    gtk_box_remove(GTK_BOX(CsGtkWindow->Stack->tabbar),
            CsGtkTab->Grid->tabTitle);
}

