#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"
#include <algorithm>

// Initializes this StickerSheet with a deep copy of the base picture and the ability to hold a max number of stickers (Images) with indices 0 through max - 1. 
StickerSheet::StickerSheet(const Image &picture, unsigned max){
    base = new Image(picture);
    maxNumber = max;
    stickers = new Image*[maxNumber];
    for (int a = 0; a < maxNumber; a++) {
        stickers[a] = NULL;
    }
    x_ = new int[maxNumber];
    y_ = new int[maxNumber];
}
    
// Frees all space that was dynamically allocated by this StickerSheet. 
StickerSheet::~StickerSheet() {
    destroy();
}                                  
     
// The copy constructor makes this StickerSheet an independent copy of the source 
StickerSheet::StickerSheet (const StickerSheet &other) {
    copy(other);
}
 	
 
// The assignment operator for the StickerSheet class.
const StickerSheet & StickerSheet::operator= (const StickerSheet &other) {
    if (&other != this) {
        destroy();
        copy(other);
    }
    return *this;
}
 	
// Modifies the maximum number of stickers that can be stored on this StickerSheet without changing existing stickers' indices. 
void StickerSheet::changeMaxStickers (unsigned max){
    StickerSheet temp = StickerSheet(*this);
    destroy();
    base = new Image(*temp.base);
    maxNumber = max;
    stickers = new Image*[max];
    for (int b = 0; b < maxNumber; b++) {
        stickers[b] = NULL;
    }
    x_ = new int[max];
    y_ = new int[max];
    for (int a = 0; a < std::min(maxNumber, temp.maxNumber); a++) {
        if (temp.stickers[a] != NULL) {
            stickers[a] = new Image((*temp.stickers[a]));
            x_[a] = temp.x_[a];
            y_[a] = temp.y_[a];
        }
    }    
}

 
// Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet.
int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y) {
    for (int a = 0; a < maxNumber; a++) {
        if (stickers[a] == NULL) {
            stickers[a] = new Image(sticker);
            x_[a] = x;
            y_[a] = y;
            return a; 
        }
    }
    return -1;
}
 	
// Changes the x and y coordinates of the Image in the specified layer. 
bool StickerSheet::translate (unsigned index, unsigned x, unsigned y) {
    if ((int) index < maxNumber && stickers[index] != NULL) {
        x_[index] = x;
        y_[index] = y;
    }
    return false;
}
 	
// Removes the sticker at the given zero-based layer index.  
void StickerSheet::removeSticker (unsigned index) {
    delete stickers[index];
    stickers[index] = NULL;
}
 	
// Returns a pointer to the sticker at the specified index, not a copy of it.  
Image * StickerSheet::getSticker (unsigned index) {
    return stickers[index];
}

// Renders the whole StickerSheet on one Image and returns that Image.  	
Image StickerSheet::render () const {
    Image image = Image(*base);
    int max_width = image.width();
    int max_height = image.height();
    for (int b = 0; b < maxNumber; b++) {
        if (stickers[b] != NULL) {
            if ((int) (x_[b] + stickers[b] -> width()) > max_width) {
                max_width = x_[b] + stickers[b] -> width();
            }
            if ((int) (y_[b] + stickers[b] -> height()) > max_height) {
                max_height = y_[b] + stickers[b] -> height();
            }
        }
        
    }
    image.resize(max_width, max_height);
    for (int a = 0; a < maxNumber; a++) {
        if (stickers[a] != NULL) {
            int sticker_width = stickers[a]-> width();
            int sticker_height = stickers[a] -> height();
            for (unsigned b = 0; b < image.width(); b++) {
                for (unsigned c = 0; c < image.height(); c++) {
                    if ((x_[a] + sticker_width > (int) b) && ((int) b >= x_[a]) && (y_[a] + sticker_height > (int) c) && ((int)c >= y_[a])) {
                        cs225::HSLAPixel& base_pixel = image.getPixel(b, c);
                        if ((*stickers[a]).getPixel(b - x_[a], c - y_[a]).a != 0) {
                            base_pixel = (*stickers[a]).getPixel(b - x_[a], c - y_[a]);
                        }
                    } 
                }
            }
        }
    }
    return image;
}

void StickerSheet::copy(const StickerSheet& other) {
    base = new Image(*(other.base));
    maxNumber = other.maxNumber;
    stickers = new Image*[other.maxNumber];
    for (int b = 0; b < other.maxNumber; b++) {
        stickers[b] = NULL;
    }
    x_ = new int[maxNumber];
    y_ = new int[maxNumber];
    for (int a = 0; a < other.maxNumber; a++) {
        if (other.stickers[a] != NULL) {
            stickers[a] = new Image(*(other.stickers[a]));
            x_[a] = other.x_[a];
            y_[a] = other.y_[a];
        }
    }  
}

void StickerSheet::destroy() {
    if (base != NULL) {
        delete base;
    }
    if (x_ != NULL) {
        delete[] x_;
    }
    if (y_ != NULL) {
        delete[] y_;
    }
    if (stickers != NULL) {
        for (int x = 0; x < maxNumber; x++) {
            delete stickers[x];
        }
        delete[] stickers;
    }
    
}