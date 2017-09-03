
#include <stdio.h>
#include "cv.h"
#include "highgui.h"

int	g_slider_position = 	0;
CvCapture* g_capture = 		NULL;

void onTrackbarSlide(int pos) {
	cvSetCaptureProperty(
		g_capture,
		CV_CAP_PROP_POS_FRAMES,
		pos
	);
}


int main( int argc, char** argv ) {

	cvNamedWindow( "Example3", CV_WINDOW_AUTOSIZE );
	//g_capture = cvCreateFileCapture( argv[1] );

	g_capture = cvCaptureFromCAM(CV_CAP_ANY);

	int frames = (int) cvGetCaptureProperty(
		g_capture,
		CV_CAP_PROP_FRAME_COUNT
	);

	if( frames!= 0 ) {
		cvCreateTrackbar(
			"Position",
			"Example3",
			&g_slider_position,
			frames,
			onTrackbarSlide
		);
	}
	
	IplImage* frame;

// While loop (as in Example 2) capture & show video

	while(1){
		frame = cvQueryFrame( g_capture );
		if( !frame )
			break;

		cvShowImage("Example3", frame);	
		char c = cvWaitKey(1);
		
		cvSetTrackbarPos(
			"Position",
			"Example3",
			++g_slider_position
		);

		if(c == 27)
			break;
	
	}

// Release memory and destroy window

	cvReleaseCapture( &g_capture );
	cvDestroyWindow("Example3");

	
return(0);

}

