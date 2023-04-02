#pragma once

#include <gtk/gtk.h>
#include <string>

class InputWindow
{
public:
  virtual ~InputWindow()
  {
    if (m_parent != nullptr)
    {
      gtk_widget_destroy(m_parent);
    }
  }
  InputWindow(const std::string &title, GtkWindow *parent)
      : m_title(title), m_parent(GTK_WIDGET(parent)) {}
  virtual std::string run() = 0;

protected:
  InputWindow(const std::string &title)
      : m_title(title), m_parent(nullptr) {}
  std::string m_title;
  GtkWidget *m_parent;
};
