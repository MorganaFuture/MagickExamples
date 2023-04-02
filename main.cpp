#include <iostream>
#include <string>
#include <gdk/gdk.h>

#include "Image.h"
#include "Watermark.h"
#include "FileDialogProvide.h"
#include "InputDegrees.h"
#include "InputSize.h"

int main()
{
  FileDialog file_dialog(FileDialog::Mode::OPEN, "Open File", "example.txt");
  std::string filename = file_dialog.run();

  Image image;
  image.load(filename);

  filename = file_dialog.run();
  Watermark watermark(filename);
  watermark.add(image.getMagickImage(), 100, 100);
  FileDialog file_dialog2(FileDialog::Mode::SAVE, "Open File", "example.jpg");
  std::string save_to_file = file_dialog2.run();
  image.save(save_to_file);

  return 0;
}