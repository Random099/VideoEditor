#pragma once
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <memory>
#include "Video.h"

class WindowVideo
{
public:
	WindowVideo(const std::string&, const std::string&);
	WindowVideo(const std::string&, int);
private:	
	void run(const std::string&, const std::string&);
	void run(const std::string&, int);
	std::thread thread_;
	std::shared_ptr<Video> vPtr_ = nullptr;
};