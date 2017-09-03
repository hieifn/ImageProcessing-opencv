#include <stdio.h>
#include <iostream>
#include "cv.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "highgui.h"

using namespace std;
using namespace cv;

/*
void CannyThreshold(int, void*)
{
  /// Reduce noise with a kernel 3x3
  blur( src_gray, detected_edges, Size(3,3) );

  /// Canny detector
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

  /// Using Canny's output as a mask, we display our result
  dst = Scalar::all(0);

  src.copyTo( dst, detected_edges);
  imshow( window_name, dst );
 }
*/

CvCapture* g_capture = 		NULL;

int main( int argc, char** argv ) {

	cvNamedWindow( "Example4a", CV_WINDOW_AUTOSIZE );
	cvNamedWindow( "Example4b", CV_WINDOW_AUTOSIZE );
	cvNamedWindow( "Example4c", CV_WINDOW_AUTOSIZE );
	cvNamedWindow( "Example4d", CV_WINDOW_AUTOSIZE );
	g_capture = cvCaptureFromCAM(CV_CAP_ANY);

	if(!g_capture)
	{
		cout << "Nao achou a camera, otario !\n";
	}
	
	IplImage* frame;
	IplImage* smooth;
	IplImage* frame_gray;
	IplImage* canny;

// While loop (as in Example 2) capture & show video

	while(1){
		frame = cvQueryFrame( g_capture );
		
		smooth = cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,3);

		frame_gray = cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
		
		canny = cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
		
		cvSmooth( frame, smooth, CV_GAUSSIAN, 11, 11);
		cvCvtColor( smooth, frame_gray, CV_BGR2GRAY );
		cvCanny( frame_gray, canny, 10, 10, 3 );


		if( !frame )
			break;

		cvShowImage("Example4a", frame);	
		cvShowImage("Example4b", smooth);	
		cvShowImage("Example4c", frame_gray);	
		cvShowImage("Example4d", canny);	
		char c = cvWaitKey(1);
		
		if(c == 27)
			break;
	
	}

// Release memory and destroy window

	cvReleaseCapture( &g_capture );
	cvDestroyWindow("Example4a");
	cvDestroyWindow("Example4b");
	cvDestroyWindow("Example4c");
	cvDestroyWindow("Example4d");

	
return(0);

}

