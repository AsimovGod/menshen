// part_menu.h



void FvGtkWindow(SaMap* CsMap, int DiArgument, char** TcArgument);


    void
FvGtkMenuNewwindow(GSimpleAction* EgSimpleaction, GVariant* EgVariant,
        void* PvUserdata)
{
    SaMap* CsMap;

    CsMap = PvUserdata;

    FvGtkWindow(CsMap, 0, NULL);
}


    void
FvGtkMenuAbout(GSimpleAction* EgSimpleaction, GVariant* EgVariant,
        void* PvUserdata)
{
    SaMap* CsMap;
    SaGtkMenu* CsGtkMenu;

    CsMap = PvUserdata;
    CsGtkMenu = CsMap->GtkMenu;

    const char* TcButton[] = { "Close", NULL };

    CsGtkMenu->about = gtk_alert_dialog_new("About");

    gtk_alert_dialog_set_detail(CsGtkMenu->about,
            "Help and About");
    gtk_alert_dialog_set_buttons(CsGtkMenu->about,
            TcButton);
    gtk_alert_dialog_choose(CsGtkMenu->about,
            GTK_WINDOW(CsMap->GtkWindow->base), NULL, NULL, NULL);
}


    void
FvGtkMenu(SaMap* CsMap)
{
    SaGtkStack* CsGtkStack;
    SaGtkMenu* CsGtkMenu;

    CsGtkStack = CsMap->GtkStack;

    CsGtkMenu = g_new0(SaGtkMenu, 1);
    CsGtkMenu->action = g_new0(SaGtkMenuAction, 1);

    CsGtkMenu->base = g_menu_new();
    CsGtkMenu->button = gtk_menu_button_new();
    CsGtkMenu->action->newwindow = g_simple_action_new("newwindow", NULL);
    CsGtkMenu->action->about = g_simple_action_new("about", NULL);

    CsMap->GtkMenu = CsGtkMenu;

    g_object_set_data_full(G_OBJECT(CsMap->GtkWindow->base),
            "CsGtkMenu", CsGtkMenu, (GDestroyNotify)g_free);

    g_menu_append(CsGtkMenu->base, "New Window", "win.newwindow");
    g_menu_append(CsGtkMenu->base, "About", "win.about");
    g_action_map_add_action(G_ACTION_MAP(CsMap->GtkWindow->base),
            G_ACTION(CsGtkMenu->action->newwindow));
    g_action_map_add_action(G_ACTION_MAP(CsMap->GtkWindow->base),
            G_ACTION(CsGtkMenu->action->about));
    gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(CsGtkMenu->button),
            G_MENU_MODEL(CsGtkMenu->base));
    gtk_header_bar_pack_end(GTK_HEADER_BAR(CsMap->GtkWindow->headerbar),
            CsGtkMenu->button);

    g_signal_connect(CsGtkMenu->action->newwindow,
            "activate", G_CALLBACK(FvGtkMenuNewwindow), CsMap);
    g_signal_connect(CsGtkMenu->action->about,
            "activate", G_CALLBACK(FvGtkMenuAbout), CsMap);

    gtk_menu_button_set_icon_name(GTK_MENU_BUTTON(CsGtkMenu->button),
            "open-menu-symbolic");
}
