// part_menu.h



void FvGtkBase(GtkApplication* EgApplication, SaMap* CsMap, char* AcUri);


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
    SaGtkMenu* CsGtkMenu;

    CsMap = PvUserdata;
    CsGtkMenu = CsMap->GtkBase->GtkMenu;

    const char* TcButton[] = { "Close", NULL };

    CsGtkMenu->dialog->about = gtk_alert_dialog_new("About");

    gtk_alert_dialog_set_detail(CsGtkMenu->dialog->about,
            "Help and About");
    gtk_alert_dialog_set_buttons(CsGtkMenu->dialog->about,
            TcButton);
    gtk_alert_dialog_choose(CsGtkMenu->dialog->about,
            GTK_WINDOW(CsMap->GtkBase->window->base), NULL, NULL, NULL);
}


    void
FvGtkMenuFree(void* PvFree)
{
    SaGtkMenu* CsGtkMenu;

    CsGtkMenu = PvFree;

    if (! CsGtkMenu) return;

    g_free(CsGtkMenu->action);
    g_free(CsGtkMenu->button);
    g_free(CsGtkMenu->dialog);
    g_free(CsGtkMenu);
}


    void
FvGtkMenu(SaMap* CsMap, SaGtkBase* CsGtkBase)
{
    SaGtkMenu* CsGtkMenu;

    CsGtkMenu = g_new0(SaGtkMenu, 1);
    CsGtkMenu->button = g_new0(SaGtkMenuButton, 1);
    CsGtkMenu->action = g_new0(SaGtkMenuAction, 1);
    CsGtkMenu->dialog = g_new0(SaGtkMenuDialog, 1);

    CsGtkMenu->base = g_menu_new();
    CsGtkMenu->button->base = gtk_menu_button_new();
    CsGtkMenu->action->newwindow = g_simple_action_new("newwindow", NULL);
    CsGtkMenu->action->about = g_simple_action_new("about", NULL);

    CsGtkBase->GtkMenu = CsGtkMenu;

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
