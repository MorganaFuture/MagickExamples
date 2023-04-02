#include "Image.h"
#include <iostream>

void Image::load(const std::string &filename)
{
    if (filename.empty())
    {
        throw std::invalid_argument("Filename cannot be empty");
    }

    try
    {
        m_image.read(filename);
    }
    catch (Magick::Exception &ex)
    {
        throw ImageException(std::string("Error rotating image: ") + ex.what());
    }
}

void Image::rotate(double degrees)
{
    try
    {
        if (degrees < 0 || degrees > 360)
        {
            throw std::invalid_argument("Degrees must be between 0 and 360");
        }
        m_image.rotate(degrees);
    }
    catch (Magick::Exception &ex)
    {
        throw ImageException(std::string("Error rotating image: ") + ex.what());
    }
}

void Image::resize(int width, int height)
{
    try
    {
        if (width <= 0 || height <= 0)
        {
            throw std::invalid_argument("Width and height must be positive integers");
        }
        m_image.resize(Magick::Geometry(width, height));
    }
    catch (Magick::Exception &ex)
    {
        throw ImageException(std::string("Error resizing image: ") + ex.what());
    }
}

void Image::save(const std::string &filename)
{
    if (filename.empty())
    {
        throw std::invalid_argument("Filename cannot be empty");
    }

    try
    {
        m_image.write(filename);
    }
    catch (Magick::Exception &ex)
    {
        throw ImageException(std::string("Error resizing image: ") + ex.what());
    }
}

Magick::Image &Image::getMagickImage()
{
    return m_image;
}
