	/**
	Setup header for VisionController
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

#ifndef COMPVIS_SETUP_HPP
#define COMPVIS_SETUP_HPP
#endif

#include <string>
#include "opencv2/imgproc/imgproc.hpp"


enum INPUTMODES { PATH = 1, LIST = 2 };
enum IMAGEMODES { IMAGE = 1, VIDEO = 2, CAMERA = 3 };
enum CHANNELFLAGS { RGB = -1, GRAYSCALE = 0, RGBNOALPHA = 1 };

//Prints welcome text and copyright info
int welcome();
//Primary point of interaction. Interface with all other functions from here.s
void home(int inputMethod);


