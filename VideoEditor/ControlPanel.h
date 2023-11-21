#pragma once
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <vector>
#include <thread>
#include <iostream>

class ControlPanel
{
public:
	inline static const cv::Mat imgBackground {cv::imread("wichu.png")};
	inline static const std::string defaultName { "Control Panel" };
	ControlPanel(const std::string&);
	//void operator()(const std::string&, const std::string&);
private:
	void run(const std::string&);
	std::thread thread_;
};
