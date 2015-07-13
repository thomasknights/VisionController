
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

/*********       Headers      ************/

int imageSave(cv::Mat image);
cv::Mat imageLoad(std::string line, int channelFlag);
void videoSave(int inType);
void videoLoad(int inType);
void cameraSave(int inType);
void cameraDetect(int inType);
bool loadList(std::vector<std::string> & path);
void displayImage(std::string windowName, cv::Mat image);
void exit();

/*********       User interface       *********/
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
	bool listLoaded = false;
	std::vector<std::string> paths;

	cv::namedWindow(currImage, CV_WINDOW_AUTOSIZE);

	while (true) {
		
		int length = 0;
		int homeAnswer;
		int firstAnswer;
		cv::Mat image;
		cv::Mat imageToLoad;

		std::cout << "What would you like to do with the displayed image? Options are:" << std::endl
			<< "1: Save/Load image" << std::endl
			<< "2: Save/Load video" << std::endl
			<< "3: Save/Check for camera" << std::endl
			<< "4: Detections" << std::endl
			<< "5: Options" << std::endl
			<< "6: Update image" << std::endl
			<< "7: Change image" << std::endl
			<< "8: Load list" << std::endl
			<< "9: Help" << std::endl
			<< "0: Exit" << std::endl
			<< "Key the number corresponding to your selection." << std::endl;

		std::cin >> homeAnswer;

		if (homeAnswer == 1) {

			//Image IO operations
			std::cout << "1: Save, 2: Load, or 3: Back?" << std::endl;
			std::cin >> firstAnswer;

			if (firstAnswer == 1) {
				//Save
				imageSave(image);
			}
			else if (firstAnswer == 2) {
				//Load
				std::string fileName;
				std::cout << "Enter the name and extension of the image (I.E. 'face1.jpg')" << std::endl
					<< "Please include file type (.jpg, .bmp, etc.), do not include quotes." << std::endl
					<< "Selection: ";
				std::cin >> fileName;
				std::cout << std::endl;

				image = imageLoad(fileName, 1); //FIXME: channelFlag (second input) should not be hardcoded, leave as is only for testing
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

			//first tier choice
			std::cout <<"1: Save, 2: Load, or 3: Back?" << std::endl;
			std::cin >> firstAnswer;

			if (firstAnswer == 1) {
				//videoSave();
			}
			else if (firstAnswer == 2) {
				//videoLoad();
			}
			else if (firstAnswer == 3) {
				//back
			}
			else {
				std::cout << "Invalid input" << std::endl;
			}
		}
		else if (homeAnswer == 3) {

			//first tier choice
			std::cout << "1: Save, 2: Detect, or 3: Back?" << std::endl;
			std::cin >> firstAnswer;

			if (firstAnswer == 1) {
				//cameraSave();
			}
			else if (firstAnswer == 2) {
				//cameraDetect();
			}
			else if (firstAnswer == 3) {
				//back
			}
			else {
				std::cout << "Invalid input" << std::endl;
			}
		}
		else if (homeAnswer == 4) {
			//first tier choice
			//detectionAlgs();
		}
		else if (homeAnswer == 5) {
			//first tier choice
			//options();
		}
		else if (homeAnswer == 6) {
			//first tier choice
			//updateImage();
		}
		else if (homeAnswer == 7) {

			//Image change selection
			std::cout << "1: Previous, 2: Next, or 3: Back?" << std::endl;
			std::cin >> firstAnswer;

			if (firstAnswer == 1) {
				//if not at 0, move to previous image, load, and display
				if (fileCount > 0) {
					--fileCount;
					image = imageLoad(paths.at(fileCount), 1);
					displayImage(currImage, image);
				}
				else {
					std::cout << "Already at first file, can't go back any further." << std::endl;
				}

				
			}
			else if (firstAnswer == 2) {
				//if not at max, move to next image, load, and display
				if (fileCount < (totalFiles-1)) {
					++fileCount;
					image = imageLoad(paths.at(fileCount), 1);
					displayImage(currImage, image);
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
			/**Loads the list, stores list length to totalFiles, then loads and displays the first image**/
			listLoaded = loadList(paths);
			totalFiles = paths.size();

			image = imageLoad(paths.at(0), 1);
			displayImage(currImage, image);


		}
		else if (homeAnswer == 9) {
			//Help

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
			exit();
			return;
		}
		else {
			std::cout << "Invalid input." << std::endl;
		}
	}
}



/*********       File I/O       *********/ 
int imageSave(cv::Mat image) {
	std::string fileName;
	int attempts = 0;

	while (true) {
		std::cout << "Enter a file name and extension (I.E. image.jpg)" << std::endl
			<< "Selection: " << std::endl;
		std::cin >> fileName;
		
		try {
			if (cv::imwrite(fileName, image)) {
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
		}
		catch (std::exception& e) {
			std::cout << "Exception in imageSave: " << e.what() << std::endl;
		}
		
		attempts++;
	}
}

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
	
	if (image.empty()) {
		std::cout << "Failed to open image." << std::endl;
		return image;
	}
	else {
		std::cout << "Good news everyone!" << std::endl << std::endl;
		return image;
	}
}

void videoSave(int inType) {


}

void videoLoad(int inType) {


}

bool loadList(std::vector<std::string> & path) {
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
		return false;
	}

	std::cout << "Targets acquired." << std::endl << std::endl;
	getchar();
	return true;
}


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