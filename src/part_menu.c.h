// part_menu.h



void FvGtkBase(GtkApplication* EgApplication, SaMap* CsMap, char** TcArgument);


    void
FvGtkMenuNewwindow(GSimpleAction* EgSimpleaction, GVariant* EgVariant,
        void* PvUserdata)
{
    SaMap* CsMap;

    CsMap = PvUserdata;

    FvGtkBase(GTK_APPLICATION(CsMap->application), CsMap, NULL);
}


    void
FvGtkMenuAbout(GSimpleAction* EgSimpleaction, GVariant* EgVariant,
        void* PvUserdata)
{
    SaMap* CsMap;

    CsMap = PvUserdata;

    CsMap->GtkBase->grid->about = gtk_grid_new();

    gtk_overlay_add_overlay(GTK_OVERLAY(CsMap->GtkBase->overlay->base),
            CsMap->GtkBase->grid->about);
}


    void
FvGtkMenuFree(void* PvFree)
{
    SaGtkMenu* CsGtkMenu;

    CsGtkMenu = PvFree;

    if (! CsGtkMenu) return;

    g_free(CsGtkMenu->action);
    g_free(CsGtkMenu->button);
    g_free(CsGtkMenu);
}


    void
FvGtkMenu(SaMap* CsMap, SaGtkBase* CsGtkBase)
{
    SaGtkMenu* CsGtkMenu;

    CsGtkMenu = CsGtkBase->GtkMenu;
    CsGtkMenu->button = g_new0(SaGtkMenuButton, 1);
    CsGtkMenu->action = g_new0(SaGtkMenuAction, 1);
    CsGtkMenu->base = g_menu_new();
    CsGtkMenu->button->base = gtk_menu_button_new();
    CsGtkMenu->action->newwindow = g_simple_action_new("newwindow", NULL);
    CsGtkMenu->action->about = g_simple_action_new("about", NULL);

    g_object_set_data_full(G_OBJECT(CsGtkBase->window->base),
            "CsGtkMenu", CsGtkMenu, (GDestroyNotify)FvGtkMenuFree);

    g_menu_append(CsGtkMenu->base, "New Window", "win.newwindow");
    g_menu_append(CsGtkMenu->base, "About", "win.about");
    g_action_map_add_action(G_ACTION_MAP(CsGtkBase->window->base),
            G_ACTION(CsGtkMenu->action->newwindow));
    g_action_map_add_action(G_ACTION_MAP(CsGtkBase->window->base),
            G_ACTION(CsGtkMenu->action->about));
    gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(CsGtkMenu->button->base),
            G_MENU_MODEL(CsGtkMenu->base));
    gtk_header_bar_pack_end(GTK_HEADER_BAR(CsGtkBase->headerbar->base),
            CsGtkBase->GtkMenu->button->base);

    g_signal_connect(CsGtkMenu->action->newwindow,
            "activate", G_CALLBACK(FvGtkMenuNewwindow), CsMap);
    g_signal_connect(CsGtkMenu->action->about,
            "activate", G_CALLBACK(FvGtkMenuAbout), CsMap);

    gtk_menu_button_set_icon_name(GTK_MENU_BUTTON(CsGtkMenu->button->base),
            "open-menu-symbolic");
}
