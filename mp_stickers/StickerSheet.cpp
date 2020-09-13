#include "StickerSheet.h"

// Initializes this StickerSheet with a deep copy of the base picture and the ability to hold a max number of stickers (Images) with indices 0 through max - 1. 
StickerSheet::StickerSheet(const Image &picture, unsigned max){

}
    
// Frees all space that was dynamically allocated by this StickerSheet. 
StickerSheet::~StickerSheet() {

}                                  
     
// The copy constructor makes this StickerSheet an independent copy of the source 
StickerSheet::StickerSheet (const StickerSheet &other) {
    
}
 	
 
// The assignment operator for the StickerSheet class.
const StickerSheet & StickerSheet::operator= (const StickerSheet &other) {
    return *this;
}
 	
// Modifies the maximum number of stickers that can be stored on this StickerSheet without changing existing stickers' indices. 
void StickerSheet::changeMaxStickers (unsigned max){

}

 
// Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet.
int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y) {
    return 0;
}
 	
// Changes the x and y coordinates of the Image in the specified layer. 
bool StickerSheet::translate (unsigned index, unsigned x, unsigned y) {
    return true;
}
 	
// Removes the sticker at the given zero-based layer index.  
void StickerSheet::removeSticker (unsigned index) {

}
 	
// Returns a pointer to the sticker at the specified index, not a copy of it.  
Image * StickerSheet::getSticker (unsigned index) {
    return NULL;
}

// Renders the whole StickerSheet on one Image and returns that Image.  	
Image StickerSheet::render () const {
    Image image;
    return image;
}
 	