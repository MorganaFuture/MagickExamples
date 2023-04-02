#include "FileDialogProvide.h"

#include <stdexcept>

std::string FileDialog::run()
{
    // Initialize GTK library
    if (!gtk_init_check(NULL, NULL))
    {
        throw std::runtime_error("Failed to initialize GTK library");
    }

    // Create a new file chooser dialog
    GtkWidget *dialog = gtk_file_chooser_dialog_new(
        m_title.c_str(),
        NULL,
        m_mode == Mode::OPEN ? GTK_FILE_CHOOSER_ACTION_OPEN : GTK_FILE_CHOOSER_ACTION_SAVE,
        "_Cancel", GTK_RESPONSE_CANCEL,
        m_mode == Mode::OPEN ? "_Open" : "_Save", GTK_RESPONSE_ACCEPT,
        NULL);

    if (!dialog)
    {
        throw std::runtime_error("Failed to create file chooser dialog");
    }

    // Set the default filename, if provided
    if (!m_default_filename.empty())
    {
        gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), m_default_filename.c_str());
    }

    // Show the dialog and run the GTK main loop
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result != GTK_RESPONSE_ACCEPT)
    {
        // User cancelled the dialog
        gtk_widget_destroy(dialog);
        gtk_main_quit();
        return "";
    }

    // Get the filename selected or entered
    char *filename_cstr = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    if (!filename_cstr)
    {
        gtk_widget_destroy(dialog);
        gtk_main_quit();
        throw std::runtime_error("Failed to get filename from file chooser dialog");
    }

    m_filename = filename_cstr;
    g_free(filename_cstr);

    // Check if the selected file exists or not, only for OPEN mode
    if (m_mode == Mode::OPEN && access(m_filename.c_str(), F_OK) == -1)
    {
        gtk_widget_destroy(dialog);
        gtk_main_quit();
        throw std::runtime_error("Selected file does not exist");
    }

    // Check if the selected file is writable, only for SAVE mode and if file doesn't exist
    if (m_mode == Mode::SAVE && access(m_filename.c_str(), F_OK) == -1 && access(g_path_get_dirname(m_filename.c_str()), W_OK) == -1)
    {
        gtk_widget_destroy(dialog);
        gtk_main_quit();
        throw std::runtime_error("Selected directory is not writable");
    }

    // Destroy the dialog and quit the GTK main loop
    gtk_widget_destroy(dialog);
    gtk_main_quit();

    // Return the filename selected or entered
    return m_filename;
}
