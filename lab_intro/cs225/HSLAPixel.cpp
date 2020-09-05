/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225 {
    // defalt pixel. non-transparent and white
    HSLAPixel::HSLAPixel(){
        h = 0.0;
        s = 0.0;
        l = 1.0;
        a = 1.0;
    }
    // opaque pixel with given hue, saturation and luminance
    HSLAPixel::HSLAPixel(double hue, double saturation, double luminance) {
        a = 1.0;
        if (hue >= 360 || hue < 0) {
            h = 0.0;
        } else {
            h = hue;
        }
        if (saturation > 1 || saturation < 0) {
            s = 0.0;
        } else {
            s = saturation;
        }
        if (luminance > 1 || luminance < 0) {
            l = 1.0;
        } else {
            l = luminance;
        }
    }
    // pixel with given hue, saturation, luminance and alpha
    HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha) {
        if (hue >= 360 || hue < 0) {
            h = 0.0;
        } else {
            h = hue;
        }
        if (saturation > 1 || saturation < 0) {
            s = 0.0;
        } else {
            s = saturation;
        }
        if (luminance > 1 || luminance < 0) {
            l = 1.0;
        } else {
            l = luminance;
        }
        if (alpha > 1 || alpha < 0) {
            a = 1.0;
        } else {
            a = alpha;
        }
    }
}
