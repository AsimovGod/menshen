// part_menu.h



void FvGtkBase(GtkApplication* UgApplication, SuMap* PsMap, char** AcArgument);


    void
FvGtkMenuNewwindow(GSimpleAction* UgSimpleaction, GVariant* UgVariant,
        void* PvUserdata)
{
    SuMap* PsMap;

    PsMap = PvUserdata;

    FvGtkBase(GTK_APPLICATION(PsMap->application), PsMap, NULL);
}


    void
FvGtkMenuAbout(GSimpleAction* UgSimpleaction, GVariant* UgVariant,
        void* PvUserdata)
{
    SuMap* PsMap;

    PsMap = PvUserdata;

    PsMap->gtkBase->grid->about = gtk_grid_new();

    gtk_overlay_add_overlay(GTK_OVERLAY(PsMap->gtkBase->overlay->base),
            PsMap->gtkBase->grid->about);
}


    void
FvGtkMenuFree(void* PvFree)
{
    SuGtkMenu* PsGtkMenu;

    PsGtkMenu = PvFree;

    if (! PsGtkMenu) return;

    g_free(PsGtkMenu->action);
    g_free(PsGtkMenu->button);
    g_free(PsGtkMenu);
}


    void
FvGtkMenu(SuMap* PsMap, SuGtkBase* PsGtkBase)
{
    SuGtkMenu* PsGtkMenu;

    PsGtkMenu = PsGtkBase->GtkMenu;
    PsGtkMenu->button = g_new0(SuGtkMenuButton, 1);
    PsGtkMenu->action = g_new0(SuGtkMenuAction, 1);
    PsGtkMenu->base = g_menu_new();
    PsGtkMenu->button->base = gtk_menu_button_new();
    PsGtkMenu->action->newwindow = g_simple_action_new("newwindow", NULL);
    PsGtkMenu->action->about = g_simple_action_new("about", NULL);

    g_object_set_data_full(G_OBJECT(PsGtkBase->window->base),
            "PsGtkMenu", PsGtkMenu, (GDestroyNotify)FvGtkMenuFree);

    g_menu_append(PsGtkMenu->base, "New Window", "win.newwindow");
    g_menu_append(PsGtkMenu->base, "About", "win.about");
    g_action_map_add_action(G_ACTION_MAP(PsGtkBase->window->base),
            G_ACTION(PsGtkMenu->action->newwindow));
    g_action_map_add_action(G_ACTION_MAP(PsGtkBase->window->base),
            G_ACTION(PsGtkMenu->action->about));
    gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(PsGtkMenu->button->base),
            G_MENU_MODEL(PsGtkMenu->base));
    gtk_header_bar_pack_end(GTK_HEADER_BAR(PsGtkBase->headerbar->base),
            PsGtkBase->GtkMenu->button->base);

    g_signal_connect(PsGtkMenu->action->newwindow,
            "activate", G_CALLBACK(FvGtkMenuNewwindow), PsMap);
    g_signal_connect(PsGtkMenu->action->about,
            "activate", G_CALLBACK(FvGtkMenuAbout), PsMap);

    gtk_menu_button_set_icon_name(GTK_MENU_BUTTON(PsGtkMenu->button->base),
            "open-menu-symbolic");
}
