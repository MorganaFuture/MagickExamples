#pragma once
#include <Magick++.h>

class ImageException : public std::exception
{
public:
    ImageException(const std::string &message) : m_message(message) {}

    virtual const char *what() const noexcept override
    {
        return m_message.c_str();
    }

private:
    std::string m_message;
};

class Image
{
public:
    // Constructors
    Image() : m_image() {}
    Image(const std::string &filename) : m_image(filename) {}
    Image(const Image &other) : m_image(other.m_image) {}
    Image(const Magick::Image &magickImage) : m_image(magickImage) {}
    Image(Image &&other) : m_image(std::move(other.m_image)) {}
    Image(int width, int height, const Magick::Color &color) : m_image(Magick::Geometry(width, height), color) {}

    ~Image() {}

    Image &operator=(const Image &other)
    {
        m_image = other.m_image;
        return *this;
    }

    Image &operator=(Image &&other)
    {
        m_image = std::move(other.m_image);
        return *this;
    }

    void load(const std::string &filename);
    void rotate(double degrees);
    void resize(int width, int height);
    void save(const std::string &filename);

    Magick::Image &getMagickImage();

private:
    Magick::Image m_image;
};