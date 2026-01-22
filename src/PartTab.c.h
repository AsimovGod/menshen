// PartTab.c.h



struct SaGtkTab {
    SaGtkUri* GtkUri;
    SaGtkMime* GtkMime;
    SaGtkTabStack* Stack;
    SaGtkTabPaned* Paned;
    SaGtkTabGrid* Grid;
    SaGtkTabScroll* Scroll;
};


struct SaGtkTabStack {
    char* name;
    bool toggle;
    GtkWidget* gridTitle;
    GtkWidget* buttonSwitch;
    GtkWidget* buttonRemove;
};


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


struct SaGtkTabGrid {
    GtkWidget* uriParse;
    GtkWidget* uriBuild;
    GtkWidget* mimeList;
    GtkWidget* mimeOpen;
};



    void
FvGtkTab(SaMap* CsMap, char* AcUri)
{
    SaGtkWindow* CsGtkWindow;
    SaGtkTab* CsGtkTab;

    CsGtkWindow = CsMap->GtkWindow;

    CsGtkTab = g_new0(SaGtkTab, 1);
    CsGtkTab->Stack = g_new0(SaGtkTabStack, 1);
    CsGtkTab->Grid = g_new0(SaGtkTabGrid, 1);
    CsGtkTab->Paned = g_new0(SaGtkTabPaned, 1);
    CsGtkTab->Scroll = g_new0(SaGtkTabScroll, 1);

    CsGtkWindow->Stack->counter = CsGtkWindow->Stack->counter + 1;
    CsGtkTab->Stack->name = g_strdup_printf("PAGE %d",
            CsGtkWindow->Stack->counter);
    CsGtkTab->Stack->toggle = FALSE;
    CsGtkTab->Stack->gridTitle = gtk_grid_new();
    CsGtkTab->Stack->buttonSwitch = gtk_toggle_button_new_with_label(
            CsGtkTab->Stack->name);
    CsGtkTab->Stack->buttonRemove = gtk_button_new_from_icon_name(
            "window-close");
    CsGtkTab->Paned->base = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);

    CsMap->GtkTab = CsGtkTab;

    g_object_set_data_full(G_OBJECT(CsGtkTab->Paned->base),
            "CsGtkTab", CsGtkTab, (GDestroyNotify)FvGtkTabFree);

    g_object_set_data(G_OBJECT(CsGtkTab->Stack->buttonSwitch),
            "CsGtkTab", CsGtkTab);
    g_object_set_data(G_OBJECT(CsGtkTab->Stack->buttonRemove),
            "CsGtkTab", CsGtkTab);

    gtk_stack_add_named(GTK_STACK(CsGtkWindow->Stack->base),
            CsGtkTab->Paned->base, CsGtkTab->Stack->name);
    gtk_box_append(GTK_BOX(CsGtkWindow->Stack->tabbar),
            CsGtkTab->Stack->gridTitle);
    gtk_grid_attach(GTK_GRID(CsGtkTab->Stack->gridTitle),
            CsGtkTab->Stack->buttonSwitch,
            0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(CsGtkTab->Stack->gridTitle),
            CsGtkTab->Stack->buttonRemove,
            1, 0, 1, 1);

    g_signal_connect(CsGtkTab->Stack->buttonSwitch,
            "toggled", G_CALLBACK(FvGtkTabSwitch), CsMap);
    g_signal_connect(CsGtkTab->Stack->buttonRemove,
            "clicked", G_CALLBACK(FvGtkTabRemove), CsMap);

    gtk_widget_add_css_class(CsGtkTab->Stack->buttonSwitch, "linked");
    gtk_widget_add_css_class(CsGtkTab->Stack->buttonRemove, "linked");
    gtk_toggle_button_set_active(
            GTK_TOGGLE_BUTTON(CsGtkTab->Stack->buttonSwitch), TRUE);

    FvGtkTabSwitch(CsGtkTab->Stack->buttonSwitch, CsMap);
    FvGtkTabPage(CsMap, AcUri);
}


    void
FvGtkTabFree(void* PvFree)
{
    SaGtkTab* CsGtkTab;

    CsGtkTab = PvFree;

    if (! CsGtkTab) return;

    g_free(CsGtkTab->Stack->name);
    g_free(CsGtkTab->Stack);
    g_free(CsGtkTab->Paned);
    g_free(CsGtkTab->Grid);
    g_free(CsGtkTab->Scroll);
    g_free(CsGtkTab);
}

