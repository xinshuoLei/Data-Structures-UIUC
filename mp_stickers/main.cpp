#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image background;
  background.readFromFile("background.png");
  Image sticker_1;
  sticker_1.readFromFile("sticker_1.png");
  sticker_1.scale(370,370);
  Image sticker_2;
  sticker_2.readFromFile("sticker_2.png");
  sticker_2.scale(370,400);
  Image sticker_3;
  sticker_3.readFromFile("sticker_3.png");
  sticker_3.scale(370,370);
  Image sticker_4;
  sticker_4.readFromFile("sticker_4.png");
  sticker_4.scale(370,370);
  Image sticker_5;
  sticker_5.readFromFile("sticker_5.png");
  sticker_5.scale(370,370);
  StickerSheet sheet(background, 5);
  sheet.addSticker(sticker_1, 250, 550);
  sheet.addSticker(sticker_2, 700, 550);
  sheet.addSticker(sticker_3, 1150, 550);
  sheet.addSticker(sticker_4, 450, 220);
  sheet.addSticker(sticker_5, 900, 220);
  sheet.render().writeToFile("myImage.png");
  return 0;
}
