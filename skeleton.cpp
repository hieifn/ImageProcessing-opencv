#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace cv;



int 
main(int, char**)
{
    namedWindow( "fg", CV_WINDOW_AUTOSIZE );
 
    cv::VideoCapture capture( -1 );
    


    Mat img; Mat out;

    while(1) {

	capture >> img;
	cvtColor(img, img, CV_BGR2GRAY);


	cv::threshold(img, img, 127, 255, cv::THRESH_BINARY);

	cv::Mat skel(img.size(), CV_8UC1, cv::Scalar(0));
	cv::Mat temp(img.size(), CV_8UC1);


	cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));

	bool done;
	do
	{
	  cv::morphologyEx(img, temp, cv::MORPH_OPEN, element);
	  cv::bitwise_not(temp, temp);
	  cv::bitwise_and(img, temp, temp);
	  cv::bitwise_or(skel, temp, skel);
	  cv::erode(img, img, element);
	 
	  double max;
	  cv::minMaxLoc(img, 0, &max);
	  done = (max == 0);
	} while (!done);



	imshow( "fg", skel);

        char c = cvWaitKey(1);

	if( c == 27 ) 
		break;


    }

    cvDestroyWindow("fg");
    
    return 0;
}
