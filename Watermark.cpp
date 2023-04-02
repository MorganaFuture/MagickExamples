#include "Watermark.h"

#include <iostream>

void Watermark::add(Magick::Image &image, int xOffset, int yOffset)
{
    try
    {
        if (xOffset < 0 || xOffset >= image.columns() || yOffset < 0 || yOffset >= image.rows())
        {
            throw WatermarkException("xOffset and yOffset must be within the bounds of the original image");
        }

        Magick::Image watermarkImage(m_image);
        watermarkImage.scale(Magick::Geometry(image.columns(), image.rows()));

        image.composite(watermarkImage, xOffset, yOffset, Magick::OverCompositeOp);
    }
    catch (Magick::Exception &ex)
    {
        throw WatermarkException(ex.what());
    }
}
