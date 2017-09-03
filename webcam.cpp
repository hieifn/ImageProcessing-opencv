#include <stdio.h>
#include <iostream>
#include "cv.h"
#include "highgui.h"

using namespace std;
using namespace cv;

CvCapture* g_capture = 		NULL;

int main( int argc, char** argv ) {

	cvNamedWindow( "Example4", CV_WINDOW_AUTOSIZE );
	//cvNamedWindow( "Example4", 0 );
	//cvResizeWindow("Example4", 1000, 1000);
	//g_capture = cvCreateFileCapture( argv[1] );
	g_capture = cvCaptureFromCAM(CV_CAP_ANY);

	if(!g_capture)
	{
		cout << "Nao achou a camera, otario !\n";
	}
	
	IplImage* frame;

// While loop (as in Example 2) capture & show video

	while(1){
		frame = cvQueryFrame( g_capture );
		if( !frame )
			break;

		cvShowImage("Example4", frame);	
		char c = cvWaitKey(1);
		
		if(c == 27)
			break;
	
	}

// Release memory and destroy window

	cvReleaseCapture( &g_capture );
	cvDestroyWindow("Example4");

	
return(0);

}

