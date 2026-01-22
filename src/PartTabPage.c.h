// PartTabPage.c.h




    void
FvGtkTabPage(SaMap* CsMap, char* AcUri)
{
    SaGtkWindow* CsGtkWindow;
    SaGtkTab* CsGtkTab;

    CsGtkWindow = CsMap->GtkWindow;
    CsGtkTab = CsMap->GtkTab;

    CsGtkTab->Paned->baseLeft = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    CsGtkTab->Paned->baseRight = gtk_paned_new(GTK_ORIENTATION_VERTICAL);

    gtk_paned_set_start_child(GTK_PANED(CsGtkTab->Paned->base),
            CsGtkTab->Paned->baseLeft);
    gtk_paned_set_end_child(GTK_PANED(CsGtkTab->Paned->base),
            CsGtkTab->Paned->baseRight);

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
FvGtkTabNew(GtkWidget* EgButton, void* PvUserdata)
{
    SaMap* CsMap;

    CsMap = PvUserdata;

    FvGtkTab(CsMap, NULL);
}


    void
FvGtkTabSwitch(GtkWidget* EgButton, void* PvUserdata)
{
    SaMap* CsMap;
    SaGtkWindow* CsGtkWindow;
    SaGtkTab* CsGtkTab;
    SaGtkTab* CsGtkTabToggle;
    GtkWidget* EgLoop;
    GtkWidget* EgLoopToggle;

    CsMap = PvUserdata;
    CsGtkWindow = CsMap->GtkWindow;
    CsGtkTab = g_object_get_data(G_OBJECT(EgButton), "CsGtkTab");

    if ( (! CsGtkTab) || CsGtkTab->Stack->toggle) return;

    if (! CsGtkTab->Stack->name) return;

    CsGtkTab->Stack->toggle = TRUE;

    if (! gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(EgButton))) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(EgButton), TRUE);
        return;
    }

    for (EgLoop = gtk_widget_get_first_child(CsGtkWindow->Stack->tabbar);
            EgLoop != NULL; EgLoop = gtk_widget_get_next_sibling(EgLoop))
    {
        EgLoopToggle = gtk_grid_get_child_at(GTK_GRID(EgLoop), 0, 0);
        if ((! EgLoopToggle) || (EgLoopToggle == EgButton)) continue;
        CsGtkTabToggle = g_object_get_data(G_OBJECT(EgLoopToggle), "CsGtkTab");
        CsGtkTabToggle->Stack->toggle = TRUE;
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(EgLoopToggle), FALSE);
        CsGtkTabToggle->Stack->toggle = FALSE;
    }

    gtk_stack_set_visible_child(GTK_STACK(CsGtkWindow->Stack->base),
            CsGtkTab->Paned->base);

    CsGtkTab->Stack->toggle = FALSE;
}


    void
FvGtkTabRemove(GtkWidget* EgButton, void* PvUserdata)
{
    SaMap* CsMap;
    SaGtkWindow* CsGtkWindow;
    SaGtkTab* CsGtkTab;
    GtkWidget* EgPage;

    CsMap = PvUserdata;
    CsGtkWindow = CsMap->GtkWindow;
    CsGtkTab = g_object_get_data(G_OBJECT(EgButton), "CsGtkTab");

    if ((! CsGtkTab) || (! CsGtkTab->Stack->name)) return;

    EgPage = gtk_stack_get_child_by_name(GTK_STACK(CsGtkWindow->Stack->base),
            CsGtkTab->Stack->name);

    gtk_stack_remove(GTK_STACK(CsGtkWindow->Stack->base),
            EgPage);

    gtk_box_remove(GTK_BOX(CsGtkWindow->Stack->tabbar),
            CsGtkTab->Stack->gridTitle);
}

