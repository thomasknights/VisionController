/**
Test module for VisionController
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
#include "Setup.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"



int main(int argc, char* argv[]) {
	
	//Launch welcome dialogue, acquire setup variables, return fileName
	int inputMethod = 0;

	//0 = error
	inputMethod =  welcome();

	while (true) {
		home(inputMethod);
		break;
	}

}
