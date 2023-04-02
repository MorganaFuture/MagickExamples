#pragma once
#include <Magick++.h>

class WatermarkException : public std::exception
{
public:
    WatermarkException(const char *message) : m_message(message) {}

    virtual const char *what() const noexcept override
    {
        return m_message.c_str();
    }

private:
    std::string m_message;
};

class Watermark
{
public:
    Watermark() : m_image() {}
    Watermark(const std::string &filename) : m_image(filename) {}
    Watermark(Magick::Image &&image) : m_image(std::move(image)) {}
    Watermark(const Magick::Image &image) : m_image(image) {}
    Watermark(Watermark &&other) : m_image(std::move(other.m_image)) {}
    Watermark(const Watermark &other) : m_image(other.m_image) {}

    ~Watermark() {}

    Watermark &operator=(Watermark &&other)
    {
        m_image = std::move(other.m_image);
        return *this;
    }

    Watermark &operator=(const Watermark &other)
    {
        m_image = other.m_image;
        return *this;
    }

    void add(Magick::Image &image, int xOffset, int yOffset);

private:
    Magick::Image m_image;
};
