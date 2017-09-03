#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace cv;

void mouseHandler(int event, int x, int y, int flags, void* param)
{
	cv::Mat* pimage = (cv::Mat*) param;
	cv::Mat image = * pimage;

    switch(event){
    case CV_EVENT_LBUTTONDOWN:
    	if(flags & CV_EVENT_FLAG_CTRLKEY) 
            printf("Left button down with CTRL pressed\n");

        break;
    case CV_EVENT_LBUTTONUP:
        printf("Left button up\n");
   	Vec3b intensity = image.at<Vec3b>(x, y);	
	uchar blue = intensity.val[0];
	uchar green = intensity.val[1];
	uchar red = intensity.val[2];
	printf("\n\nred: %i ; blue: %i, green: %i\n\n", red, blue, green);

    	break;
    }

}


int 
main(int, char**)
{
    namedWindow( "fg", CV_WINDOW_AUTOSIZE );
    
    Mat img;

	img = imread("guide.png");
	GaussianBlur(img, img, Size(5,5), 0, 0);

	imshow( "fg", img);

	cvSetMouseCallback("fg",mouseHandler, &img);

	cvWaitKey(0);

    return 0;
}
