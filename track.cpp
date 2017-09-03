#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace cv;


int match_method;
int max_Trackbar = 5;


int 
main(int, char**)
{
    namedWindow( "Tracker", CV_WINDOW_AUTOSIZE );
    namedWindow( "Result Tracker", CV_WINDOW_AUTOSIZE );
   
    cv::VideoCapture capture( -1 );
    



    char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
    createTrackbar( trackbar_label, "Tracker", &match_method, max_Trackbar );

    

    cv::Mat frame; cv::Mat img_display;
    cv::Mat templ;
    cv::Mat result;


    unsigned result_cols, result_rows;

    templ = imread("lena.jpeg", 1);


    while(1) {
        capture >> frame;
	
	frame.copyTo(img_display);


       // GaussianBlur( frame, out, Size(5, 5), 0, 0 );

	result_cols =  frame.cols - templ.cols + 1;
	result_rows = frame.rows - templ.rows + 1;
	

	result.create(result_rows, result_cols, CV_32FC1);


	matchTemplate( frame, templ, result, match_method );
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat() );


	double minVal; double maxVal; Point minLoc; Point maxLoc;
	Point matchLoc;


	minMaxLoc(  result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());


	if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
		matchLoc = minLoc; 
	else
	       	matchLoc = maxLoc;


	rectangle( img_display, matchLoc, 
			Point( matchLoc.x + templ.cols , 
				matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );

	rectangle( result, matchLoc, 
			Point( matchLoc.x + templ.cols , 
				matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );


        if( !frame.data ) break;

        imshow( "Tracker", img_display );
        imshow( "Result Tracker", result );


        char c = cvWaitKey(33);
        if( c == 'c' ) break;
    }

    cvDestroyWindow("Tracker");
    cvDestroyWindow("Result Tracker");

    return 0;
}
