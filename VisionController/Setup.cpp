
/**

Requires: 
OpenCV's imgproc.hpp & highgui.hpp.

**/

/**
Home module for VisionController
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
#include <vector>
#include <stdbool.h>
#include <exception>
#include "Setup.hpp"
#include "ObjectDetection.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui.hpp"

/*********       Global variables       *********/
const std::string currImage = "Current Image";

/*********       End global variables       *********/

/*********       Headers      ************/

//UI
int welcome();
int videoProcessing(cv::VideoCapture vid);
void displayImage(std::string windowName, cv::Mat image);
void exit();

//File I/O
int imageSave(cv::Mat image);
cv::Mat imageLoad(std::string line, int channelFlag);
int videoSave(cv::VideoCapture vid);
cv::VideoCapture videoLoad();
int cameraSave(int inType);
int cameraDetect(int inType);
int loadList(std::vector<std::string> & path);

/*********       End headers      ************/

/*********       UI       *********/
int welcome() {
	//FIXME: Add in options show c and show w to corresponding parts of license
	std::cout << "VisionController Copyright (C) 2015 Steven Schweiger" << std::endl
		<< "This program comes with ABSOLUTELY NO WARRANTY." << std::endl
		<< "This is free software, and you are welcome to redistribute it" << std::endl
		<< "under certain conditions." << std::endl << std::endl
		<< "Welcome to the Computer Vision test module." << std::endl
		//<< "'show w' for warranty details." << std::endl
		//<< "'show c' for conditions." << std::endl;
		<< "inputList.txt and images should be stored in same folder as .exe" << std::endl
		<< "If using list method, it is advisable to create an image folder at that location." << std::endl
		<< "Then in inputlist.txt point to the images using 'images/image.jpg'" << std::endl;
		//<< "Selection: ";

	//if(show w) FIXME: fill out the show w & show c options to properly launch
	//if(show c)

	//cv::waitKey(100);
	
	return 0;
}

void home(int inputMethod) {
	int fileCount = 0; //Controls active file, Prev & Next decrement/increment this
	int totalFiles = 0;
	int errors;
	std::vector<std::string> paths;
	cv::Mat image;
	cv::Mat imageToLoad;
	cv::VideoCapture vid;
	cv::namedWindow(currImage, CV_WINDOW_AUTOSIZE);

	while (true) {
		int length = 0;
		int homeAnswer;
		int firstAnswer;
		
		std::cout << "What would you like to do with the displayed image? Options are:" << std::endl
			<< "1: Save/Load image" << std::endl
			<< "2: Save/Load video" << std::endl
			<< "3: Camera options" << std::endl
			<< "4: Detections" << std::endl
			<< "5: Options" << std::endl
			<< "6: Update image" << std::endl
			<< "7: Change image" << std::endl
			<< "8: Load list" << std::endl
			<< "9: Help" << std::endl
			<< "0: Exit" << std::endl
			<< "Key the number corresponding to your selection: ";

		std::cin >> homeAnswer;

		if (homeAnswer == 1) {
			/*****     Image options     *****/
			std::cout << "1: Save, 2: Load, or 3: Back?" << std::endl;
			std::cin >> firstAnswer;

			if (firstAnswer == 1) {
				//Save
				errors = imageSave(image);
				(errors == 0) ? std::cout << "Image saved successfully." << std::endl << std::endl
					: std::cout << "Image save failed." << std::endl << std::endl;
			}
			else if (firstAnswer == 2) {
				//Load
				std::string fileName;
				std::cout << "Enter the name and extension of the image (I.E. 'images/face1.jpg' without quotes)" << std::endl
					<< "Acceptable extensions are:" << std::endl
					<< ".jpg, .jpeg, .jpe, .jp2, .bmp, .dib, .png, .webp" << std::endl
					<< ".pgm, .pbm, ppm, .sr, .ras, .tiff, .tif" << std::endl
					<< "Selection: ";
				std::cin >> fileName;
				std::cout << std::endl;

				image = imageLoad(fileName, 1); //FIXME: channelFlag (second input) should not be hardcoded, leave as is only for testing
				(!(image.empty())) ? std::cout << "Image loaded successfully." << std::endl << std::endl
					: std::cout << "Image load failed." << std::endl << std::endl;
				displayImage(currImage, image);
			}
			else if (firstAnswer == 3) {
				//Back
			}
			else{
				std::cout << "Invalid input" << std::endl;
			}
		}
		else if (homeAnswer == 2) {
			errors = videoProcessing(vid);
		}
		else if (homeAnswer == 3) {
			/*****     Camera options   WIP  *****/
			std::cout << "1: Save, 2: Detect, 3: Open feed, 4: Reset feed, or 5: Back?" << std::endl;
			std::cin >> firstAnswer;

			if (firstAnswer == 1) {
				//errors = cameraSave();
				(errors == 0) ? std::cout << "Camera saved successfully." << std::endl << std::endl
					: std::cout << "Camera save failed." << std::endl << std::endl;
			}
			else if (firstAnswer == 2) {
				//errors = cameraDetect();
				(errors == 0) ? std::cout << "Camera detected successfully." << std::endl << std::endl
					: std::cout << "Camera detection failed." << std::endl << std::endl;
			}
			else if (firstAnswer == 3) {
				//errors = openFeed();
				(errors == 0) ? std::cout << "Feed opened successfully." << std::endl << std::endl
					: std::cout << "Feed failed to open." << std::endl << std::endl;
			}
			else if (firstAnswer == 4) {
				//errors = openFeed();
				(errors == 0) ? std::cout << "Feed reset successfully." << std::endl << std::endl
					: std::cout << "Feed failed to reset." << std::endl << std::endl;
			}
			else if (firstAnswer == 5) {
				//back
			}
			else {
				std::cout << "Invalid input" << std::endl;
			}
		}
		else if (homeAnswer == 4) {
			/*****     Detection   WIP  *****/
			//errors = detectionAlgs();
			(errors == 0) ? std::cout << "Detection successfully executed." << std::endl << std::endl
				: std::cout << "Detection failed to execute." << std::endl << std::endl;
		}
		else if (homeAnswer == 5) {
			/*****     Settings  WIP   *****/
			//errors = options();
			(errors == 0) ? std::cout << "Options saved successfully." << std::endl << std::endl
				: std::cout << "Options failed to save." << std::endl << std::endl;
		}
		else if (homeAnswer == 6) {
			/*****     Update     *****/
			displayImage(currImage, image);
			std::cout << "Image updated." << std::endl << std::endl;
		}
		else if (homeAnswer == 7) {
			/*****     Image selection     *****/
			std::cout << "1: Previous, 2: Next, or 3: Back?" << std::endl;
			std::cin >> firstAnswer;

			if (firstAnswer == 1) {
				//if fileCount not at 0, move to previous image, load, and display
				if (fileCount > 0) {
					--fileCount;
					image = imageLoad(paths.at(fileCount), 1);
					displayImage(currImage, image);
					std::cout << "Image: " << fileCount << std::endl << std::endl;
				}
				else {
					std::cout << "Already at first file, can't go back any further." << std::endl;
				}
			}
			else if (firstAnswer == 2) {
				//if fileCount not at max, move to next image, load, and display
				if (fileCount < (totalFiles-1)) {
					++fileCount;
					image = imageLoad(paths.at(fileCount), 1);
					displayImage(currImage, image);
					std::cout << "Image: " << fileCount << std::endl << std::endl;
				}
				else {
					std::cout << "Already at last file, can't go on any further." << std::endl;
				}			
			}
			else if (firstAnswer == 3) {
				//back
			}
			else {
				std::cout << "Invalid input" << std::endl;
			}
		}
		else if (homeAnswer == 8) {
			/*****     List loading     *****/
			errors = loadList(paths);
			totalFiles = paths.size();

			image = imageLoad(paths.at(0), 1);
			displayImage(currImage, image);

			(errors == 0) ? std::cout << "List opened successfully." << std::endl << std::endl 
				: std::cout << "List failed to open." << std::endl << std::endl;
		}
		else if (homeAnswer == 9) {
			/*****     Help     *****/
			std::cout << "Help topics are: " << std::endl
				<< "Add help topics";
			std::cin >> firstAnswer;

			if (firstAnswer == 1) {

			}
			else if (firstAnswer == 2) {

			}
			else if (firstAnswer == 3) {
				//back
			}
			else {
				std::cout << "Invalid input" << std::endl;
			}
		}
		else if (homeAnswer == 0) {
			/*****     Exit    *****/
			exit();
			return;
		}
		else {
			std::cout << "Invalid input." << std::endl;
		}
	}
}

int videoProcessing(cv::VideoCapture vid) {
	int errors;
	int selection;
	cv::Mat frame;
	cv::Mat image;
	bool paused = false;

	while (true) {
		if (!paused)
		{
			vid >> frame;
			if (frame.empty()) {
				break;
			}
			frame.copyTo(image);
		}

		/*****     Video options   WIP  *****/
		std::cout << "What would you like to do with the displayed frame? Options are:" << std::endl
			<< "'S': Save frame" << std::endl
			<< "' ': Pause frame" << std::endl
			<< "'O': Camera options" << std::endl
			<< "4: Detection" << std::endl
			<< "5: Options" << std::endl
			<< "6: Update image" << std::endl
			<< "7: Change image" << std::endl
			<< "8: Load list" << std::endl
			<< "9: Help" << std::endl
			<< "0: Exit" << std::endl
			<< "Enter the key corresponding to your selection." << std::endl;
		std::cin >> selection;

		if (selection == 1) {
			errors = videoSave(vid);
			(errors == 0) ? std::cout << "Frame saved successfully." << std::endl << std::endl
				: std::cout << "Frame save failed." << std::endl << std::endl;
		}
		else if (selection == 2) {
			vid = videoLoad();
			(vid.isOpened()) ? std::cout << "Video loaded successfully." << std::endl << std::endl
				: std::cout << "Video load failed." << std::endl << std::endl;
		}
		else if (selection == 3) {
			//back
		}
		else {
			std::cout << "Invalid input" << std::endl;
		}
	}
	return 0;
}

/**
*DisplayImage attempts to display the loaded image file to the window
**/
void displayImage(std::string windowName, cv::Mat image) {

	try {
		cv::imshow(windowName, image);
		cv::waitKey(30);
	}
	catch (std::exception& e) {
		std::cout << "Exception in displayImage: " << e.what() << std::endl;
	}

}

void exit() {

	std::cout << "Thanks for using VisionController." << std::endl
		<< "Closing." << std::endl;
}

/*********       End UI       *********/

/**
*******    File I/O    *******
*imageSave recieves a Mat, asks for save name & extension.
*Based upon extension, user may be asked for additional save paramaters.
*Max attempts = 10
*Returns 0 if save is successfull
*1 if user exits
*2 if max attempts are reached
**/ 
int imageSave(cv::Mat image) {
	std::string fileName;
	std::vector<int> compressionParams;
	int attempts = 0;
	int length;
	std::string extension;
	std::string extensionBegin = ".";
	int extPos = 0;

	while (true) {
		std::cout << "Enter a file name and extension (I.E. image.jpg)" << std::endl
			<< "Acceptable extensions are:" << std::endl
			<< ".jpg, .jpeg, .jpe, .jp2, .bmp, .dib, .png, .webp" << std::endl
			<< ".pgm, .pbm, ppm, .sr, .ras, .tiff, .tif" << std::endl
			<< "Selection: " << std::endl;
		std::cin >> fileName;

		extPos = fileName.find(extensionBegin);
		length = fileName.size();
		

		for (int i = extPos; i < length; i++) {
			tolower(fileName.at(i));
		}
		extension = fileName.substr(extPos, 6);

		std::cout << "ext: " << extension << std::endl;
		
		getchar();

		if (extension.compare(".jpeg") == 0) {
			int jpegQuality;
			std::cout << "Enter image quality (Lowest) 0 - 100 (Highest)" << std::endl
				<< "Selection: " << std::endl;
			std::cin >> jpegQuality;

			compressionParams.push_back(CV_IMWRITE_JPEG_QUALITY);
			compressionParams.push_back(jpegQuality);

			try {
				if (cv::imwrite(fileName, image, compressionParams)) {
					std::cout << "Saving." << std::endl;
					return 0;
				}
				else if (fileName == "exit") {
					return 1;
				}
				else if (attempts == 9) {
					return 2;
				}
				else {
					std::cout << "Error writing image, try again or key back to go back." << std::endl
						<< "Attempts left: " << (10 - (attempts + 1)) << std::endl;
				}
				attempts++;
			}
			catch (std::exception& e) {
				std::cout << "Exception in imageSave: " << e.what() << std::endl;
			}
		}
		else if (extension.compare(".webp") == 0) {
			int webpQuality;
			std::cout << "Enter image quality (Lowest) 0 - 101 (Highest)" << std::endl
				<< "Note: if value >100 is selected lossless compression is used." << std::endl
				<< "Selection: " << std::endl;
			std::cin >> webpQuality;

			compressionParams.push_back(CV_IMWRITE_WEBP_QUALITY);
			compressionParams.push_back(webpQuality);

			try {
				if (cv::imwrite(fileName, image, compressionParams)) {
					std::cout << "Saving." << std::endl;
					return 0;
				}
				else if (fileName == "exit") {
					return 1;
				}
				else if (attempts == 9) {
					return 2;
				}
				else {
					std::cout << "Error writing image, try again or key back to go back." << std::endl
						<< "Attempts left: " << (10 - (attempts + 1)) << std::endl;
				}
				attempts++;
			}
			catch (std::exception& e) {
				std::cout << "Exception in imageSave: " << e.what() << std::endl;
			}
		}
		else if (extension.compare(".png") == 0) {
			int pngQuality;
			std::cout << "Enter compression level (Lowest) 0 - 9 (Highest)" << std::endl
				<< "Note: PNG is lossless, higher compression levels suffer only longer compression times." << std::endl
				<< "Selection: " << std::endl;
			std::cin >> pngQuality;

			compressionParams.push_back(CV_IMWRITE_PNG_COMPRESSION);
			compressionParams.push_back(pngQuality);

			try {
				if (cv::imwrite(fileName, image, compressionParams)) {
					std::cout << "Saving." << std::endl;
					return 0;
				}
				else if (fileName == "exit") {
					return 1;
				}
				else if (attempts == 9) {
					return 2;
				}
				else {
					std::cout << "Error writing image, try again or key back to go back." << std::endl
						<< "Attempts left: " << (10 - (attempts + 1)) << std::endl;
				}
				attempts++;
			}
			catch (std::exception& e) {
				std::cout << "Exception in imageSave: " << e.what() << std::endl;
			}
		}
		else {
			try {
				if (cv::imwrite(fileName, image)) {
					std::cout << "Saving." << std::endl;
					return 0;
				}
				else if (fileName == "exit") {
					return 1;
				}
				else if (attempts == 9) {
					return 2;
				}
				else {
					std::cout << "Error writing image, try again or key back to go back." << std::endl
						<< "Attempts left: " << (10 - (attempts + 1)) << std::endl;
				}
				attempts++;
			}
			catch (std::exception& e) {
				std::cout << "Exception in imageSave: " << e.what() << std::endl;
			}
		}
	}
}

/**
*ImageLoad takes a string and an int and loads image from string using channel determined by channelFlag.
*Returns an image in Mat form
**/
cv::Mat imageLoad(std::string line, int channelFlag) {
	cv::Mat image;

	std::cout << "Loading image: " << line << std::endl;

	/** FIXME: calling grayscale breaks due to BGR2GRAY in cvt color later
	std::cout << "Loading: " <<  lines[fIndex] << std::endl <<
	"What flag would you like to use for image " << (fIndex + 1) << ">" << std::endl
	<< "RGB no Alpha = 1, Grayscale = 0, Full RGB = -1." << std::endl;
	std::cin >> channelFlag;
	**/

	try {
		image = cv::imread(line, channelFlag);
	}
	catch (std::exception& e) {
		std::cout << "Exception in imageLoad(2): " << e.what() << std::endl;
	}

	return image;
}

int videoSave(cv::VideoCapture vid) {
	
	return 0;
}

cv::VideoCapture videoLoad() {
	std::string fileName;
	cv::VideoCapture vid;
	std::cout << "Enter the name and extension of the video (I.E. 'images/face1.avi' without quotes)" << std::endl
		<< "Acceptable extensions are:" << std::endl
		<< ".avi" << std::endl
		<< "Selection: ";
	std::cin >> fileName;
	std::cout << std::endl;

	try {
		vid.open(fileName);
		return vid;
	}
	catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return vid;
}

int cameraSave(int inType) {

	return 0;
}

int cameraDetect(int inType) {

	return 0;
}

/**
*LoadList takes a vector of strings passed by reference and attempts to populate it with the txt file pointed to by the user.
*List should be stored in the same file as source.
*Returns 0 if successfull
*1 if list failed to load
*2 if an exception occured
**/
int loadList(std::vector<std::string> & path) {
	int listLen = 0;
	std::string fileName;
	std::string buffer;
	std::ifstream inputList;
	
	std::cout << "Enter the name and extension of the list (I.E. 'inputList.txt')" << std::endl
		<< "Please include file type (.txt), do not include quotes." << std::endl
		<< "Selection: ";
	std::cin >> fileName;
	std::cout << std::endl;
	
	try {
		inputList.open(fileName);

		if (inputList.is_open()) {
			std::cout << "inputList open" << std::endl << std::endl;
		}
		else {
			return 1;
		}

		std::cout << "Acquiring targets." << std::endl;
		//While getline returns a new line buffer it and store
		while (std::getline(inputList, buffer)) {
			path.push_back(buffer);
			std::cout << path.at(listLen) << std::endl;
			listLen++;
		}
	}
	catch (std::exception& e) {
		std::cout << "Exception in loadList: " << e.what() << std::endl;
		return 2;
	}

	std::cout << "Targets acquired." << std::endl << std::endl;
	getchar();
	return 0;
}

/**** End File I/O ****/


