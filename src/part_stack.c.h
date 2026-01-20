// part_window.h



    void
FvGtkStackFree(void* PvFree)
{
    SaGtkStack* CsGtkStack;

    CsGtkStack = PvFree;

    if (! CsGtkStack) return;

    g_free(CsGtkStack->paned);
    g_free(CsGtkStack->grid);
    g_free(CsGtkStack->scroll);
    g_free(CsGtkStack);
}


    void
FvGtkStack(SaMap* CsMap, char* AcUri)
{
    SaGtkStack* CsGtkStack;
    GtkApplication* EgApplication;

    EgApplication = CsMap->application;

    CsGtkStack = g_new0(SaGtkStack, 1);
    CsGtkStack->paned = g_new0(SaGtkPaned, 1);
    CsGtkStack->grid = g_new0(SaGtkGrid, 1);
    CsGtkStack->scroll = g_new0(SaGtkScroll, 1);

    CsGtkStack->paned->base = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    CsGtkStack->paned->baseLeft = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    CsGtkStack->paned->baseRight = gtk_paned_new(GTK_ORIENTATION_VERTICAL);

    CsMap->GtkStack = CsGtkStack;

    g_object_set_data_full(G_OBJECT(CsMap->GtkWindow->base),
            "CsGtkStack", CsGtkStack, (GDestroyNotify)FvGtkStackFree);

    gtk_window_set_child(GTK_WINDOW(CsMap->GtkWindow->base),
            CsGtkStack->paned->base);
    gtk_paned_set_start_child(GTK_PANED(CsGtkStack->paned->base),
            CsGtkStack->paned->baseLeft);
    gtk_paned_set_end_child(GTK_PANED(CsGtkStack->paned->base),
            CsGtkStack->paned->baseRight);

    CsGtkStack->paned->baseR = 0.8;
    CsGtkStack->paned->baseLeftR = 0.2;
    CsGtkStack->paned->baseRightR = 0.7;

    gtk_paned_set_position(GTK_PANED(CsGtkStack->paned->base),
            CsGtkStack->paned->baseR * CsMap->GtkWindow->baseW);
    gtk_paned_set_position(GTK_PANED(CsGtkStack->paned->baseLeft),
            CsGtkStack->paned->baseLeftR * CsMap->GtkWindow->baseH);
    gtk_paned_set_position(GTK_PANED(CsGtkStack->paned->baseRight),
            CsGtkStack->paned->baseRightR * CsMap->GtkWindow->baseH);

    gtk_widget_set_valign(CsGtkStack->paned->base, GTK_ALIGN_FILL);
    gtk_widget_set_halign(CsGtkStack->paned->base, GTK_ALIGN_FILL);
    gtk_widget_set_valign(CsGtkStack->paned->baseLeft, GTK_ALIGN_FILL);
    gtk_widget_set_halign(CsGtkStack->paned->baseLeft, GTK_ALIGN_FILL);
    gtk_widget_set_valign(CsGtkStack->paned->baseRight, GTK_ALIGN_FILL);
    gtk_widget_set_halign(CsGtkStack->paned->baseRight, GTK_ALIGN_FILL);

    FvGtkUri(CsMap, AcUri);
    FvGtkMime(CsMap);
}

