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
	inline void readFrame();
	cv::Mat getFrame();
	cv::Mat getOutFrame();
	int getFPS() const;
	void applyFilter();
	void addParameter(std::shared_ptr<Parameter>);
private:
	cv::VideoCapture capSrc_;
	int FPS_;
	cv::Mat originalFrame_;
	cv::Mat outFrame_;
	std::map<PType, std::shared_ptr<Parameter>> parameters_;
};

class VideoInitException : public std::runtime_error {
public:
	VideoInitException() : std::runtime_error("Capture creation error") { }
};