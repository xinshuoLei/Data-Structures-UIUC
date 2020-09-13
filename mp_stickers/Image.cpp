#include "Image.h"
#include "cs225/HSLAPixel.h"
#include <cmath>

// Lighten an Image by increasing the luminance of every pixel by 0.1. 
void Image::lighten() {
    for (unsigned x = 0; x < this -> width(); x++) {
        for (unsigned y = 0; y < this -> height(); y++) {
            cs225::HSLAPixel& pixel = this -> getPixel(x, y);
            if (pixel.l + 0.1 <= 1) {
                pixel.l = pixel.l + 0.1;
            } else {
                pixel.l = 1;
            }
        }
    }
}

// Lighten an Image by increasing the luminance of every pixel by amount. 
void Image::lighten(double amount) {
    for (unsigned x = 0; x < this -> width(); x++) {
        for (unsigned y = 0; y < this -> height(); y++) {
            cs225::HSLAPixel& pixel = this -> getPixel(x, y);
            if (pixel.l + amount <= 1) {
                pixel.l = pixel.l + amount;
            } else {
                pixel.l = 1;
            }
        }
    }
} 

// Darken an Image by decreasing the luminance of every pixel by 0.1.
void Image::darken() {
    for (unsigned x = 0; x < this -> width(); x++) {
        for (unsigned y = 0; y < this -> height(); y++) {
            cs225::HSLAPixel& pixel = this -> getPixel(x, y);
            if (pixel.l - 0.1 >= 0) {
                pixel.l = pixel.l - 0.1;
            } else {
                pixel.l = 0;
            }
        }
    }
}

// Darkens an Image by decreasing the luminance of every pixel by amount.
void Image::darken(double amount) {
    for (unsigned x = 0; x < this -> width(); x++) {
        for (unsigned y = 0; y < this -> height(); y++) {
            cs225::HSLAPixel& pixel = this -> getPixel(x, y);
            if (pixel.l - amount >= 0) {
                pixel.l = pixel.l - amount;
            } else {
                pixel.l = 0;
            }
        }
    }
}        

// Saturates an Image by increasing the saturation of every pixel by 0.1. 
void Image::saturate() {
    for (unsigned x = 0; x < this -> width(); x++) {
        for (unsigned y = 0; y < this -> height(); y++) {
            cs225::HSLAPixel& pixel = this -> getPixel(x, y);
            if (pixel.s + 0.1 <= 1) {
                pixel.s = pixel.s + 0.1;
            } else {
                pixel.s = 1;
            }
        }
    }
}        

//Saturates an Image by increasing the saturation of every pixel by amount. 
void Image::saturate(double amount) {
    for (unsigned x = 0; x < this -> width(); x++) {
        for (unsigned y = 0; y < this -> height(); y++) {
            cs225::HSLAPixel& pixel = this -> getPixel(x, y);
            if (pixel.s + amount <= 1) {
                pixel.s = pixel.s + amount;
            } else {
                pixel.s = 1;
            }
        }
    }
}   

// Desaturates an Image by decreasing the saturation of every pixel by 0.1
void Image::desaturate() {
    for (unsigned x = 0; x < this -> width(); x++) {
        for (unsigned y = 0; y < this -> height(); y++) {
            cs225::HSLAPixel& pixel = this -> getPixel(x, y);
            if (pixel.s - 0.1 >= 0) {
                pixel.s = pixel.s - 0.1;
            } else {
                pixel.s = 0;
            };
        }
    }
}

// Desaturates an Image by decreasing the saturation of every pixel by amount. 
void Image::desaturate(double amount) {
    for (unsigned x = 0; x < this -> width(); x++) {
        for (unsigned y = 0; y < this -> height(); y++) {
            cs225::HSLAPixel& pixel = this -> getPixel(x, y);
            if (pixel.s - amount >= 0) {
                pixel.s = pixel.s - amount;
            } else {
                pixel.s = 0;
            }
        }
    }
}

// Turns the image grayscale.
void Image::grayscale() {
    for (unsigned x = 0; x < this -> width(); x++) {
        for (unsigned y = 0; y < this -> height(); y++) {
            cs225::HSLAPixel& pixel = this -> getPixel(x, y);
            pixel.s = 0;
        }
    }
}

// Rotates the color wheel by degrees.
void Image::rotateColor(double degrees) {
    for (unsigned x = 0; x < this -> width(); x++) {
        for (unsigned y = 0; y < this -> height(); y++) {
            cs225::HSLAPixel& pixel = this -> getPixel(x, y);
            if (pixel.h + degrees > 360) {
                pixel.h = (degrees - (360 - pixel.h));
            } else if (pixel.h + degrees < 0) {
                pixel.h = 360 + (pixel.h + degrees);
            } else {
                pixel.h = pixel.h + degrees;
            }
        }
    }
}

// Illinify the image.
void Image::illinify() {
    double midpoint1 = (216.0 - 11.0) / 2 + 11.0;
    double midpoint2 = ((360.0 - 216.0 + 11.0) / 2) + 216.0;
    for (unsigned i = 0; i < this -> width(); i++) {
        for (unsigned j = 0; j < this -> height(); j++) {
            cs225::HSLAPixel & pixel = this -> getPixel(i, j);
        if ((pixel.h > midpoint1) && (pixel.h < midpoint2)) {
            pixel.h = 216;
        } else {
            pixel.h = 11;
        }
    }
  }
}

// Scale the Image by a given factor. 
void Image::scale(double factor) {
    unsigned newWidth = this -> width() * factor;
    unsigned newHeight = this -> height() * factor;
    cs225::PNG png = (*this);
    this -> resize(newWidth, newHeight);
    for (unsigned x = 0; x < newWidth; x++) {
        for (unsigned y = 0; y < newHeight; y++) {
            cs225::HSLAPixel& original = png.getPixel(floor(x / factor), floor(y / factor));
            cs225::HSLAPixel& newPixel = this -> getPixel(x, y);
            newPixel = original;
        }
    }
}

// Scales the image to fit within the size (w x h)
void Image::scale(unsigned w, unsigned h) {
    double factor = std::min((double) w / this -> width(), (double) h / this -> height());
    cs225::PNG png = (*this);
    this -> resize(w, h);
    for (unsigned x = 0; x < png.width() * factor; x++) {
        for (unsigned y = 0; y < png.height() * factor; y++) {
            cs225::HSLAPixel& original = png.getPixel(floor(x / factor), floor(y / factor));
            cs225::HSLAPixel& newPixel = this -> getPixel(x, y);
            newPixel = original;
        }
    }
}