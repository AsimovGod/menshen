#include <stdio.h>




    void
FvGtkUriEntryCopy(GtkButton *UgButton, void* GuUserdata)
{
    GtkEntry* UgEntry;
    GdkClipboard* UgClipboard;
    const char* VcUriText;

    UgEntry = GuUserdata;
    VcUriText = gtk_editable_get_text(GTK_EDITABLE(UgEntry));

    if (VcUriText) {
        UgClipboard = gtk_widget_get_clipboard(GTK_WIDGET(UgEntry));
        gdk_clipboard_set_text(UgClipboard, VcUriText);
    }
}


    void
FvGtkUriEntryPasteReceived(GObject* UgObject, GAsyncResult* UgResult,
        void* GuUserdata)
{
    GtkEntry* UgEntry;
    GdkClipboard* UgClipboard;
    const GValue* UgValue;
    const char* VcUriText;

    UgEntry = GTK_ENTRY(GuUserdata);
    UgClipboard = GDK_CLIPBOARD(UgObject);
    UgValue = gdk_clipboard_read_value_finish(UgClipboard, UgResult, NULL);

    if (! UgValue) return;
    if (! G_VALUE_HOLDS_STRING(UgValue)) return;

    VcUriText = g_value_get_string(UgValue);

    if (VcUriText) {
        gtk_editable_set_text(GTK_EDITABLE(UgEntry), VcUriText);
    }
}


    void
FvGtkUriEntryPaste(GtkButton *UgButton, void* GuUserdata)
{
    GtkEntry* UgEntry;
    GdkClipboard* UgClipboard;

    UgEntry = GTK_ENTRY(GuUserdata);
    UgClipboard = gtk_widget_get_clipboard(GTK_WIDGET(UgEntry));

    if (UgClipboard) {
        gdk_clipboard_read_value_async(UgClipboard,
                G_TYPE_STRING, G_PRIORITY_DEFAULT, NULL,
                FvGtkUriEntryPasteReceived, UgEntry);
    }
}

