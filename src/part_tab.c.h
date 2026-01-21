// part_tab.c.h



struct SaGtkTab {
    SaGtkPaned* Paned;
    SaGtkGrid* Grid;
    SaGtkScroll* Scroll;
    SaGtkButton* Button;
    char* name;
};


struct SaGtkPaned {
    GtkWidget* base;
    double baseR;
    GtkWidget* baseLeft;
    double baseLeftR;
    GtkWidget* baseRight;
    double baseRightR;
};


struct SaGtkGrid {
    GtkWidget* tabTitle;
    GtkWidget* uriParse;
    GtkWidget* uriBuild;
    GtkWidget* mimeList;
    GtkWidget* mimeOpen;
};


struct SaGtkScroll {
    GtkWidget* uriParse;
    GtkWidget* uriBuild;
    GtkWidget* mimeList;
    GtkWidget* mimeOpen;
};


struct SaGtkButton {
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
    CsGtkTab->Paned = g_new0(SaGtkPaned, 1);
    CsGtkTab->Grid = g_new0(SaGtkGrid, 1);
    CsGtkTab->Scroll = g_new0(SaGtkScroll, 1);
    CsGtkTab->Button = g_new0(SaGtkButton, 1);

    CsGtkWindow->Stack->counter = CsGtkWindow->Stack->counter + 1;
    CsGtkTab->name = g_strdup_printf("Page %d", CsGtkWindow->Stack->counter);
    CsGtkTab->Grid->tabTitle = gtk_grid_new();
    CsGtkTab->Button->title = gtk_button_new_with_label(CsGtkTab->name);
    CsGtkTab->Button->close = gtk_button_new_from_icon_name("window-close");
    CsGtkTab->Paned->base = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    CsGtkTab->Paned->baseLeft = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    CsGtkTab->Paned->baseRight = gtk_paned_new(GTK_ORIENTATION_VERTICAL);

    CsMap->GtkTab = CsGtkTab;

    g_object_set_data_full(G_OBJECT(CsMap->GtkWindow->base),
            "CsGtkTab", CsGtkTab, (GDestroyNotify)FvGtkTabFree);

    gtk_grid_attach(GTK_GRID(CsGtkTab->Grid->tabTitle), CsGtkTab->Button->title,
            0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(CsGtkTab->Grid->tabTitle), CsGtkTab->Button->close,
            1, 0, 1, 1);
    gtk_box_prepend(GTK_BOX(CsGtkWindow->Stack->barTab),
            CsGtkTab->Grid->tabTitle);
    gtk_stack_add_named(GTK_STACK(CsGtkWindow->Stack->base), 
            CsGtkTab->Paned->base, CsGtkTab->name);
    gtk_paned_set_start_child(GTK_PANED(CsGtkTab->Paned->base),
            CsGtkTab->Paned->baseLeft);
    gtk_paned_set_end_child(GTK_PANED(CsGtkTab->Paned->base),
            CsGtkTab->Paned->baseRight);

    g_signal_connect(CsGtkTab->Button->title,
            "clicked", G_CALLBACK(FvGtkTabSwitch), CsMap);
    g_signal_connect(CsGtkTab->Button->close,
            "clicked", G_CALLBACK(FvGtkTabClose), CsMap);

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
    CsGtkTab = CsMap->GtkTab;

    gtk_stack_set_visible_child_name(GTK_STACK(CsGtkWindow->Stack->base),
            CsMap->GtkTab->name);
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
    CsGtkTab = CsMap->GtkTab;

    EgPage = gtk_stack_get_child_by_name(GTK_STACK(CsGtkWindow->Stack->base),
            CsGtkTab->name);

    gtk_box_remove(GTK_BOX(CsGtkWindow->Stack->barTab),
            CsGtkTab->Grid->tabTitle);

    if (! CsMap->GtkTab->name) return;
    gtk_stack_remove(GTK_STACK(CsMap->GtkWindow->Stack->base), EgPage);
}


    void
FvGtkTabFree(void* PvFree)
{
    SaGtkTab* CsGtkTab;

    CsGtkTab = PvFree;

    if (! CsGtkTab) return;

    g_free(CsGtkTab->name);
    g_free(CsGtkTab->Paned);
    g_free(CsGtkTab->Grid);
    g_free(CsGtkTab->Scroll);
    g_free(CsGtkTab->Button);
    g_free(CsGtkTab);
}

