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
    

    Mat frame; Mat out;
    Mat result; Mat fgModel;
    Mat bgModel;
    //Mat foreground; 
    Mat background;

    Rect rectangle(40,90,200,300);

    while(1) {
        capture >> out;

	frame = out.clone();
    
	Rect rectangle(40,90,out.cols-80,out.rows-170);

	grabCut(out,    // input image
            result,   // segmentation result
            rectangle,// rectangle containing foreground
            bgModel,fgModel, // models
            1,        // number of iterations
            cv::GC_INIT_WITH_RECT); // use rectangle

	compare(result,GC_PR_FGD,result,CMP_EQ);

	//printf();
	
	//printf("%i %i \n", out.rows, out.cols);

	Mat foreground(out.rows, out.cols, CV_8UC3, cv::Scalar(255,255,255));

	out.copyTo(foreground,result);

	cv::rectangle(out, rectangle, cv::Scalar(255,255,255),1);
	
        if( !frame.data ) break;

	imshow( "fg", foreground);

	out.copyTo(background,~result);

        char c = cvWaitKey(33);
        if( c == 'c' ) break;
    }

    cvDestroyWindow("fg");
    
    return 0;
}
