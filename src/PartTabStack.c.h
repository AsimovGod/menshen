// PartTabStack.c.h



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



    SaGtkTabStack*
FsGtkTabStack(SaMap* CsMap, SaGtkTab* CsGtkTab)
{
    // declaration
    SaGtkWindow* CsGtkWindow;

    // inherit
    CsGtkWindow = CsMap->GtkWindow;

    // malloc
    CsGtkTab->Stack = g_new0(SaGtkTabStack, 1);

    // variable
    CsGtkWindow->Stack->number = CsGtkWindow->Stack->number + 1;
    CsGtkTab->Stack->toggle = FALSE;
    CsGtkTab->Stack->name = g_strdup_printf("PAGE %d",
            CsGtkWindow->Stack->number);

    // gtk.h new
    CsGtkTab->Stack->gridTitle = gtk_grid_new();
    CsGtkTab->Stack->frameTitle = gtk_frame_new(NULL);
    CsGtkTab->Stack->buttonSwitch = gtk_toggle_button_new_with_label(
            CsGtkTab->Stack->name);
    CsGtkTab->Stack->buttonRemove = gtk_button_new_from_icon_name(
            "window-close");

    // bequeath
    CsMap->GtkTab = CsGtkTab;

    // gobject.h data
    g_object_set_data_full(G_OBJECT(CsGtkTab->Paned->base),
            "CsGtkTab->Stack->name", CsGtkTab->Stack->name,
            (GDestroyNotify)g_free);

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
    gtk_button_set_label(GTK_BUTTON(CsGtkWindow->Stack->count),
            g_strdup_printf("%d", CsGtkWindow->Stack->counter));
    gtk_button_set_has_frame(GTK_BUTTON(CsGtkTab->Stack->buttonSwitch), FALSE);
    gtk_button_set_has_frame(GTK_BUTTON(CsGtkTab->Stack->buttonRemove), FALSE);
    gtk_toggle_button_set_active(
            GTK_TOGGLE_BUTTON(CsGtkTab->Stack->buttonSwitch), TRUE);

    // PartWindowStack.c.h
    FvGtkWindowStackCount(CsMap, 1);

    // return
    return CsGtkTab->Stack;
}


    gboolean
FgGtkTabStackScroll(void* PvUserdata)
{
    // declaration
    SaMap* CsMap;
    SaGtkWindow* CsGtkWindow;
    SaGtkTab* CsGtkTab;
    int DiFrameX;
    int DiFrameW;
    double DfScrollW;
    double DfScrollC;
    bool DbFrameR;
    graphene_rect_t EgFrameR;
    GtkWidget* EgPaned;

    // inherit
    CsMap = PvUserdata;

    if (! CsMap) return G_SOURCE_REMOVE;

    CsGtkWindow = CsMap->GtkWindow;

    // variable gtk.h stack
    EgPaned = gtk_stack_get_visible_child(GTK_STACK(CsGtkWindow->Stack->base));

    // gobject.h data get
    CsGtkTab = EgPaned ? g_object_get_data(G_OBJECT(EgPaned), "CsGtkTab") : NULL;

    if (! CsGtkTab) return G_SOURCE_REMOVE;

    // variable pointer
    DbFrameR = gtk_widget_compute_bounds(CsGtkTab->Stack->frameTitle,
            CsGtkWindow->Stack->tabbar, &EgFrameR);

    if (! DbFrameR) return G_SOURCE_REMOVE;

    // variable
    DiFrameW = gtk_widget_get_width(CsGtkTab->Stack->frameTitle);
    DiFrameX = graphene_rect_get_x(&EgFrameR);
    DfScrollW = gtk_adjustment_get_page_size(CsGtkWindow->Stack->scrollAH);
    DfScrollC = DiFrameX + (DiFrameW / 2.0) - (DfScrollW / 2.0);

    // gtk.h property
    gtk_adjustment_set_value(CsGtkWindow->Stack->scrollAH, DfScrollC);

    // return
    return G_SOURCE_REMOVE;
}

