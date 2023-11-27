#pragma once
//project
#include "Parameter.h"
//opencv
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
//std
#include <string>
#include <stdexcept>
#include <iostream>
#include <map>
#include <memory>
#include <thread>

class Video
{
public:
	Video(int);
	Video(const std::string&);
	~Video();
	inline bool frameRead();
	cv::Mat outFrameGet();
	double fpsGet() const;
	void filterApply();
	void parameterCreate(std::shared_ptr<Parameter>);
	int frameCountGet() const;
	bool frameEmptyFlag();
	cv::Mat	frameLastGet();
private:
	cv::Mat frameIn_;
	cv::Mat frameOut_;
	cv::Mat frameLast_;
	int frameCount_;
	cv::VideoCapture capSrc_;
	double FPS_;
	std::map<PType, std::shared_ptr<Parameter>> parameters_;
	bool frameEmptyFlag_;
};

class VideoInitException : public std::runtime_error {
public:
	VideoInitException() : std::runtime_error("Capture creation error.") { }
};

class FrameReadException : public std::runtime_error {
public:
	FrameReadException() : std::runtime_error("Frame read error.") { }
};