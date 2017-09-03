#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace cv;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;



int 
main(int, char**)
{
    namedWindow( "Edges", CV_WINDOW_AUTOSIZE );
    createTrackbar( "Min Threshold:", "Edges", &lowThreshold, max_lowThreshold);
    cv::VideoCapture capture( -1 );

    cv::Mat frame; cv::Mat out; cv::Mat out2;

    while(1) {
        capture >> frame;

        GaussianBlur( frame, out, Size(5, 5), 0, 0 );
        cvtColor( out ,out2, CV_BGR2GRAY ); // produces out2, a one-channel image (CV_8UC1)
        Canny( out2, out2, lowThreshold, lowThreshold*ratio, kernel_size); // the result goes to out2 again,but since it is still one channel it is fine

        if( !frame.data ) break;
        imshow( "Edges", out2 );

        char c = cvWaitKey(33);
        if( c == 'c' ) break;
    }
    return 0;
}
