#include "imageProcessor.hpp"
#include <math.h>
#include <string>
imageProcessor::imageProcessor(){}

std::vector<cv::KeyPoint> imageProcessor::blobDetection(cv::Mat &image , int minArea=0){

	/*
	 returns the keypoints of blobs in an images
	 */
	
		// Setup SimpleBlobDetector parameters.
	cv::SimpleBlobDetector::Params params;

		// Supposing that a foreground human takes minimum one quarter of the total screen size
	if(minArea == 0){
		minArea= image.rows*image.cols / 200;
	}

	params.filterByArea = true;
	params.minArea = minArea;
	params.maxArea = image.rows*image.cols / 2 ;

	params.filterByCircularity = true;
	params.minCircularity=0;
	params.maxCircularity=1;

	params.filterByColor = true;
	params.blobColor = 255;

	params.filterByConvexity = true;
	params.minConvexity=0;
	params.maxConvexity=1;


		// Set up detector with the above parameters. As of now there is not need to alter them.
	cv::Ptr<cv::SimpleBlobDetector> blobDetector = cv::SimpleBlobDetector::create(params);

		// Detect blobs.
	std::vector<cv::KeyPoint> keypoints;
	std::cout<<keypoints.size()<<std::endl;
	blobDetector->detect( image, keypoints);

	return keypoints;
}

void imageProcessor::blobExtractor(cv::Mat image,std::vector<cv::KeyPoint> keypoints, std::string pathToSave, std::string naming){
	/*
	 Write extracted blobs to image files (png format) inside the pathToSave
	 */
		//Image writer PNG parameters.
	
	std::vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(3);

	int blobCounter=0;
	std::string imageFilename;

	imageFilename = naming;


	for (int i=0;i<keypoints.size();++i){
		int size = keypoints[i].size;

		int leftestX = keypoints[i].pt.x - size;
		int uppermostY= keypoints[i].pt.y - size;
		int rightestX = keypoints[i].pt.x + size;
		int bottomY= keypoints[i].pt.y + size;

		if (leftestX < 0)
			leftestX =0;

		if(rightestX > image.cols)
			rightestX = image.cols;

		if (uppermostY<0)
			uppermostY = 0;

		if (bottomY>image.rows)
			bottomY   = image.rows;

		int rectWidth = (rightestX - leftestX);
		int rectHeight = (bottomY - uppermostY);

		cv::Rect myRect= cvRect(leftestX,uppermostY,rectWidth,rectHeight);
		cv::Mat croppedImage = image(myRect);

			//write the image to a file
		std::string filename =pathToSave+"/"+imageFilename+"Blob" + std::to_string(blobCounter++) +".png" ;
		cv::imwrite(filename,croppedImage,compression_params);
		std::cout<<"<--Writing blob number "<<blobCounter<<"-->"<<std::endl;
		std::cout<<"<--Path: "<<filename<<"-->"<<std::endl;

	}

	std::cout<<"\nSuccessfully written "<<blobCounter<<" blobs."<<std::endl;

}

cv::Mat imageProcessor::removePadding(cv::Mat &im){
	/*
	 Calculate the black borders of a blob and re-set the borders of the blob to not include them. (aka crop)
	 */

	int xsum=0;
	int top=0;
	int bot=im.rows;
	int left=0;
	int right=im.cols;

	bool flag=false;

	for (int i=0;i<im.rows;++i){
		for (int j=0;j<im.cols;++j){
			xsum+=im.at<uchar>(i,j);
			if (xsum>0){
				top = i;
				flag = true;
				break;
			}
		}
		if (flag){
			break;
		}
	}

	for (int i=0;i<im.rows;++i){
		for (int j=0;j<im.cols;++j){
			xsum+=im.at<uchar>(j,i);
			if (xsum>0){
				left = j;
				flag = true;
				break;
			}
		}
		if (flag){
			break;
		}
	}
	cv::namedWindow("peos");
	cv::imshow("peos", im);
	for (int i=im.rows;i>0;--i){
		for (int j=im.cols;j>0;--j){
			xsum+=im.at<uchar>(i,j);
			if (xsum>0){
				bot = i;
				flag = true;
				break;
			}
		}
		if (flag){
			break;
		}
	}

	for (int i=im.rows;i>0;--i){
		for (int j=im.cols;j>0;--j){
			xsum+=im.at<uchar>(j,i);
			if (xsum>0){
				right = j;
				flag = true;
				break;
			}
		}
		if (flag){
			break;
		}
	}

	cv::Rect myROI( left, top, im.cols-left - (im.cols-right) , im.rows-top - (im.rows-bot) );
	cv::Mat croppedImage = im (myROI);

	return croppedImage;


}

int imageProcessor::autoRotationAngle(cv::Mat &im){

	/*
	 Calculate the rotation angle needed. Assuming the object of interest resembles a human silhouette, the uppermost non-zero point will be the top of the head. With this in mind, the human to be upright, his head needs to be alligned to the y'y axis. This is exactly what this method does, calculates that angle.
	 */

	bool flag = false;
	double const PI = 3.14159265;
	static int y=0;
	static int x=0;
	for (;y<im.rows;++y){
		for(;x<im.cols;++x){
			if(im.at<int>(x,y)>0){
				flag=true;
				break;
			}
		}
		if (flag){
			break;
		}
	}

	float xDiff = im.cols/2.0 - x;
	float yDiff = im.rows/2.0 - y;
	float tanInRads = atan2(-xDiff,yDiff);
	int angle = tanInRads*180/PI;

	return angle;
}

void imageProcessor::rotateNoCrop(cv::Mat &im, cv::Mat &rotIm, const double angle){
	/*
	 Rotate the image without cropping. First the transformation(rotation) matrix is calculated, then a new, bigger cv::Mat is constructed.
	 */

	{
	cv::Point2f center(im.cols/2.0, im.rows/2.0);
	cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
	cv::Rect bbox = cv::RotatedRect(center,im.size(), angle).boundingRect();

	rot.at<double>(0,2) += bbox.width/2.0 - center.x;
	rot.at<double>(1,2) += bbox.height/2.0 - center.y;

	cv::warpAffine(im, rotIm, rot, bbox.size());
	}

}
