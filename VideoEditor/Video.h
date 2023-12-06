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
	void parameterAdd(std::shared_ptr<Parameter>);
	int frameCountGet() const;
	bool frameEmptyFlag();
	cv::Mat	frameLastGet();
	std::shared_ptr<std::map<Param::Type, std::shared_ptr<Parameter>>> parametersGet();
private:
	std::map<Param::Type, std::shared_ptr<Parameter>> parameters_;
	cv::VideoCapture capSrc_;
	cv::Mat frameIn_;
	cv::Mat frameOut_;
	cv::Mat frameLast_;
	double FPS_{};
	int frameCount_{};
	bool frameEmptyFlag_{};
};

class VideoInitException : public std::runtime_error {
public:
	VideoInitException() : std::runtime_error("Capture creation error.") { }
};

class FrameReadException : public std::runtime_error {
public:
	FrameReadException() : std::runtime_error("Frame read error.") { }
};