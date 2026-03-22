// PartTabManage.cpp


// MainInclude.hpp
#include "MainInclude.hpp"




    void
FvGtkTabNew(GtkWidget* EgButton, void* PvUserdata)
{
    // declaration
    SaMap* CsMap;

    // inherit
    CsMap = PvUserdata;

    // PartTab.cpp
    FvGtkTab(CsMap, NULL);

    // PartTabStack.cpp
    FvGtkWindowStackScroll(NULL, CsMap);
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
    gtk_stack_set_visible_child_name(GTK_STACK(CsGtkWindow->Stack->base),
            CsGtkTab->Stack->name);

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
    SaGtkTab* CsGtkTabPrev;
    SaGtkTab* CsGtkTabNext;
    GtkWidget* EgPanedDel;
    GtkWidget* EgPanedNow;
    GtkWidget* EgPanedPrev;
    GtkWidget* EgPanedNext;

    // inherit
    CsMap = PvUserdata;

    if (! CsMap) return;

    CsGtkWindow = CsMap->GtkWindow;

    // branch inhert
    CsGtkTab = g_object_get_data(G_OBJECT(EgButton), "CsGtkTab");

    if (! CsGtkTab) return;

    // bequeath
    CsMap->GtkTab = CsGtkTab;

    // variable gtk.h stack
    EgPanedNow = gtk_stack_get_visible_child(
            GTK_STACK(CsGtkWindow->Stack->base));
    EgPanedDel = gtk_stack_get_child_by_name(
            GTK_STACK(CsGtkWindow->Stack->base), CsGtkTab->Stack->name);
    EgPanedPrev = gtk_widget_get_prev_sibling(EgPanedNow);
    EgPanedNext = gtk_widget_get_next_sibling(EgPanedNow);

    // gobject.h data get
    CsGtkTabPrev = EgPanedPrev
        ? g_object_get_data(G_OBJECT(EgPanedPrev), "CsGtkTab") : NULL;
    CsGtkTabNext = EgPanedNext
        ? g_object_get_data(G_OBJECT(EgPanedNext), "CsGtkTab") : NULL;

    // gtk.h layout
    gtk_stack_remove(GTK_STACK(CsGtkWindow->Stack->base),
            EgPanedDel);

    gtk_box_remove(GTK_BOX(CsGtkWindow->Stack->tabbar),
            CsGtkTab->Stack->frameTitle);

    // PartWindowStack.cpp
    FvGtkWindowStackCount(CsMap, -1);

    // PartTabPage.cpp
    if (CsMap->GtkWindow->Stack->counter < 1) {
        FvGtkTabNew(NULL, CsMap);
    }
    else if (EgPanedDel != EgPanedNow) (void)0;
    else if (CsGtkTabPrev) {
        FvGtkTabSwitch(CsGtkTabPrev->Stack->buttonSwitch, CsMap);
    }
    else if (CsGtkTabNext) {
        FvGtkTabSwitch(CsGtkTabNext->Stack->buttonSwitch, CsMap);
    }

    // PartTabStack.cpp
    FvGtkWindowStackScroll(NULL, CsMap);
}

