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


struct SaGtkTabStack {
    // declaration property
    char* name;
    // declaration lock
    bool toggle;
    // gtk.h widget grid
    GtkWidget* gridTitle;
    GtkWidget* frameTitle;
    // gtk.h widget button
    GtkWidget* buttonSwitch;
    GtkWidget* buttonRemove;
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
    SaGtkWindow* CsGtkWindow;
    SaGtkTab* CsGtkTab;

    // inherit
    CsGtkWindow = CsMap->GtkWindow;

    // malloc
    CsGtkTab = g_new0(SaGtkTab, 1);
    CsGtkTab->Stack = g_new0(SaGtkTabStack, 1);
    CsGtkTab->Paned = g_new0(SaGtkTabPaned, 1);

    // variable
    CsGtkWindow->Stack->counter = CsGtkWindow->Stack->counter + 1;
    CsGtkTab->Stack->toggle = FALSE;
    CsGtkTab->Stack->name = g_strdup_printf("PAGE %d",
            CsGtkWindow->Stack->counter);

    // gtk.h new
    CsGtkTab->Stack->gridTitle = gtk_grid_new();
    CsGtkTab->Stack->frameTitle = gtk_frame_new(NULL);
    CsGtkTab->Stack->buttonSwitch = gtk_toggle_button_new_with_label(
            CsGtkTab->Stack->name);
    CsGtkTab->Stack->buttonRemove = gtk_button_new_from_icon_name(
            "window-close");
    CsGtkTab->Paned->base = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);

    // bequeath
    CsMap->GtkTab = CsGtkTab;

    // gobject.h data
    g_object_set_data_full(G_OBJECT(CsGtkTab->Paned->base),
            "CsGtkTab", CsGtkTab, (GDestroyNotify)FvGtkTabFree);

    g_object_set_data(G_OBJECT(CsGtkTab->Stack->buttonSwitch),
            "CsGtkTab", CsGtkTab);
    g_object_set_data(G_OBJECT(CsGtkTab->Stack->buttonRemove),
            "CsGtkTab", CsGtkTab);

    // gtk.h layout
    gtk_stack_add_named(GTK_STACK(CsGtkWindow->Stack->base),
            CsGtkTab->Paned->base, CsGtkTab->Stack->name);
    gtk_box_append(GTK_BOX(CsGtkWindow->Stack->tabbar),
            CsGtkTab->Stack->frameTitle);
    gtk_frame_set_child(GTK_FRAME(CsGtkTab->Stack->frameTitle),
            CsGtkTab->Stack->gridTitle);
    gtk_grid_attach(GTK_GRID(CsGtkTab->Stack->gridTitle),
            CsGtkTab->Stack->buttonSwitch,
            0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(CsGtkTab->Stack->gridTitle),
            CsGtkTab->Stack->buttonRemove,
            1, 0, 1, 1);

    // gobject.h signal
    g_signal_connect(CsGtkTab->Stack->buttonSwitch,
            "toggled", G_CALLBACK(FvGtkTabSwitch), CsMap);
    g_signal_connect(CsGtkTab->Stack->buttonRemove,
            "clicked", G_CALLBACK(FvGtkTabRemove), CsMap);

    // gtk.h property
    gtk_button_set_has_frame(GTK_BUTTON(CsGtkTab->Stack->buttonSwitch), FALSE);
    gtk_button_set_has_frame(GTK_BUTTON(CsGtkTab->Stack->buttonRemove), FALSE);
    gtk_toggle_button_set_active(
            GTK_TOGGLE_BUTTON(CsGtkTab->Stack->buttonSwitch), TRUE);

    // PartTabPage.h
    FvGtkTabPage(CsMap, AcUri);
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
    g_free(CsGtkTab->Stack->name);
    g_free(CsGtkTab->Stack);
    g_free(CsGtkTab->Paned);
    g_free(CsGtkTab->Grid);
    g_free(CsGtkTab->Scroll);
    g_free(CsGtkTab);
}

