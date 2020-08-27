/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#pragma once

#include <iostream>
#include <sstream>

namespace cs225 {
    class HSLAPixel {
      public:
        double h;   // hue of the pixel
        double s;   // saturation of the pixel
        double l;   // luminance of the pixel
        double a;   // alpha of the pixel

        // create a default HSLAPixel
        HSLAPixel();
        // create a opaque HSLAPixel with the given hue, saturation and luminance
        HSLAPixel(double hue, double saturation, double luminance);
        // create HSLAPixel with the given hue, saturation, luminance, and alpha
        HSLAPixel(double hue, double saturation, double luminabce, double alpha);
    };
}
