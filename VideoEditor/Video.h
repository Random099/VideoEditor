#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <stdexcept>
#include <iostream>
#include <map>
#include <memory>
#include <thread>
#include "Parameter.h"
#include "ConcurrentQueue.h"

class Video
{
public:
	Video(int);
	Video(const std::string&);
	~Video();
	inline void frameRead();
	std::shared_ptr<cv::Mat> outFrameGet();
	double fpsGet() const;
	void filterApply();
	void parameterCreate(std::shared_ptr<Parameter>);
private:
	std::thread frameReader_;
	std::unique_ptr<ConcurrentQueue<cv::Mat>> framesRead_;
	int frameCount_;
	cv::VideoCapture capSrc_;
	double FPS_;
	//cv::Mat frameIn_;
	cv::Mat frameOut_;
	std::map<PType, std::shared_ptr<Parameter>> parameters_;
};

class VideoInitException : public std::runtime_error {
public:
	VideoInitException() : std::runtime_error("Capture creation error.") { }
};

class FrameReadException : public std::runtime_error {
public:
	FrameReadException() : std::runtime_error("Frame read error.") { }
};