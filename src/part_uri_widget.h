#include <stdio.h>




    void
FvGtkUriEntryClear(GtkEntry* UgEntry, GtkEntryIconPosition UgPosition,
        GdkEvent* UgEvent, void* GuUriUserdata)
{
    if (UgPosition == GTK_ENTRY_ICON_SECONDARY) {
        gtk_editable_delete_text(GTK_EDITABLE(UgEntry), 0, -1);
    }
}


    GtkWidget*
FgGtkUriEntry(TgGtkUri* UtGtkUri, const char* VcType, GtkWidget* UgParent,
        int ViUriRow, char* VcLabel)
{
    GtkWidget* UgWidget;
    GtkWidget* UgTitle;
    GtkWidget* UgEmpty;
    GtkWidget* UgButtonCopy;
    GtkWidget* UgButtonPaste;

    UgWidget = gtk_entry_new();
    UgTitle = gtk_entry_new();
    UgEmpty = gtk_label_new(NULL);
    UgButtonCopy = gtk_button_new_from_icon_name("edit-copy-symbolic");
    UgButtonPaste = gtk_button_new_from_icon_name("edit-paste-symbolic");

    gtk_grid_attach(GTK_GRID(UgParent), UgTitle,
            0, ViUriRow, 4, 1);
    gtk_grid_attach(GTK_GRID(UgParent), UgWidget,
            4, ViUriRow, 24, 1);
    gtk_grid_attach(GTK_GRID(UgParent), UgButtonPaste,
            28, ViUriRow, 2, 1);
    gtk_grid_attach(GTK_GRID(UgParent), UgButtonCopy,
            30, ViUriRow, 2, 1);
    gtk_grid_attach(GTK_GRID(UgParent), UgEmpty,
            32, ViUriRow, 1, 1);

    if (strcmp(VcType, "build") == 0)
    {
        g_signal_connect(UgWidget,
                "changed", G_CALLBACK(FvGtkUriEntryParse), UtGtkUri);
    }
    else if (strcmp(VcType, "parse") == 0)
    {
        g_signal_connect(UgWidget,
                "changed", G_CALLBACK(FvGtkUriEntryBuild), UtGtkUri);
    }

    g_signal_connect(UgWidget,
            "icon-press", G_CALLBACK(FvGtkUriEntryClear), NULL);
    g_signal_connect(UgButtonCopy,
            "clicked", G_CALLBACK(FvGtkUriEntryCopy), UgWidget);
    g_signal_connect(UgButtonPaste,
            "clicked", G_CALLBACK(FvGtkUriEntryPaste), UgWidget);

    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(UgWidget),
            GTK_ENTRY_ICON_SECONDARY, "edit-clear-symbolic");

    FvGtkUriEntrySet(UgTitle, VcLabel);
    gtk_editable_set_editable(GTK_EDITABLE(UgTitle), FALSE);
    gtk_widget_set_sensitive(UgTitle, FALSE);

    gtk_widget_set_tooltip_text(UgButtonCopy, "Copy");
    gtk_widget_set_tooltip_text(UgButtonPaste, "Paste");

    return UgWidget;
}


    GtkWidget*
FgGtkUriSpin(TgGtkUri* UtGtkUri, const char* VcType, GtkWidget* UgParent,
        int ViUriRow, char* VcLabel)
{
    GtkWidget* UgWidget;
    GtkWidget* UgTitle;
    GtkWidget* UgEmpty;
    GtkWidget* UgButtonCopy;

    UgWidget = gtk_spin_button_new_with_range(-1, 65535, 1);
    UgTitle = gtk_entry_new();
    UgEmpty = gtk_label_new(NULL);
    UgButtonCopy = gtk_button_new_from_icon_name("edit-copy-symbolic");

    gtk_grid_attach(GTK_GRID(UgParent), UgTitle,
            0, ViUriRow, 4, 1);
    gtk_grid_attach(GTK_GRID(UgParent), UgWidget,
            4, ViUriRow, 26, 1);
    gtk_grid_attach(GTK_GRID(UgParent), UgButtonCopy,
            30, ViUriRow, 2, 1);
    gtk_grid_attach(GTK_GRID(UgParent), UgEmpty,
            32, ViUriRow, 1, 1);

    g_signal_connect(UgWidget,
            "value-changed", G_CALLBACK(FvGtkUriEntryBuild), UtGtkUri);
    g_signal_connect(UgButtonCopy,
            "clicked", G_CALLBACK(FvGtkUriEntryCopy), UgWidget);

    FvGtkUriEntrySet(UgTitle, VcLabel);
    gtk_editable_set_editable(GTK_EDITABLE(UgTitle), FALSE);
    gtk_widget_set_sensitive(UgTitle, FALSE);

    gtk_widget_set_tooltip_text(UgButtonCopy, "Copy");

    return UgWidget;
}

