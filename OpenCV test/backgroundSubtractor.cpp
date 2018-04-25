	//opencv
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
	//C++
#include <iostream>

using namespace cv;
using namespace std;

#include "backgroundSubtractor.hpp"


	// Global variables
Mat frame; //current frame
Mat fgMaskMOG2; //fg mask fg mask generated by MOG2 method
Ptr<BackgroundSubtractor> pMOG2; //MOG2 Background subtractor
int keyboard; //input from keyboard

void processVideo(char* videoFilename) {

		//create GUI windows
	namedWindow("Frame");
	namedWindow("FG Mask MOG 2");

		//create Background Subtractor objects
		//BackgroundSubtractorMOG2(int history, float varThreshold, bool bShadowDetection=true)
	pMOG2 = createBackgroundSubtractorMOG2(2000,220,false);

		//create the capture object
	VideoCapture capture(videoFilename);

	if(!capture.isOpened()){
			//error in opening the video input
		cerr << "Unable to open video file: " << videoFilename << endl;
		exit(EXIT_FAILURE);
	}
		//read input data. ESC or 'q' for quitting
	while( (char)keyboard != 'q' && (char)keyboard != 27 ){
			//read the current frame
		if(!capture.read(frame)) {
			cerr << "Unable to read next frame." << endl;
			cerr << "Exiting..." << endl;
			exit(EXIT_FAILURE);
		}
			//update the background model
		pMOG2->apply(frame, fgMaskMOG2);

		imshow("Frame", frame);
		imshow("FG Mask MOG 2", fgMaskMOG2);
			//get the input from the keyboard
		keyboard = waitKey( 30 );
	}
		//delete capture object
	capture.release();
	destroyAllWindows();
}
