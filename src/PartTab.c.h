// PartTab.c.h



struct SaGtkTab {
    SaGtkUri* GtkUri;
    SaGtkMime* GtkMime;
    SaGtkTabPaned* Paned;
    SaGtkTabGrid* Grid;
    SaGtkTabScroll* Scroll;
    SaGtkTabButton* Button;
    char* name;
};


struct SaGtkTabGrid {
    GtkWidget* tabTitle;
    GtkWidget* uriParse;
    GtkWidget* uriBuild;
    GtkWidget* mimeList;
    GtkWidget* mimeOpen;
};


struct SaGtkTabButton {
    GtkWidget* title;
    GtkWidget* close;
};



    void
FvGtkTab(SaMap* CsMap, char* AcUri)
{
    SaGtkWindow* CsGtkWindow;
    SaGtkTab* CsGtkTab;

    CsGtkWindow = CsMap->GtkWindow;

    CsGtkTab = g_new0(SaGtkTab, 1);
    CsGtkTab->Grid = g_new0(SaGtkTabGrid, 1);
    CsGtkTab->Button = g_new0(SaGtkTabButton, 1);

    CsGtkWindow->Stack->counter = CsGtkWindow->Stack->counter + 1;
    CsGtkTab->name = g_strdup_printf("PAGE %d", CsGtkWindow->Stack->counter);
    CsGtkTab->Grid->tabTitle = gtk_grid_new();
    CsGtkTab->Button->title = gtk_button_new_with_label(CsGtkTab->name);
    CsGtkTab->Button->close = gtk_button_new_from_icon_name("window-close");

    CsMap->GtkTab = CsGtkTab;

    g_object_set_data(G_OBJECT(CsGtkTab->Button->title),
            "CsGtkTab", CsGtkTab);
    g_object_set_data(G_OBJECT(CsGtkTab->Button->close),
            "CsGtkTab", CsGtkTab);

    gtk_grid_attach(GTK_GRID(CsGtkTab->Grid->tabTitle), CsGtkTab->Button->title,
            0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(CsGtkTab->Grid->tabTitle), CsGtkTab->Button->close,
            1, 0, 1, 1);

    g_signal_connect(CsGtkTab->Button->title,
            "clicked", G_CALLBACK(FvGtkTabSwitch), CsMap);
    g_signal_connect(CsGtkTab->Button->close,
            "clicked", G_CALLBACK(FvGtkTabClose), CsMap);

    FvGtkTabWidget(CsMap, AcUri);
}


    void
FvGtkTabNew(GtkWidget* EgButton, void* PvUserdata)
{
    SaMap* CsMap;

    CsMap = PvUserdata;

    FvGtkTab(CsMap, NULL);
}


    void
FvGtkTabFree(void* PvFree)
{
    SaGtkTab* CsGtkTab;

    CsGtkTab = PvFree;

    if (! CsGtkTab) return;

    g_free(CsGtkTab->Paned);
    g_free(CsGtkTab->Grid);
    g_free(CsGtkTab->Scroll);
    g_free(CsGtkTab->Button);
    g_free(CsGtkTab->name);
    g_free(CsGtkTab);
}

