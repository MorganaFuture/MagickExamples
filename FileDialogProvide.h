#pragma once
#include <gtk/gtk.h>
#include <string>

class FileDialog
{
public:
  enum class Mode
  {
    OPEN,
    SAVE
  };

  FileDialog(Mode mode, const std::string &title, const std::string &default_filename = "")
      : m_mode(mode), m_title(title), m_default_filename(default_filename), m_filename("") {}

  FileDialog(const FileDialog &other) = delete;
  FileDialog(FileDialog &&other) = delete;
  FileDialog &operator=(const FileDialog &other) = delete;
  FileDialog &operator=(FileDialog &&other) = delete;

  std::string run();

private:
  Mode m_mode;
  std::string m_title;
  std::string m_default_filename;
  std::string m_filename;
};