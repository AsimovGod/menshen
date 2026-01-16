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
        int ViUriRow, const char* VcLabel)
{
    GtkWidget* UgWidget;
    GtkWidget* UgButtonCopy;
    GtkWidget* UgButtonPaste;

    UgButtonCopy = gtk_button_new_from_icon_name("edit-copy-symbolic");

    if (strcmp(VcType, "buttonPort") == 0) {
        UgWidget = gtk_spin_button_new_with_range(-1, 65535, 1);
    }
    else {
        UgWidget = gtk_entry_new();
        UgButtonPaste = gtk_button_new_from_icon_name("edit-paste-symbolic");

        gtk_widget_set_tooltip_text(UgButtonPaste, "Paste");

        gtk_entry_set_icon_from_icon_name(GTK_ENTRY(UgWidget),
                GTK_ENTRY_ICON_SECONDARY, "edit-clear-symbolic");

        gtk_grid_attach(GTK_GRID(UgParent),
                UgButtonPaste, 3, ViUriRow, 1, 1);

        g_signal_connect(UgWidget,
                "icon-press", G_CALLBACK(FvGtkUriEntryClear), NULL);

        g_signal_connect(UgButtonPaste,
                "clicked", G_CALLBACK(FvGtkUriEntryPaste), UgWidget);
    }

    gtk_widget_set_hexpand(UgWidget, TRUE);
    gtk_widget_set_tooltip_text(UgButtonCopy, "Copy");
    gtk_widget_set_margin_end(UgButtonCopy, 24);

    if (strcmp(VcType, "buttonPort") == 0) {
        g_signal_connect(UgWidget,
                "value-changed", G_CALLBACK(FvGtkUriEntryBuild), UtGtkUri);
    }
    else if (strcmp(VcType, "entryBuild") == 0)
    {
        g_signal_connect(UgWidget,
                "changed", G_CALLBACK(FvGtkUriEntryParse), UtGtkUri);
    }
    else if (strcmp(VcType, "entryParse") == 0)
    {
        g_signal_connect(UgWidget,
                "changed", G_CALLBACK(FvGtkUriEntryBuild), UtGtkUri);
    }
    else {
        return NULL;
    }

    g_signal_connect(UgButtonCopy,
            "clicked", G_CALLBACK(FvGtkUriEntryCopy), UgWidget);

    gtk_grid_attach(GTK_GRID(UgParent),
            gtk_label_new(VcLabel), 0, ViUriRow, 1, 1);

    gtk_grid_attach(GTK_GRID(UgParent),
            UgButtonCopy, 4, ViUriRow, 1, 1);

    gtk_grid_attach(GTK_GRID(UgParent),
            UgWidget, 1, ViUriRow, 2, 1);

    return UgWidget;
}

