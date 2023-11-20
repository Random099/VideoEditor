#pragma once

#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <memory>
#include <utility>
#include <map>
#include "Video.h"

class ControlPanel
{
public:
	inline static const cv::Mat imgBackground {cv::imread("wichu.png")};
	inline static const std::string defaultName { "Control Panel" };
	ControlPanel(const std::string&);
	inline std::string nameGet() const;
	int* posGet();
	int maxGet();
	void targetChange(const std::string&, int*);
	void trackbarCreate(const std::string&, void(*func)(int, void*), void* data, int* pos, int max);
	//void operator()(const std::string&, const std::string&);
private:
	int pos = 50;
	int max = 100;
	std::string name_;
	std::vector<std::string> trackbars_;
};

class VideoEditor
{
public:
	int testData;
	//void test(int, void*);
	VideoEditor();
	~VideoEditor();
	std::shared_ptr<std::thread> getWindow(const std::string&);
	void windowCreate(const std::string&, int);
	void windowCreate(const std::string&, const std::string&);
	void windowDestroy(const std::string&);
	void controlPanelCreate(const std::string&);
	void controlPanelDestroy(const std::string&);
	std::shared_ptr<std::thread> operator[](const std::string&);
private:
	std::map<std::string, std::shared_ptr<std::thread>> windows_;
	std::map<std::string, std::shared_ptr<std::thread>> controlPanels_;
	void videoDisplay(const std::string&, int);
	void videoDisplay(const std::string&, const std::string&);
	void controlPanelRun(const std::string&);
	//std::vector<Video> videos_;
};

/*

Control Panel

*/
