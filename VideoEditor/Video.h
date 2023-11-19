#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <stdexcept>
#include <iostream>
#include <map>
#include <memory>
#include "Parameter.h"

class Video
{
public:
	Video(int);
	Video(const std::string&);
	~Video();
	void readFrame();
	cv::Mat getFrame();
	cv::Mat getOutFrame();
	int getFPS() const;
	void applyFilter();
	void addParameter(Parameter*);
private:
	cv::VideoCapture capSrc;
	int FPS;
	cv::Mat originalFrame;
	cv::Mat outFrame;
	std::map<PType, Parameter*> parameters;
};

class VideoInitException : public std::runtime_error {
public:
	VideoInitException() : std::runtime_error("Capture creation error") { }
};