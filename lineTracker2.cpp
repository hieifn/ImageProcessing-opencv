#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace cv;



void on_low_r_thresh_trackbar(int, void *);
void on_high_r_thresh_trackbar(int, void *);
void on_low_g_thresh_trackbar(int, void *);
void on_high_g_thresh_trackbar(int, void *);
void on_low_b_thresh_trackbar(int, void *);
void on_high_b_thresh_trackbar(int, void *);

int low_r=30, low_g=30, low_b=30;
int high_r=100, high_g=100, high_b=100;





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

	uchar blue  = intensity.val[0];
	uchar green = intensity.val[1];
	uchar red = intensity.val[2];
	
	cout << "Red: "<< (int) red << "Blue: " << (int) blue << "Green: " << (int) green << "\n\n" << endl;
	printf("\n\nred: %i ; blue: %i, green: %i\n\n", red, blue, green);

    	break;
    }

}

int 
main(int, char**)
{
    namedWindow( "image", CV_WINDOW_AUTOSIZE );
    namedWindow( "Threshold", CV_WINDOW_AUTOSIZE );


    createTrackbar("Low R","Threshold", &low_r, 255, on_low_r_thresh_trackbar);
    createTrackbar("High R","Threshold", &high_r, 255, on_high_r_thresh_trackbar);
    createTrackbar("Low G","Threshold", &low_g, 255, on_low_g_thresh_trackbar);
    createTrackbar("High G","Threshold", &high_g, 255, on_high_g_thresh_trackbar);
    createTrackbar("Low B","Threshold", &low_b, 255, on_low_b_thresh_trackbar);
    createTrackbar("High B","Threshold", &high_b, 255, on_high_b_thresh_trackbar);


    Mat img;
    Mat img_threshold;

	img = imread("guide.png");
	GaussianBlur(img, img, Size(5,5), 0, 0);
	img.copyTo(img_threshold);
	

	while((char)waitKey(1)!='q')
	{
	        if(img.empty())
        		break;
        //-- Detect the object based on RGB Range Values
	
		inRange(img,Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r),img_threshold);
        //-- Show the frames
        
		imshow("image",img);
		imshow("Threshold",img_threshold);

		cvSetMouseCallback("image",mouseHandler, &img);
	}

    return 0;
}



void on_low_r_thresh_trackbar(int, void *){
    low_r = min(high_r-1, low_r);
    setTrackbarPos("Low R","Threshold", low_r);
}

void on_high_r_thresh_trackbar(int, void *){
    high_r = max(high_r, low_r+1);
    setTrackbarPos("High R", "Threshold", high_r);
}

void on_low_g_thresh_trackbar(int, void *){
    low_g = min(high_g-1, low_g);
    setTrackbarPos("Low G","Threshold", low_g);
}

void on_high_g_thresh_trackbar(int, void *){
    high_g = max(high_g, low_g+1);
    setTrackbarPos("High G", "Threshold", high_g);
}

void on_low_b_thresh_trackbar(int, void *){
    low_b= min(high_b-1, low_b);
    setTrackbarPos("Low B","Threshold", low_b);
}

void on_high_b_thresh_trackbar(int, void *){
    high_b = max(high_b, low_b+1);
    setTrackbarPos("High B", "Threshold", high_b);
}
