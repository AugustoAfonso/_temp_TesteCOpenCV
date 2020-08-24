// openCVProject.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
  

    Mat image;
    Mat pattern;
    Mat result;

    image = imread(argv[1], IMREAD_COLOR); // Read the image file
    pattern = imread(argv[2], IMREAD_COLOR); // Read pattern to find

    //cout << argv[1] << std::endl;
    //cout << argv[2] << std::endl;


    if (!image.data) // Check for invalid input
    {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }


    int result_cols = image.cols - pattern.cols + 1;
    int result_rows = image.rows - pattern.rows + 1;
    result.create(result_rows, result_cols, CV_32FC1); // Create result matrix

    matchTemplate(image, pattern, result, TM_CCORR_NORMED); // Executes pattern matching process
    normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());// Normalizes result matrix

    double minVal;
    double maxVal;
    Point minLoc;
    Point maxLoc;
    Point matchLoc;

    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat()); //Find largest percentual match value
    matchLoc = maxLoc; // For TM_CCORR_NORMED the best result is the maximum value

    rectangle(image, matchLoc, Point(matchLoc.x + pattern.cols, matchLoc.y + pattern.rows), Scalar::all(0), 2, 8, 0);
  
    cout << "X:" << matchLoc.x << std::endl;
    cout << "Y:" << matchLoc.y << std::endl;
    rectangle(result, matchLoc, Point(matchLoc.x + pattern.cols, matchLoc.y + pattern.rows), Scalar::all(0), 2, 8, 0);
    namedWindow("Display Window", WINDOW_AUTOSIZE);
    //namedWindow("Result Window", WINDOW_AUTOSIZE);
    imshow("Display Window", image);
    //imshow("Result Window", result);


    waitKey(0); // Wait for a keystroke in the window
    return 0;
}
