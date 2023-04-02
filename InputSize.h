#pragma once
#include "InputWindow.h"

#include <gtk/gtk.h>
#include <string>

class InputSize : public InputWindow
{
public:
  InputSize(const std::string &title, GtkWindow *parent) : InputWindow(title, parent) {}

  ~InputSize() {}

  std::string run() override;

private:
  std::string m_value;
};
