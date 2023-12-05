#pragma once
//project
#include "Video.h"
#include "extras.h"
#include "ConcurrentQueue.h"
//opencv
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
//imgui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
//std
#include <memory>
#include <chrono>
#include <thread>

class WindowVideo
{
public:
	WindowVideo(const std::string&, const std::string&);
	WindowVideo(const std::string&, const int);
	void run();
	std::string videoNameGet() const;
private:	
	std::thread frameDisplayer_;
	Video video_;
	std::thread frameReader_;
	ConcurrentQueue<cv::Mat> frameBuffer_;
	void readFrames();
	cv::Mat frame_;
	bool isSourceCam_;
	const std::string name_;
	int currentFrameId_ = 0;
	int videoFrameCount_;
	float testFloat_ = 0.0f;
};