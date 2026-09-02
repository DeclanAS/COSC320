#include <iostream>
#include <stdlib.h>
#include "Graph.h"

/*  OpenCV was used for this project to make the loading of the image.ppm more doable
     *  The referenced paper by Huttenlocher Reccomends defining you own image class but that
     *  was far out of the scope of the project and very difficult
     * 
     * You will need to install 'opencv' to get the project to complile
     * for us it was as as easy as 'sudo <install command> opencv'
     * 
     * We also had and issue where if we didn't #include opencv in every file it
     * would have and issue so please ignore that
     * 
     */

int main(int argc, const char *argv[])
{
    std::string imageName;

    if (argc != 4)
    {
        std::cout << "ERROR: Input should look like ( ./segment <path_to_file> <threshold> <min_size> )" << std::endl;
        std::cout << "EXAMPLE: ./segment images/cameraman.ppm 1000 20 )" << std::endl;
        exit(1);
    }

    // Load image file with color
    cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
    int threshold = atoi(argv[2]);
    int min_size = atoi(argv[3]);

    // Check if the image is able to be opend
    if (image.empty())
    {
        std::cout << "ERROR: Image not Found or unable to open" << std::endl;
        exit(1);
    }

    Graph seg = Graph();
    seg.SegmentImage(image, threshold, min_size);

    cv::imshow("Segmented Image", image);

    // Wait for any input to exit (click 'X' or press 'Enter')
    cv::waitKey(0);

    return 0;
}
