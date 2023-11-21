#pragma once

#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <memory>
#include <utility>
#include <map>
#include "Video.h"
#include "Window.h"
#include "ControlPanel.h"

class VideoEditor
{
public:
	//void test(int, void*);
	VideoEditor();
	~VideoEditor();
	std::shared_ptr<WindowVideo> getWindow(const std::string&);
	void videoWindowCreate(const std::string&, int);
	void videoWindowCreate(const std::string&, const std::string&);
	void videoWindowDestroy(const std::string&);
	void controlPanelCreate(const std::string&);
	void controlPanelDestroy(const std::string&);
	std::shared_ptr<WindowVideo> operator[](const std::string&);
private:
	std::map<std::string, std::shared_ptr<ControlPanel>> controlPanels_;
	std::map<std::string, std::shared_ptr<WindowVideo>> videoWindows_;
};