#include "Color.hh"
#include "Vec3.hh"

#include <iostream>

int main() {
    // image
    auto aspect_ratio = 16. / 9.;
    int imageWidth = 512;

    // calculate heigh of image and ensure its of height at least 1
    int imageHeight = int(imageWidth/ aspect_ratio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    // Viewport widths less than one are ok since they are real valued.
    auto viewportHeight = 2.0;
    auto viewportWidth = viewportHeight * (double(imageWidth)/imageHeight);

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++) {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < imageWidth; i++) {
            auto pixelColor = Color(double(i)/(imageWidth-1), double(j)/(imageHeight-1), 0);
            write_color(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.               \n";

}