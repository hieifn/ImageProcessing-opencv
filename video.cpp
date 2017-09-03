#include "highgui.h"


int main( int argc, char** argv ) {

	cvNamedWindow( "Example2", CV_WINDOW_AUTOSIZE );
	CvCapture* capture = cvCreateFileCapture( argv[1] );
	IplImage* frame;
	while(1) {
		frame = cvQueryFrame( capture );
		if( !frame ){
			printf("Estive Aqui 1");	
			break;
		}
		cvShowImage( "Example2", frame );

		char c = cvWaitKey(33);

		if( c == 27 ){ 
			printf("Estive Aqui 2");	
			break;
		}
	}
	cvReleaseCapture( &capture );
	cvDestroyWindow( "Example2" );
}

