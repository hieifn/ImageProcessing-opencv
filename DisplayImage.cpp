#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int
main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usou errado");
		return -1;
	}
	
	Mat A, C, image;
	
	A = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	
	Mat B(A);

	C = A;
	
	Mat D (A, Rect(10, 10, 100, 100) ); // using a rectangle
	
	Mat E = A(Range::all(), Range(1,3));

	Mat M(2,2, CV_8UC3, Scalar(0,0,255));
	cout << "M = " << endl << " " << M << endl << endl;
	
	namedWindow("Display Image A", WINDOW_AUTOSIZE);
	imshow("Display Image A", A);
	
	namedWindow("Display Image B", WINDOW_AUTOSIZE);
	imshow("Display Image B", B);
	
	namedWindow("Display Image C", WINDOW_AUTOSIZE);
	imshow("Display Image C", C);

	namedWindow("Display Image D", WINDOW_AUTOSIZE);
	imshow("Display Image D", D);
	
	namedWindow("Display Image E", WINDOW_AUTOSIZE);
	imshow("Display Image E", E);
	
	namedWindow("Display Image M", WINDOW_AUTOSIZE);
	imshow("Display Image M", M);
	
	image = imread(argv[1], 1);
	
	if (!image.data)
	{
		printf("ta sem imagem idiota.");
		return -1;
	}
	
	namedWindow("Display Image", WINDOW_AUTOSIZE);
	imshow("Display Image", image);

	waitKey(0);

	return 0;

}
