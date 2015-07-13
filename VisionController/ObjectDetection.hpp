/**
Object detection header for VisionController
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

#ifndef COMPVIS_OBJECT_DETECTION_HPP
#define COMPVIS_OBJECT_DETECTION_HPP
#endif

#include <string>
#include "opencv2/imgproc/imgproc.hpp"


const std::string origWin = "Image:";
const std::string newWin = " New image:";

cv::Mat detectFaces(cv::Mat *image, int channelFlag);
cv::Mat detectEyes(cv::Mat *image, int channelFlag);
cv::Mat detectEyeglasses(cv::Mat *image, int channelFlag);
cv::Mat detectDog(cv::Mat *image, int channelFlag);
cv::Mat detectCat(cv::Mat *image, int channelFlag);
cv::Mat detectPartyCup(cv::Mat *image, int channelFlag);
cv::Mat detectPongBalls(cv::Mat *image, int channelFlag);