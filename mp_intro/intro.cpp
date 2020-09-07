#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
#include <cmath>


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
  double diagonal_distance = sqrt((width - 1) * (width - 1) + (height - 1) * (height - 1));
  for (unsigned a = 0; a < width; a++) {
    for (unsigned b = 0; b < width; b++) {
      cs225::HSLAPixel & pixel = png.getPixel(a, b);
      pixel.s = 1.0;
      double distance = sqrt(a * a + b * b);
      // change hue
      if (distance <= (diagonal_distance / 4)) {
        pixel.h = 60;
      } else if (distance <= (diagonal_distance / 2)) {
        pixel.h = 120;
      } else if (distance <= (diagonal_distance * 0.75)) {
        pixel.h = 180;
      } else {
        pixel.h = 210;
      }
      // change luminance
      if (distance <= (diagonal_distance) * 0.125) {
        pixel.l = 0.8;
      } else if (distance <= (diagonal_distance * 0.25)) {
        pixel.l = 0.7;
      } else if (distance <= (diagonal_distance * 0.375)) {
        pixel.l = 0.65;
      } else if (distance <= (diagonal_distance * 0.5)) {
        pixel.l = 0.55;
      } else if (distance <= (diagonal_distance * 0.625)) {
        pixel.l = 0.5;
      } else if (distance <= (diagonal_distance * 0.75)) {
        pixel.l = 0.45;
      } else if (distance <= (diagonal_distance * 0.875)) {
        pixel.l = 0.4;
      } else {
        pixel.l = 0.35;
      }
    }
  }

  return png;
}
