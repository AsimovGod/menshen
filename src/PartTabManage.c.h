// PartTabManage.c.h




    void
FvGtkTabNew(GtkWidget* EgButton, void* PvUserdata)
{
    // declaration
    SaMap* CsMap;

    // inherit
    CsMap = PvUserdata;

    // PartTab.c.h
    FvGtkTab(CsMap, NULL);
}


    void
FvGtkTabSwitch(GtkWidget* EgButton, void* PvUserdata)
{
    // declaration
    SaMap* CsMap;
    SaGtkWindow* CsGtkWindow;
    SaGtkTab* CsGtkTab;
    SaGtkTab* CsGtkTabToggle;
    GtkWidget* EgLoop;
    GtkWidget* EgLoopGrid;
    GtkWidget* EgLoopToggle;

    // inherit
    CsMap = PvUserdata;

    if (! CsMap) return;

    CsGtkWindow = CsMap->GtkWindow;

    // branch inhert
    CsGtkTab = g_object_get_data(G_OBJECT(EgButton), "CsGtkTab");

    if (! CsGtkTab) return;
    if (! CsGtkTab->Stack->name) return;
    if (CsGtkTab->Stack->toggle) return;

    // bequeath
    CsMap->GtkTab = CsGtkTab;

    // gtk.h button
    if (! gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(EgButton))) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(EgButton), TRUE);
        return;
    }

    // lock on
    CsGtkTab->Stack->toggle = TRUE;

    // loop gtk.h box
    for (EgLoop = gtk_widget_get_first_child(CsGtkWindow->Stack->tabbar);
            EgLoop != NULL; EgLoop = gtk_widget_get_next_sibling(EgLoop))
    {
        // block gtk.h box
        if (EgLoop == CsGtkTab->Stack->frameTitle) continue;
        // block gtk.h frame
        EgLoopGrid = gtk_frame_get_child(GTK_FRAME(EgLoop));
        if (! EgLoopGrid) continue;
        // block gtk.h grid
        EgLoopToggle = gtk_grid_get_child_at(GTK_GRID(EgLoopGrid), 0, 0);
        if (! EgLoopToggle) continue;
        // block veriable gobject.h
        CsGtkTabToggle = g_object_get_data(G_OBJECT(EgLoopToggle), "CsGtkTab");
        // block lock on
        CsGtkTabToggle->Stack->toggle = TRUE;
        // block gtk.h button
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(EgLoopToggle), FALSE);
        // block lock off
        CsGtkTabToggle->Stack->toggle = FALSE;
    }

    // gtk.h layout
    gtk_stack_set_visible_child(GTK_STACK(CsGtkWindow->Stack->base),
            CsGtkTab->Paned->base);

    // lock off
    CsGtkTab->Stack->toggle = FALSE;
}


    void
FvGtkTabRemove(GtkWidget* EgButton, void* PvUserdata)
{
    // declaration
    SaMap* CsMap;
    SaGtkWindow* CsGtkWindow;
    SaGtkTab* CsGtkTab;
    SaGtkTabStack* CsStackFirst;
    SaGtkTabStack* CsStackSecond;
    SaGtkTabStack* CsStackLast;
    GtkWidget* EgDelPaned;
    GtkWidget* EgNowPaned;

    // malloc
    CsStackFirst = g_new0(SaGtkTabStack, 1);
    CsStackSecond = g_new0(SaGtkTabStack, 1);
    CsStackLast = g_new0(SaGtkTabStack, 1);

    // inherit
    CsMap = PvUserdata;

    if (! CsMap) return;

    CsGtkWindow = CsMap->GtkWindow;

    EgNowPaned = gtk_stack_get_visible_child(
            GTK_STACK(CsGtkWindow->Stack->base));

    // gobject.h data get
    CsGtkTab = g_object_get_data(G_OBJECT(EgButton), "CsGtkTab");

    if (! CsGtkTab) return;
    if (! CsGtkTab->Stack->name) return;

    // bequeath
    CsMap->GtkTab = CsGtkTab;

    // variable gtk.h widget
    CsStackFirst->frameTitle = gtk_widget_get_first_child(
            CsGtkWindow->Stack->tabbar);
    CsStackSecond->frameTitle = gtk_widget_get_next_sibling(
            CsStackFirst->frameTitle);
    CsStackLast->frameTitle = gtk_widget_get_last_child(
            CsGtkWindow->Stack->tabbar);

    // variable gtk.h stack
    EgDelPaned = gtk_stack_get_child_by_name(
            GTK_STACK(CsGtkWindow->Stack->base), CsGtkTab->Stack->name);

    // gtk.h layout
    gtk_stack_remove(GTK_STACK(CsGtkWindow->Stack->base),
            EgDelPaned);

    gtk_box_remove(GTK_BOX(CsGtkWindow->Stack->tabbar),
            CsGtkTab->Stack->frameTitle);

    // gtk.h box
    if (CsStackFirst->frameTitle && CsStackSecond->frameTitle) {
        CsStackFirst->gridTitle = gtk_frame_get_child(
                GTK_FRAME(CsStackFirst->frameTitle));
        CsStackFirst->buttonSwitch = gtk_grid_get_child_at(
                GTK_GRID(CsStackFirst->gridTitle), 0, 0);
        CsStackSecond->gridTitle = gtk_frame_get_child(
                GTK_FRAME(CsStackSecond->frameTitle));
        CsStackSecond->buttonSwitch = gtk_grid_get_child_at(
                GTK_GRID(CsStackSecond->gridTitle), 0, 0);
    }

    // PartTabPage.c.h
    if (CsStackFirst->frameTitle == CsStackLast->frameTitle) {
        FvGtkTabNew(NULL, CsMap);
    }
    else if (EgDelPaned != EgNowPaned) {
        return;
    }
    else if (CsGtkTab->Stack->gridTitle == CsStackFirst->gridTitle) {
        FvGtkTabSwitch(CsStackSecond->buttonSwitch, CsMap);
    }
    else {
        FvGtkTabSwitch(CsStackFirst->buttonSwitch, CsMap);
    }
}

