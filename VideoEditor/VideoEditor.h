#pragma once
//project
#include "Video.h"
#include "ControlPanel.h"
#include "WindowVideo.h"
//opencv
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
//imgui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
//std
#include <vector>
#include <memory>
#include <utility>
#include <map>

class VideoEditor
{
public:
	//void test(int, void*);
	VideoEditor();
	~VideoEditor();
	int run();
	std::shared_ptr<WindowVideo> getWindow(const std::string&);
	void videoWindowCreate(const std::string&, int);
	void videoWindowCreate(const std::string&, const std::string&);
	void videoWindowDestroy(const std::string&);
	void controlPanelCreate(const std::string&z);
	void controlPanelDestroy(const std::string&);
	std::shared_ptr<WindowVideo> operator[](const std::string&);
private:
	std::map<std::string, std::shared_ptr<ControlPanel>> controlPanels_;
	std::map<std::string, std::shared_ptr<WindowVideo>> videoWindows_;
};