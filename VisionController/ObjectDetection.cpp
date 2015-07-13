/**
Object detection module for VisionController
Copyright (C) {2015}  Steven Schweiger

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#include <iostream>
#include <fstream>
#include <string>
#include "ObjectDetection.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"

//Global variables
const double scaleFactor = 1.05;
const int hitsForDetection = 0;
const static cv::Scalar colors[] = { CV_RGB(0, 0, 0) = 0, CV_RGB(255, 255, 255) = 1 };
const cv::Size minFaceSize(0, 0);
const cv::Size maxFaceSize(100, 100);
const cv::Size minEyeSize(0, 0);
const cv::Size maxEyeSize(100, 100);
const cv::Size minEyeglassSize(0, 0);
const cv::Size maxEyeglassSize(100, 100);
const cv::Size minDogSize(0, 0);
const cv::Size maxDogSize(100, 100);
const cv::Size minCatSize(0, 0);
const cv::Size maxCatSize(100, 100);
const cv::Size minPartyCupSize(0, 0);
const cv::Size maxPartyCupSize(100, 100);
const cv::Size minPongBallSize(0, 0);
const cv::Size maxPongBallSize(100, 100);
const std::string faceCascadeName = 
"C:\\Users\\pyro\\Downloads\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml";
const std::string faceAltCascadeName = 
"C:\\Users\\pyro\\Downloads\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt2.xml";
const std::string faceDefCascadeName = 
"C:\\Users\\pyro\\Downloads\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_default.xml";
const std::string faceTreeCascadeName = 
"C:\\Users\\pyro\\Downloads\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt_tree.xml";
const std::string eyesCascadeName = "C:\\Users\\pyro\\Downloads\\opencv\\build\\etc\\haarcascades\\haarcascade_eye.xml";
const std::string eyeglassesCascadeName = "";
const std::string dogCascadeName = "";
const std::string catCascadeName = "";
const std::string pCupCascadeName = "";
const std::string pBallCascadeName = "";

void grayImage(cv::Mat *image, cv::Mat *grayImage, int channelFlag);
void squareMaker(cv::Mat image, double x, double y, double width, double height, cv::Scalar color);
void circleMaker(cv::Mat image, double x, double y, double width, double height, cv::Scalar color);

cv::Mat detectFaces(cv::Mat *image, int channelFlag) {
	cv::CascadeClassifier faceCascade;
	cv::CascadeClassifier faceAltCascade;
	cv::CascadeClassifier faceDefCascade;
	cv::CascadeClassifier faceTreeCascade;
	cv::Mat gray_image;
	cv::Scalar color;
	std::vector<cv::Rect> faces;
	int faceIndex = 0;
	int count = 0;
	int fSize;
	//unsigned long long time;

	imshow(origWin, *image);

	//load face cascades
	faceCascade.load(faceCascadeName) ? std::cout << "Face cascade loaded." << std::endl : 
		std::cout << "Error loading face cascade." << std::endl;
	faceAltCascade.load(faceAltCascadeName) ? std::cout << "Face alt cascade loaded." << std::endl :
		std::cout << "Error loading alt face cascade." << std::endl;
	faceDefCascade.load(faceDefCascadeName) ? std::cout << "Default face cascade loaded." << std::endl :
		std::cout << "Error loading default face cascade." << std::endl;
	faceTreeCascade.load(faceTreeCascadeName) ? std::cout << "Face tree cascade loaded." << std::endl :
		std::cout << "Error loading face tree cascade." << std::endl;


	if (faceCascade.empty()|| faceAltCascade.empty() || faceDefCascade.empty() || faceTreeCascade.empty()) {
		return *image;
	}
	
	//convert to grayscale
	grayImage(image, &gray_image, channelFlag);

	//time = cv::getTickCount();

	//scan for faces
	faceCascade.detectMultiScale(gray_image, faces, scaleFactor, hitsForDetection,
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, minFaceSize, maxFaceSize);
	faceAltCascade.detectMultiScale(gray_image, faces, scaleFactor, hitsForDetection,
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, minFaceSize, maxFaceSize);
	faceDefCascade.detectMultiScale(gray_image, faces, scaleFactor, hitsForDetection,
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, minFaceSize, maxFaceSize);
	faceTreeCascade.detectMultiScale(gray_image, faces, scaleFactor, hitsForDetection,
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, minFaceSize, maxFaceSize);

	//flip it now
	flip(gray_image, gray_image, 1);

	faceCascade.detectMultiScale(gray_image, faces, scaleFactor, hitsForDetection,
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, minFaceSize, maxFaceSize);
	faceAltCascade.detectMultiScale(gray_image, faces, scaleFactor, hitsForDetection,
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, minFaceSize, maxFaceSize);
	faceDefCascade.detectMultiScale(gray_image, faces, scaleFactor, hitsForDetection,
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, minFaceSize, maxFaceSize);
	faceTreeCascade.detectMultiScale(gray_image, faces, scaleFactor, hitsForDetection,
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, minFaceSize, maxFaceSize);

	flip(gray_image, gray_image, 1);

	fSize = faces.size();

	for (faceIndex = 0; faceIndex < fSize; faceIndex++) {
		color = colors[faceIndex % 2];

		squareMaker(*image, faces[faceIndex].x, faces[faceIndex].y, faces[faceIndex].width, faces[faceIndex].height, color);
	}

	//time = ((cv::getTickCount() - time) / cv::getTickFrequency()) * 1000;
	//std::cout << "Detection time: " << time << "ms" << std::endl;

	//Display updated image
	imshow(newWin, *image);
	std::cout << "Updated" << std::endl;

	return *image;
}

cv::Mat detectEyes(cv::Mat *image, int channelFlag) {
	std::vector<cv::Rect> eyes;
	cv::CascadeClassifier eyeCascade;
	cv::Scalar color;
	cv::Mat gray_image;
	cv::Mat newImage;
	int eSize;
	int eyesIndex = 0;
	//unsigned long long time;

	//convert to grayscale
	grayImage(image, &gray_image, channelFlag);

	//load eye cascade
	eyeCascade.load(eyesCascadeName) ? std::cout << "Eye cascade loaded." << std::endl : std::cout
		<< "Error loading eye cascade." << std::endl;

	if (eyeCascade.empty()) {
		return *image;
	}

	//time = cv::getTickCount();

	//scan for eyes
	eyeCascade.detectMultiScale(gray_image, eyes, scaleFactor, hitsForDetection, 
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, minEyeSize, maxEyeSize);

	//flip it now
	cv::flip(gray_image, gray_image, 1);

	eyeCascade.detectMultiScale(gray_image, eyes, scaleFactor, hitsForDetection, 
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, minEyeSize, maxEyeSize);
	
	newImage = *image;
	eSize = eyes.size();
	for (eyesIndex = 0; eyesIndex < eSize; eyesIndex++) {
		color = colors[eyesIndex % 2];
		//loop places circles around eyes
		circleMaker(newImage, eyes[eyesIndex].x, eyes[eyesIndex].y, eyes[eyesIndex].width, eyes[eyesIndex].height, color);
	}
	
	//timer
	//time = ((cv::getTickCount() - time) / cv::getTickFrequency()) * 1000
	//std::cout << "Detection time: " << time << "ms" << std::endl;

	//Display updated image
	imshow(newWin, newImage);
	std::cout << "Updated" << std::endl;

	return newImage;
}

cv::Mat detectEyeglasses(cv::Mat *image, int channelFlag) {
	std::vector<cv::Rect> eyeglasses;
	cv::CascadeClassifier eyeglassesCascade;
	cv::Scalar color;
	cv::Mat gray_image;
	int egSize;
	int eyeglassIndex = 0;
	//unsigned long long time;

	//convert to grayscale
	grayImage(image, &gray_image, channelFlag);

	//load eyeglasses cascade
	eyeglassesCascade.load(eyeglassesCascadeName) ? std::cout << "Eyeglass cascade loaded." << std::endl : std::cout
		<< "Error loading eyeglass cascade." << std::endl;

	if (eyeglassesCascade.empty()) {
		return *image;
	}

	//time = cv::getTickCount();

	//scan for eyeglasses
	eyeglassesCascade.detectMultiScale(gray_image, eyeglasses, scaleFactor, hitsForDetection, 
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, minEyeglassSize, maxEyeglassSize);

	//flip it now
	cv::flip(gray_image, gray_image, 1);

	eyeglassesCascade.detectMultiScale(gray_image, eyeglasses, scaleFactor, hitsForDetection, 
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, minEyeglassSize, maxEyeglassSize);

	egSize = eyeglasses.size();

	for (eyeglassIndex = 0; eyeglassIndex < egSize; eyeglassIndex++) {
		color = colors[eyeglassIndex % 2];
		//loop places circles around eyeglasses
		squareMaker(*image, eyeglasses[eyeglassIndex].x, eyeglasses[eyeglassIndex].y,
			eyeglasses[eyeglassIndex].width, eyeglasses[eyeglassIndex].height, color);
	}

	//timer
	//time = ((cv::getTickCount() - time) / cv::getTickFrequency()) * 1000;
	//std::cout << "Detection time: " << time << "ms" << std::endl;

	//Display updated image
	imshow(newWin, *image);
	std::cout << "Updated" << std::endl;
	cv::waitKey(0);

	return *image;
}

cv::Mat detectDog(cv::Mat *image, int channelFlag) {
	cv::CascadeClassifier dogCascade;
	cv::Mat gray_image;
	cv::Scalar color;
	std::vector<cv::Rect> dogs;
	int dogIndex = 0;
	int count = 0;
	int dSize;
	//unsigned long long time;

	imshow(origWin, *image);

	//load dog cascade
	dogCascade.load(dogCascadeName) ? std::cout << "Dog cascade loaded." << std::endl :
		std::cout << "Error loading dog cascade." << std::endl;

	if (dogCascade.empty()) {
		return *image;
	}

	//convert to grayscale
	grayImage(image, &gray_image, channelFlag);

	//time = cv::getTickCount();

	//scan for dogs
	dogCascade.detectMultiScale(gray_image, dogs, scaleFactor, hitsForDetection, 
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, minDogSize, maxDogSize);

	//flip it now
	flip(gray_image, gray_image, 1);

	dogCascade.detectMultiScale(gray_image, dogs, scaleFactor, hitsForDetection, 
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, minDogSize, maxDogSize);


	flip(gray_image, gray_image, 1);

	dSize = dogs.size();
	for (dogIndex = 0; dogIndex < dSize; dogIndex++) {
		color = colors[dogIndex % 2];

		//loop places boxes around dogs
		squareMaker(*image, dogs[dogIndex].x, dogs[dogIndex].y, dogs[dogIndex].width, dogs[dogIndex].height, color);

	}

	//time = ((cv::getTickCount() - time) / cv::getTickFrequency()) * 1000;
	//std::cout << "Detection time: " << time << "ms" << std::endl;

	//Display updated image
	imshow(newWin, *image);
	std::cout << "Updated" << std::endl;
	cv::waitKey(0);

	return *image;

}

cv::Mat detectCat(cv::Mat *image, int channelFlag) {
	cv::CascadeClassifier catCascade;
	cv::Mat gray_image;
	cv::Scalar color;
	std::vector<cv::Rect> cats;
	int catsIndex = 0;
	int count = 0;
	int cSize;
	//unsigned long long time;

	imshow(origWin, *image);

	//load cat cascade
	catCascade.load(catCascadeName) ? std::cout << "Cat cascade loaded." << std::endl :
		std::cout << "Error loading cat cascade." << std::endl;

	if (catCascade.empty()) {
		return *image;
	}

	//convert to grayscale
	grayImage(image, &gray_image, channelFlag);

	//time = cv::getTickCount();

	//scan for cats
	catCascade.detectMultiScale(gray_image, cats, scaleFactor, hitsForDetection, 
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, minCatSize, maxCatSize);

	//flip it now
	flip(gray_image, gray_image, 1);

	catCascade.detectMultiScale(gray_image, cats, scaleFactor, hitsForDetection, 
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, minCatSize, maxCatSize);

	flip(gray_image, gray_image, 1);

	cSize = cats.size();
	for (catsIndex = 0; catsIndex < cSize; catsIndex++) {
		color = colors[catsIndex % 2];
		//loop places boxes around cats
		squareMaker(*image, cats[catsIndex].x, cats[catsIndex].y, cats[catsIndex].width, cats[catsIndex].height, color);
	}

	//time = ((cv::getTickCount() - time) / cv::getTickFrequency()) * 1000;
	//std::cout << "Detection time: " << time << "ms" << std::endl;

	//Display updated image
	imshow(newWin, *image);
	std::cout << "Updated" << std::endl;
	cv::waitKey(0);

	return *image;
}

cv::Mat detectPartyCup(cv::Mat *image, int channelFlag) {
	cv::CascadeClassifier partyCupCascade;
	cv::Mat gray_image;
	cv::Scalar color;
	std::vector<cv::Rect> cups;
	int cupsIndex = 0;
	int count = 0;
	int pcSize;
	//unsigned long long time;

	//imshow(origWin, *image);
	//cv::waitKey(0);

	//load partyCup cascade
	partyCupCascade.load(pCupCascadeName) ? std::cout << "Cup cascade loaded." << std::endl :
		std::cout << "Error loading cup cascade." << std::endl;

	if (partyCupCascade.empty()) {
		return *image;
	}

	//convert to grayscale
	grayImage(image, &gray_image, channelFlag);

	//time = cv::getTickCount();

	//scan for partyCup
	partyCupCascade.detectMultiScale(gray_image, cups, scaleFactor, hitsForDetection, 
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, minPartyCupSize, maxPartyCupSize);

	//flip it now
	flip(gray_image, gray_image, 1);

	partyCupCascade.detectMultiScale(gray_image, cups, scaleFactor, hitsForDetection, 
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, minPartyCupSize, maxPartyCupSize);

	flip(gray_image, gray_image, 1);

	pcSize = cups.size();
	for (cupsIndex = 0; cupsIndex < pcSize; cupsIndex++) {
		color = colors[cupsIndex % 2];
		squareMaker(*image, cups[cupsIndex].x, cups[cupsIndex].y, cups[cupsIndex].width, cups[cupsIndex].height, color);
	}

	//time = ((cv::getTickCount() - time) / cv::getTickFrequency()) * 1000;
	//std::cout << "Detection time: " << time << "ms" << std::endl;

	//Display updated image
	imshow(newWin, *image);
	std::cout << "Updated" << std::endl;
	cv::waitKey(0);
	
	return *image;
}


cv::Mat detectPongBalls(cv::Mat *image, int channelFlag) {
	std::vector<cv::Rect> pBalls;
	cv::CascadeClassifier pongBallCascade;
	cv::Scalar color;
	cv::Mat gray_image;
	int pbSize;
	int pongBallIndex = 0;
	//unsigned long long time;

	imshow(origWin, *image);

	//convert to grayscale
	grayImage(image, &gray_image, channelFlag);

	//load pong ball cascade
	pongBallCascade.load(pBallCascadeName) ? std::cout << "Pong ball cascade loaded." << std::endl : std::cout
		<< "Error loading pong ball cascade." << std::endl;

	if (pongBallCascade.empty()) {
		return *image;
	}

	//time = cv::getTickCount();

	//scan for pong ball
	pongBallCascade.detectMultiScale(gray_image, pBalls, scaleFactor, hitsForDetection, 
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, minPongBallSize, maxPongBallSize);

	//flip it now
	cv::flip(gray_image, gray_image, 1);

	pongBallCascade.detectMultiScale(gray_image, pBalls, scaleFactor, hitsForDetection, 
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, minPongBallSize, maxPongBallSize);

	pbSize = pBalls.size();

	for (pongBallIndex = 0; pongBallIndex < pbSize; pongBallIndex++) {
		color = colors[pongBallIndex % 2];
		circleMaker(*image, pBalls[pongBallIndex].x, pBalls[pongBallIndex].y, pBalls[pongBallIndex].width, pBalls[pongBallIndex].height, color);
	}

	//timer
	//time = ((cv::getTickCount() - time) / cv::getTickFrequency()) * 1000;
	//std::cout << "Detection time: " << time << "ms" << std::endl;
	cvDestroyAllWindows();

	//Display updated image
	imshow(newWin, *image);
	std::cout << "Updated" << std::endl;
	cv::waitKey(0);

	return *image;
}

void grayImage(cv::Mat *image, cv::Mat *grayImage, int channelFlag) {

	if (channelFlag != 0) {
		cv::cvtColor((*image), (*grayImage), CV_BGR2GRAY);
	}

	//histogram equalization; spreads contrast range
	equalizeHist((*grayImage), (*grayImage));
}

void squareMaker(cv::Mat image, double x, double y, double width, double height, cv::Scalar color ) {
	cv::Point p1, p2;

	//p1 = cvPoint(cvRound(x * scaleFactor), cvRound(y * scaleFactor));
	p1 = cvPoint(x, y);
	//p2 = cvPoint(cvRound((x + width - 1) * scaleFactor), cvRound((y + height - 1) * scaleFactor));
	p2 = cvPoint((x + width), (y + height));

	//loop places boxes around faces
	rectangle(image, p1, p2, color, 1, 8, 0);

}

void circleMaker(cv::Mat image, double x, double y, double width, double height, cv::Scalar color) {
	int radius;
	cv::Point center;

	center.x = cvRound((x + width * 0.5) * scaleFactor);
	center.y = cvRound((y + height * 0.5) * scaleFactor);
	radius = cvRound((width + height) * 0.25 * scaleFactor);

	circle(image, center, radius, color, 1, 8, 0);

}