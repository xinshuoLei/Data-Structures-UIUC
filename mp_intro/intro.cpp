#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG inputPNG;
  inputPNG.readFromFile(inputFile);
  unsigned width = inputPNG.width();
  unsigned height = inputPNG.height();
  cs225::PNG outputPNG(width, height);
  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height; y++) {
      cs225::HSLAPixel & inputPixel = inputPNG.getPixel(x, y);
      cs225::HSLAPixel & outputPixel = outputPNG.getPixel(width -1 - x, height - 1 - y);
      outputPixel = inputPixel;
    }
  }
  outputPNG.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3

  return png;
}
