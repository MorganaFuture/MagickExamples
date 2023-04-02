#pragma once

#include "InputWindow.h"

#include <gtk/gtk.h>
#include <string>

class InputDegrees : public InputWindow
{
public:
  InputDegrees(const std::string &title, GtkWindow *parent) : InputWindow(title, parent) {}

  virtual std::string run() override;

private:
  int m_degrees;
};